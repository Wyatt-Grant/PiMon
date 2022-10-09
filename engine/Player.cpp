#include "engine/Player.hpp"

Player::Player(int32_t x, int32_t y) {
    position.x = x;
    position.y = y;
    offsetTileX = 0;
    offsetTileY = 0;
    movingOffsetX = 0;
    movingOffsetY = 0;
    isAligned = true;
    inGrass = false;
    isMoving = false;
    canMoveDown = true;
    canMoveUp = true;
    canMoveLeft = true;
    canMoveRight = true;
}

bool Player::willActorsIntersect(Npc *npc, Direction d) {
    switch(d) {
        case down:
            return intersects(position.x, position.y + 16, 15, 15, npc->position.x + virtualCamera.x, npc->position.y + virtualCamera.y, 15, 15);
        case up:
            return intersects(position.x, position.y - 16, 15, 15, npc->position.x + virtualCamera.x, npc->position.y + virtualCamera.y, 15, 15);
        case left:
            return intersects(position.x - 16, position.y, 15, 15, npc->position.x + virtualCamera.x, npc->position.y + virtualCamera.y, 15, 15);
        case right:
            return intersects(position.x + 16, position.y, 15, 15, npc->position.x + virtualCamera.x, npc->position.y + virtualCamera.y, 15, 15);
        default:
            return false;
    }
}

void Player::updateMovementAvailability(const int16_t colliders[][160], std::vector<Npc*> npcs) {
    for (auto &npc : npcs) {
        if (willActorsIntersect(npc, down)) {
            canMoveDown = false;
        }
        if (willActorsIntersect(npc, up)) {
            canMoveUp = false;
        }
        if (willActorsIntersect(npc, left)) {
            canMoveLeft = false;
        }
        if (willActorsIntersect(npc, right)) {
            canMoveRight = false;
        }
    }

    if (colliders[offsetTileY + 10][offsetTileX + 8] == 419) {
        canMoveDown = false;
    }
    if (colliders[offsetTileY + 6][offsetTileX + 8] == 419) {
        canMoveUp = false;
    }
    if (colliders[offsetTileY + 8][offsetTileX + 6] == 419) {
        canMoveLeft = false;
    }
    if (colliders[offsetTileY + 8][offsetTileX + 10] == 419) {
        canMoveRight = false;
    }
}

void Player::handleTalkToNpcs(std::vector<Npc*> npcs, Message *message) {
    for (auto &npc : npcs) {
        if (pressed(A) && isAligned) {
            if (willActorsIntersect(npc, down) && direction == down) {
                message->showMessages(npc->messages);
                enemyFront = npc->frontBuffer;
                npc->direction = up;
            }
            if (willActorsIntersect(npc, up) && direction == up) {
                message->showMessages(npc->messages);
                enemyFront = npc->frontBuffer;
                npc->direction = down;
            }
            if (willActorsIntersect(npc, left) && direction == left) {
                message->showMessages(npc->messages);
                enemyFront = npc->frontBuffer;
                npc->direction = right;
            }
            if (willActorsIntersect(npc, right) && direction == right) {
                message->showMessages(npc->messages);
                enemyFront = npc->frontBuffer;
                npc->direction = left;
            }
        }
    }
}

void Player::handleGrass(const int16_t colliders[][160]) {
    inGrass = false;
    if ((colliders[offsetTileY + 9][offsetTileX + 8] == 418)
     || (colliders[offsetTileY + 9][offsetTileX + 9] == 418)
     || (colliders[offsetTileY + 8][offsetTileX + 8] == 418)
     || (colliders[offsetTileY + 8][offsetTileX + 9] == 418)) {
        inGrass = true;
    }
}

void Player::handleMovement() {
    if (button(DOWN) && isAligned) {
        if (canMoveDown) {
            virtualCamera.y -= button(B) ? 2 : 1;
        }
        direction = down;
        isMoving = true;
    } else if (button(UP) && isAligned) {
        if (canMoveUp) {
            virtualCamera.y += button(B) ? 2 : 1;
        }
        direction = up;
        isMoving = true;
    } else if (button(LEFT) && isAligned) {
        if (canMoveLeft) {
            virtualCamera.x += button(B) ? 2 : 1;
        }
        direction = left;
        isMoving = true;
    } else if (button(RIGHT) && isAligned) {
        if (canMoveRight) {
            virtualCamera.x -= button(B) ? 2 : 1;
        }
        direction = right;
        isMoving = true;
    } else if (virtualCamera.y % 16 != 0 && direction == down) {
        virtualCamera.y -= button(B) ? 2 : 1;
        isMoving = true;
    } else if (virtualCamera.y % 16 != 0 && direction == up) {
        virtualCamera.y += button(B) ? 2 : 1;
        isMoving = true;
    } else if (virtualCamera.x % 16 != 0 && direction == left) {
        virtualCamera.x += button(B) ? 2 : 1;
        isMoving = true;
    } else if (virtualCamera.x % 16 != 0 && direction == right) {
        virtualCamera.x -= button(B) ? 2 : 1;
        isMoving = true;
    } else {
        isMoving = false;
    }

    if (button(B)) {
        virtualCamera.x = virtualCamera.x/2*2;
        virtualCamera.y = virtualCamera.y/2*2;
    }
}

void Player::update(uint32_t tick, int32_t mapNumber, std::vector<Npc*> npcs, Message *message) {
    isAligned = virtualCamera.y % 16 == 0 && virtualCamera.x % 16 == 0;
    offsetTileX  = -virtualCamera.x / 8;
    offsetTileY  = -virtualCamera.y / 8;
    movingOffsetX = virtualCamera.x % 8;
    movingOffsetY = virtualCamera.y % 8;
    canMoveDown = true;
    canMoveUp = true;
    canMoveLeft = true;
    canMoveRight = true;

    if (!waiting && !menuOpen) {
        switch(mapNumber) {
            case 1:
                updateMovementAvailability(town1_outside_colliders, npcs);
                handleGrass(town1_outside_colliders);
                break;
            case 0:
                updateMovementAvailability(town1_inside_colliders, npcs);
                handleGrass(town1_inside_colliders);
                break;
        }

        handleMovement();
        handleTalkToNpcs(npcs, message);

        // 10% chance to get in battle everytime you take a "step" in grass
        srand(time() + virtualCamera.x);
        if (inGrass && isMoving && isAligned && (rand() % 10 == 5)) {
            changeSong = true;
            MainScene = BATTLE;
            transitionCounter = 0;
            transitionDone = false;

            int32_t wildNum = (((rand() % 12) + 1) * 2) - 1;

            isWildBattle = true;
            enemyParty.clear();
            enemyParty.push_back({ wildNum, party.at(0).xp, getMaxHp(wildNum, xpToLvl(party.at(0).xp)), 0 });

            virtualCamera.x = virtualCamera.x/16*16;
            virtualCamera.y = virtualCamera.y/16*16;
            isMoving = false;
        }
    }
}

void Player::setBuffer() {
    switch(playerAvatar) {
        case 1:
            spritesheet(character_1_overworld_buffer);
            break;
        case 2:
            spritesheet(character_2_overworld_buffer);
            break;
        case 3:
            spritesheet(character_3_overworld_buffer);
            break;
    }
}

void Player::draw(uint32_t tick) {
    setBuffer();

    int32_t spriteOffset = 0;
    switch(direction) {
        case up:
            spriteOffset += 12;
            break;
        case down:
            spriteOffset += 0;
            break;
        case left:
            spriteOffset += 6;
            break;
        case right:
            spriteOffset += 18;
            break;
    }

    if (isMoving && !waiting) {
        int32_t speed = button(B) ? 6 : 10;
        int32_t frame = (tick % (4 * speed))/speed * 2;
        if (frame == 4) {
            spriteOffset += 0;
        } else if (frame == 6) {
            spriteOffset += 4;
        } else {
            spriteOffset += frame;
        }
    }

    sprite(0 + spriteOffset, position.x, position.y);
    sprite(1 + spriteOffset, position.x + 8, position.y);
    if (!inGrass) {
        sprite(24 + spriteOffset, position.x, position.y + 8);
        sprite(25 + spriteOffset, position.x + 8, position.y + 8);
    }
}
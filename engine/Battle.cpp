#include "engine/Battle.hpp"

#include "sprites/players/backs.cpp"

Battle::Battle() {
    waitingForStartAnimation = true;
    animPlayer = -56;
    animEnemy = 120;
    scene = BATTLE_INTRO_TEXT;
}

void Battle::update(uint32_t tick, Message *message) {
    if (animPlayer < 0) {
        animPlayer++;
    }
    if (animEnemy > 64) {
        animEnemy--;
    }

    if (!waiting) {
        switch(scene) {
            case BATTLE_INTRO_TEXT:
                // message->showMessage("Battle Start!");
                scene = BATTLE_INTRO_ANIMATION;
                break;
            case BATTLE_INTRO_ANIMATION:
                message->showMessage("Trainer would like to\nbattle!");
                scene = BATTLE_ENEMY_TRAINER_TEXT;
                break;
            case BATTLE_ENEMY_TRAINER_TEXT:
                message->showMessage("Trainer sent out\nMonster!");
                scene = BATTLE_MONSTER_TRAINER_TEXT;
                break;
            case BATTLE_MONSTER_TRAINER_TEXT:
                MainScene = OVERWORLD;
                changeSong = true;
                waitingForStartAnimation = true;
                animPlayer = -56;
                animEnemy = 120;
                scene = BATTLE_INTRO_TEXT;
                break;
        }
    }
}

void Battle::ppSprite(buffer_t *buffer, int32_t spriteOffset, int32_t posX, int32_t posY) {
    int32_t underflow = -56;
    int32_t overflow = 120;

    if (posY >= underflow && posX >= underflow && posY <= overflow && posX <= overflow) {
        for (int32_t y = 0; y < 56; y++) {
            for (int32_t x = 0; x < 56; x++) {
                if (posX + x >= 0 && posY + y >= 0) {
                    uint32_t sx = ((spriteOffset * 56) % buffer->w) + x;
                    uint32_t sy = (((spriteOffset * 56) / buffer->w) * 56) + y;
                    blit(buffer, sx, sy, 1, 1, posX + x, posY + y);
                }
            }
        }
    }
}

void Battle::drawCharacter1Back(int32_t _x, int32_t _y) {
    if (animPlayer == 0) {
        switch(playerAvatar) {
            case 1:
                spritesheet(character_1_back_buffer);
                break;
            case 2:
                spritesheet(character_2_back_buffer);
                break;
            case 3:
                spritesheet(character_3_back_buffer);
                break;
        }
        for (int32_t y = 0; y < 7; y++) {
            for (int32_t x = 0; x < 7; x++) {
                sprite((y * 7) + x, x*8 + _x, y*8 + _y);
            }
        }
    } else {
        switch(playerAvatar) {
            case 1:
                ppSprite(character_1_back_buffer, 0, _x, _y);
                break;
            case 2:
                ppSprite(character_2_back_buffer, 0, _x, _y);
                break;
            case 3:
                ppSprite(character_3_back_buffer, 0, _x, _y);
                break;
        }
    }
}

void Battle::drawEnemyTrainerBack(int32_t _x, int32_t _y) {
    spritesheet(enemyFront);
    for (int32_t y = 0; y < 7; y++) {
        for (int32_t x = 0; x < 7; x++) {
            sprite((y * 7) + x, x*8 + _x, y*8 + _y);
        }
    }
}

void Battle::noCornerBox(int32_t x, int32_t y, int32_t w, int32_t h) {
    hline(x+1, y,   w-2);
    hline(x+1, y+h-1, w-2);
    vline(x, y+1,   h-2);
    vline(x+w-1, y+1, h-2);
}

void Battle::drawWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    pen(15,15,15);
    noCornerBox(x,y,w,h);
    frect(x+1,y+1,w-2,h-2);
    pen(3,3,3);
    noCornerBox(x+1,y+1,w-2,h-2);
}

void Battle::draw(uint32_t tick) {
    pen(15,15,15);
    clear();

    switch(scene) {
        case BATTLE_INTRO_TEXT:
            break;
        case BATTLE_INTRO_ANIMATION:
        case BATTLE_ENEMY_TRAINER_TEXT:
        case BATTLE_MONSTER_TRAINER_TEXT:
            drawCharacter1Back(animPlayer, 32);
            drawEnemyTrainerBack(animEnemy, 0);
            break;
    }

    drawWindow(0, 88, 120, 32);
}
#include "engine/Npc.hpp"

Npc::Npc(int32_t x, int32_t y, buffer_t *b, buffer_t *b2, Direction d, bool v, int32_t m) {
    avatar = 1;
    position.x = x;
    position.y = y;
    offsetTileX = 0;
    offsetTileY = 0;
    inGrass = false;
    buffer = b;
    frontBuffer = b2;
    direction = d;
    visible = v;
    map = m;
}

void Npc::addMessage(Text msg) {
    messages.push_back(msg);
}

void Npc::update(uint32_t tick, int32_t mapNumber) {
    offsetTileX  = -virtualCamera.x / 8;
    offsetTileY  = -virtualCamera.y / 8;
}

void Npc::ppSprite(int32_t spriteOffset, int32_t posX, int32_t posY) {
    int32_t underflow = -16;
    int32_t overflow = 120;

    if (posY >= underflow && posX >= underflow && posY <= overflow && posX <= overflow) {
        for (int32_t y = 0; y < 16; y++) {
            for (int32_t x = 0; x < 16; x++) {
                if (posX + x >= 0 && posY + y >= 0) {
                    uint32_t sx = ((spriteOffset * 16) % buffer->w) + x;
                    uint32_t sy = (((spriteOffset * 16) / buffer->w) * 16) + y;
                    blit(buffer, sx, sy, 1, 1, posX + x, posY + y);
                }
            }
        }
    }
}

void Npc::draw(uint32_t tick) {
    if (visible) {
        int32_t spriteOffset = 0;
        switch(direction) {
            case up:
                spriteOffset += 6;
                break;
            case down:
                spriteOffset += 0;
                break;
            case left:
                spriteOffset += 3;
                break;
            case right:
                spriteOffset += 9;
                break;
        }

        int32_t offsetX = virtualCamera.x + position.x;
        int32_t offsetY = virtualCamera.y + position.y;

        ppSprite(spriteOffset, offsetX, offsetY);
    }
}
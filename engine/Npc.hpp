#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

using namespace picosystem;

class Npc {       
    private:
        int32_t offsetTileX;
        int32_t offsetTileY;
        bool inGrass;
        int32_t avatar;

        void setBuffer();
        void ppSprite(int32_t spriteOffset, int32_t posX, int32_t posY);
        
    public:
        Point position;
        Direction direction;
        std::vector<Text> messages;
        buffer_t *buffer;
        buffer_t *frontBuffer;

        Npc(int32_t x, int32_t y, buffer_t *b, buffer_t *b2, Direction d);
        void draw(uint32_t tick);
        void update(uint32_t tick, int32_t mapNumber);
        void addMessage(Text msg);
};
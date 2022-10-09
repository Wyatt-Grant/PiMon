#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

using namespace picosystem;

class Map {       
    private:
        int32_t offsetTileX;
        int32_t offsetTileY;
        int32_t movingOffsetX;
        int32_t movingOffsetY;
        
        void drawMapTile(const int16_t map[][160], int32_t x, int32_t y);
        void drawMap(const int16_t above[][160], const int16_t below[][160]);
        void drawAboveMap(const int16_t above[][160]);
        
    public:
        Map();
        void draw(uint32_t tick, int32_t mapNumber);
        void drawAbove(uint32_t tick, int32_t mapNumber);
        void update(uint32_t tick);
};
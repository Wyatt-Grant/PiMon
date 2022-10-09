#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "engine/Player.hpp"

using namespace picosystem;

class Teleporter {       
    private:
        int32_t teleportTimer;
        bool teleporting;
        Direction nextPlayerDir;
        Point nextPos;
        int32_t nextMap;
        const uint32_t teleportTime = 8; // can be instant but it feels weird

        void teleport(uint32_t newMap, int32_t newX, int32_t newY, Direction dir);

    public:
        Teleporter();
        void draw(uint32_t tick, Player *player);
        void update(uint32_t tick);
};
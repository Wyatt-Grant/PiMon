#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "engine/Npc.hpp"
#include "engine/Message.hpp"

using namespace picosystem;

class Player {       
    private:
        int32_t offsetTileX;
        int32_t offsetTileY;
        int32_t movingOffsetX;
        int32_t movingOffsetY;
        bool isAligned;
        bool isMoving;
        bool canMoveDown;
        bool canMoveUp;
        bool canMoveLeft;
        bool canMoveRight;

        void handleMovement();
        void updateMovementAvailability(const int16_t colliders[][160], std::vector<Npc*> npcs);
        void handleGrass(const int16_t colliders[][160]);
        bool willActorsIntersect(Npc *npc, Direction d);
        void setBuffer();
        void handleTalkToNpcs(std::vector<Npc*> npcs, Message *message);
        
    public:
        Point position;
        Direction direction;
        bool inGrass;

        Player(int32_t x, int32_t y);
        void draw(uint32_t tick);
        void update(uint32_t tick, int32_t mapNumber, std::vector<Npc*> npcs, Message *message);
};
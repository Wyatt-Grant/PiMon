#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "engine/Npc.hpp"

using namespace picosystem;

class StarterPicker {       
    private:
        int8_t dexIndex;
        int8_t dexOffset;
        bool heldUp;
        bool heldDown;
        int16_t heldCounter;

    public:
        bool waitForOpenAnimation;
        bool waitForCloseAnimation;
        int8_t animX;

        StarterPicker();
        void draw(uint32_t tick);
        void update(uint32_t tick, std::vector<Npc*> npcs);
};
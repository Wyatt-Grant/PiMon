#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

using namespace picosystem;

class Dex {       
    private:
        int8_t dexIndex;
        int8_t dexOffset;
        bool heldUp;
        bool heldDown;
        int16_t heldCounter;

    public:
        bool closing;
        bool pressedBack;

        //anim
        int8_t animX;
        bool waitForOpenAnimation;
        bool waitForCloseAnimation;

        Dex();
        void draw(uint32_t tick);
        void update(uint32_t tick);
};
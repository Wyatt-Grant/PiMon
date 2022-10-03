#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

using namespace picosystem;

class Settings {       
    private:
        int8_t menuIndex;
        bool heldRight;
        bool heldLeft;
        int16_t heldCounter;

    public:
        bool closing;
        bool pressedBack;

        //anim
        int8_t animX;
        bool waitForOpenAnimation;
        bool waitForCloseAnimation;

        Settings();
        void draw(uint32_t tick);
        void update(uint32_t tick);
};
#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

using namespace picosystem;

class Party {       
    private:

    public:
        bool closing;
        bool pressedBack;

        //anim
        int8_t animX;
        bool waitForOpenAnimation;
        bool waitForCloseAnimation;

        Party();
        void draw(uint32_t tick);
        void update(uint32_t tick);
};
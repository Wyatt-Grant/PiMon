#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

using namespace picosystem;

class BaseMenu {       
    private:

    public:
        int8_t width;
        int8_t height;
        int8_t animX;
        bool closing;
        bool pressedBack;
        bool waitForOpenAnimation;
        bool waitForCloseAnimation;

        BaseMenu(int32_t w, int32_t h);
        void draw(uint32_t tick);
        void update(uint32_t tick);
        void close();
};
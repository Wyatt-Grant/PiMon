#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "BaseMenu.hpp"

using namespace picosystem;

class Dex : public BaseMenu {       
    private:
        int8_t dexIndex;
        int8_t dexOffset;
        bool heldUp;
        bool heldDown;
        int16_t heldCounter;

    public:
        Dex();
        void draw(uint32_t tick);
        void update(uint32_t tick);
};
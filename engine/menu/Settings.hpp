#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "BaseMenu.hpp"

using namespace picosystem;

class Settings : public BaseMenu {
    private:
        int8_t menuIndex;
        int8_t heldCounter;
        bool heldRight;
        bool heldLeft;

    public:
        Settings();
        void draw(uint32_t tick);
        void update(uint32_t tick);
};
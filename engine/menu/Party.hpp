#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "BaseMenu.hpp"

using namespace picosystem;

class Party : public BaseMenu {       
    private:
        int8_t partySwitch;

    public:
        int8_t menuIndex;

        Party();
        void draw(uint32_t tick);
        void update(uint32_t tick);
};
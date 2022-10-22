#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "engine/menu/Party.hpp"
#include "engine/Message.hpp"
#include "BaseMenu.hpp"

using namespace picosystem;

class Bag : public BaseMenu {       
    private:
        int8_t menuIndex;
        int8_t counter;

    public:
        Party *partyMenu;
        bool partyOpen;
        int8_t selected;

        Bag();
        void draw(uint32_t tick);
        void update(uint32_t tick, Message *message);
};
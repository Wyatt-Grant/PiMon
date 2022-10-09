#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "engine/menu/Party.hpp"
#include "engine/Message.hpp"

using namespace picosystem;

class Bag {       
    private:
        int8_t menuIndex;
        int8_t counter;

    public:
        Party *partyMenu;
        bool closing;
        bool pressedBack;
        bool partyOpen;
        int8_t selected;

        //anim
        int8_t animX;
        bool waitForOpenAnimation;
        bool waitForCloseAnimation;

        Bag();
        void draw(uint32_t tick);
        void update(uint32_t tick, Message *message);
};
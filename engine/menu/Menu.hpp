#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

#include "engine/Message.hpp"

#include "engine/menu/Bag.hpp"
#include "engine/menu/Dex.hpp"
#include "engine/menu/TownMap.hpp"
#include "engine/menu/Party.hpp"
#include "engine/menu/Settings.hpp"
#include "engine/menu/Stats.hpp"

using namespace picosystem;

class Menu {       
    private:
        enum SCENE {
            MENU_BASE,
            MENU_BAG,
            MENU_STATS,
            MENU_MAP,
            MENU_DEX,
            MENU_PARTY,
            MENU_SAVE,
            MENU_SETTINGS,
            MENU_EXIT,
        };
        SCENE scene;
        int8_t menuIndex;

        Bag *bag;
        Dex *dex;
        TownMap *townMap;
        Party *party;
        Settings *settings;
        Stats *stats;

        //anim
        int8_t animX;
        bool waitForOpenAnimation;
        bool waitForCloseAnimation;

        void updateBase(uint32_t tick, Message *message);
        void drawBase(uint32_t tick);
        void handleOpenClose();

    public:
        Menu();
        void draw(uint32_t tick);
        void update(uint32_t tick, Message *message);
};
#include <picosystem.hpp>
#include <pico/multicore.h>
#include <cstring>
#include <math.h>

#include "types.hpp"
#include "globals.hpp"

#include "Util.cpp"
#include "engine/Map.hpp"
#include "engine/Player.hpp"
#include "engine/Npc.hpp"
#include "engine/Message.hpp"
#include "engine/Battle.hpp"
#include "engine/TitleScreen.hpp"
#include "engine/menu/Menu.hpp"

using namespace picosystem;
using namespace std::placeholders;

// Scene vars
Map *map;
Player *player;
std::vector<Npc*> npcs;
Message *message;
Battle *battle;
TitleScreen *titleScreen;
Menu *menu;

void init() {
    blend(MASK);
    backlight(bright);

    player = new Player(52, 52);
    map = new Map();
    message = new Message();
    battle = new Battle();
    titleScreen = new TitleScreen();
    menu = new Menu();

    party.push_back({ 1, 20, getMaxHp(1, xpToLvl(30)), 0 });
    party.push_back({ 3, 90, getMaxHp(3, xpToLvl(90)), 0 });
    party.push_back({ 21, 50000, getMaxHp(21, xpToLvl(500)), 0 });

    // npc set up
    npcs.push_back(new Npc(84, 52, npc_1_overworld_buffer, npc_1_front_buffer, down));
    npcs.at(0)->addMessage({ "Hey PLAYER!", 0 });
    npcs.at(0)->addMessage({ "Let's have a battle!", 0, []() -> void {
        startBattle(); 
        enemyParty.clear();
        enemyParty.push_back({ 17, 20, getMaxHp(17, xpToLvl(20)), 0 });
        enemyParty.push_back({ 15, 40, getMaxHp(15, xpToLvl(40)), 0 });
    }});

    npcs.push_back(new Npc(116, 52, npc_2_overworld_buffer, npc_2_front_buffer, down));
    npcs.at(1)->addMessage({ "Hey PLAYER!", 0 });
    npcs.at(1)->addMessage({ "Let's not battle.", 0, []() -> void { return; } });

    // music
    multicore_launch_core1(playMusic);
}

void update(uint32_t tick) {
    forceDrawMap = false;

    switch (MainScene) {
        case TITLE_SCREEN:
            titleScreen->update(tick);
            break;
        case NEWGAME_INTRO:
            break;
        case OVERWORLD:
            if (!menuOpen) {
                player->update(tick, 1, npcs, message);
                map->update(tick);
                for (auto &npc : npcs) npc->update(tick, 1);
            }
            menu->update(tick, message);
            message->update(tick);
            break;
        case BATTLE:
            battle->update(tick, message);
            message->update(tick);
            break;
    }
}

void draw(uint32_t tick) {
    switch (MainScene) {
        case TITLE_SCREEN:
            titleScreen->draw(tick);
            break;
        case NEWGAME_INTRO:
            break;
        case OVERWORLD:
            if (!menuOpen || forceDrawMap) {
                map->draw(tick, 1);
                player->draw(tick);
                map->drawAbove(tick, 1);
                for (auto &npc : npcs) npc->draw(tick);
            }
            menu->draw(tick);
            message->draw(tick);
            break;
        case BATTLE:
            if (battleTransitionDone()) {
                battle->draw(tick);
                message->draw(tick);
            }
            break;
    }
}
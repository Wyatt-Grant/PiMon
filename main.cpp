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
#include "engine/LoadGame.hpp"
#include "engine/NewGame.hpp"
#include "engine/Teleporter.hpp"
#include "engine/StarterPicker.hpp"
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
LoadGame *loadGame;
NewGame *newGame;
Menu *menu;
Teleporter *teleporter;
StarterPicker *starterPicker;

void init() {
    blend(MASK);
    backlight(bright);

    virtualCamera = {-240, -208};
    currentMap = 0;

    player = new Player(52, 52);
    map = new Map();
    message = new Message();
    battle = new Battle();
    titleScreen = new TitleScreen();
    loadGame = new LoadGame();
    newGame = new NewGame();
    menu = new Menu();
    teleporter = new Teleporter();
    starterPicker = new StarterPicker();

    party.push_back({ 9, 10, getMaxHp(9, xpToLvl(10)), 0 });
    party.push_back({ 3, 90, getMaxHp(3, xpToLvl(90)), 0 });
    party.push_back({ 21, 50000, getMaxHp(21, xpToLvl(500)) - 25, 0 });

    //signs
    npcs.push_back(new Npc(84, 116, npc_1_overworld_buffer, npc_1_front_buffer, down, false, 1));
    npcs.at(0)->addMessage({ "PLAYER's house", 0, []() -> void { return; } });
    npcs.push_back(new Npc(212, 116, npc_1_overworld_buffer, npc_1_front_buffer, down, false,1 ));
    npcs.at(1)->addMessage({ "RIVAL's house", 0, []() -> void { return; } });
    npcs.push_back(new Npc(116, 164, npc_1_overworld_buffer, npc_1_front_buffer, down, false,1 ));
    npcs.at(2)->addMessage({ "Oakville", 0, []() -> void { return; } });
    npcs.push_back(new Npc(196, 212, npc_1_overworld_buffer, npc_1_front_buffer, down, false, 1));
    npcs.at(3)->addMessage({ "Dr Pine's Research\nfacility", 0, []() -> void { return; } });
    npcs.push_back(new Npc(52, 980, npc_1_overworld_buffer, npc_1_front_buffer, down, false, 1));
    npcs.at(4)->addMessage({ "Austin's House", 0, []() -> void { return; } });
    npcs.push_back(new Npc(52, 1076, npc_1_overworld_buffer, npc_1_front_buffer, down, false,1 ));
    npcs.at(5)->addMessage({ "Nixon's House", 0, []() -> void { return; } });
    npcs.push_back(new Npc(260, 980, npc_1_overworld_buffer, npc_1_front_buffer, down, false, 1));
    npcs.at(6)->addMessage({ "Clinic", 0, []() -> void { return; } });
    npcs.push_back(new Npc(260, 1076, npc_1_overworld_buffer, npc_1_front_buffer, down, false, 1));
    npcs.at(7)->addMessage({ "Dojo", 0, []() -> void { return; } });

    // trainers
    npcs.push_back(new Npc(516, 100, npc_4_overworld_buffer, npc_4_front_buffer, down, true, 1));
    npcs.at(8)->addMessage({ "Hi PLAYER!", 0 });
    npcs.at(8)->addMessage({ "Let's have a battle!", 0, []() -> void {
        startBattle();
        isWildBattle = false;
        freePartyFromMemory(enemyParty);
        enemyParty.push_back({ 9, 20, getMaxHp(9, xpToLvl(20)), 0 });
    }});

    npcs.push_back(new Npc(532, 324, npc_11_overworld_buffer, npc_11_front_buffer, left, true, 1));
    npcs.at(9)->addMessage({ "Hey PLAYER!", 0 });
    npcs.at(9)->addMessage({ "Let's battle!", 0, []() -> void {
        startBattle();
        isWildBattle = false;
        freePartyFromMemory(enemyParty);
        enemyParty.push_back({ 5, 300, getMaxHp(5, xpToLvl(300)), 0 });
        enemyParty.push_back({ 7, 400, getMaxHp(7, xpToLvl(400)), 0 });
    }});

    npcs.push_back(new Npc(276, 372, npc_6_overworld_buffer, npc_6_front_buffer, down, true, 1));
    npcs.at(10)->addMessage({ "Yo PLAYER!", 0 });
    npcs.at(10)->addMessage({ "you're going down!", 0, []() -> void {
        startBattle();
        isWildBattle = false;
        freePartyFromMemory(enemyParty);
        enemyParty.push_back({ 9, 2000, getMaxHp(9, xpToLvl(2000)), 0 });
        enemyParty.push_back({ 11, 2000, getMaxHp(11, xpToLvl(2000)), 0 });
    }});

    npcs.push_back(new Npc(132, 532, npc_7_overworld_buffer, npc_7_front_buffer, left, true, 1));
    npcs.at(11)->addMessage({ "Sup PLAYER!", 0 });
    npcs.at(11)->addMessage({ "fight time!", 0, []() -> void {
        startBattle();
        isWildBattle = false;
        freePartyFromMemory(enemyParty);
        enemyParty.push_back({ 13, 10000, getMaxHp(13, xpToLvl(10000)), 0 });
        enemyParty.push_back({ 15, 10000, getMaxHp(15, xpToLvl(10000)), 0 });
    }});

    npcs.push_back(new Npc(52, 676, npc_8_overworld_buffer, npc_8_front_buffer, down, true, 1));
    npcs.at(12)->addMessage({ "Hey PLAYER!", 0 });
    npcs.at(12)->addMessage({ "you look weak!", 0, []() -> void {
        startBattle();
        isWildBattle = false;
        freePartyFromMemory(enemyParty);
        enemyParty.push_back({ 17, 10000, getMaxHp(17, xpToLvl(10000)), 0 });
        enemyParty.push_back({ 19, 10000, getMaxHp(19, xpToLvl(10000)), 0 });
        enemyParty.push_back({ 21, 10000, getMaxHp(21, xpToLvl(10000)), 0 });
    }});

    //town 1 outside npc
    npcs.push_back(new Npc(340, 132, npc_4_overworld_buffer, npc_4_front_buffer, down, true, 1));
    npcs.at(13)->addMessage({ "It's dangerous to\nleave without a\nPiMon!", 0, []() -> void { return; } });

    //town 1 inside npc
    npcs.push_back(new Npc(84, 116, npc_3_overworld_buffer, npc_3_front_buffer, up, true, 0));
    npcs.at(14)->addMessage({ "Hey PLAYER\nyou and RIVAL\nare so competitive!", 0, []() -> void { return; } });

    npcs.push_back(new Npc(84, 292, npc_3_overworld_buffer, npc_3_front_buffer, up, true, 0));
    npcs.at(15)->addMessage({ "Hey PLAYER\nDr. Pine was looking\nfor you!", 0, []() -> void { return; } });

    npcs.push_back(new Npc(276, 84, npc_2_overworld_buffer, npc_2_front_buffer, down, true, 0));
    npcs.at(16)->addMessage({ "Hey Dweeb", 0, []() -> void { return; } });

    npcs.push_back(new Npc(180, 436, npc_1_overworld_buffer, npc_1_front_buffer, up, true, 0));
    npcs.at(17)->addMessage({ "Hey PLAYER, which\npimon do you want?", 0, []() -> void {
        pickingStarter = true;
        starterPicker->waitForOpenAnimation = true;
        starterPicker->animX = 120;
    } });

    //town 2 outside
    npcs.push_back(new Npc(116, 644, npc_9_overworld_buffer, npc_9_front_buffer, up, true, 0));
    npcs.at(18)->addMessage({ "Hey, i'm just chilling.", 0, []() -> void { return; } });

    npcs.push_back(new Npc(116, 820, npc_10_overworld_buffer, npc_10_front_buffer, up, true, 0));
    npcs.at(19)->addMessage({ "Hey, i'm just chilling.", 0, []() -> void { return; } });

    npcs.push_back(new Npc(372, 660, npc_5_overworld_buffer, npc_5_front_buffer, down, true, 0));
    npcs.at(20)->addMessage({ "Hey PLAYER!\nLet me heal your\nPiMon!", 0, []() -> void {
        for (auto &tpimon : party) {
            tpimon.hp = getMaxHp(tpimon.pimon_id, xpToLvl(tpimon.xp));
        }
    }});

    npcs.push_back(new Npc(388, 836, npc_10_overworld_buffer, npc_10_front_buffer, down, true, 0));
    npcs.at(21)->addMessage({ "Hey PLAYER!", 0 });
    npcs.at(21)->addMessage({ "I'm the dojo leader!\nlet's fight!", 0, []() -> void {
        startBattle();
        isWildBattle = false;
        freePartyFromMemory(enemyParty);
        enemyParty.push_back({ 23, 10000, getMaxHp(23, xpToLvl(15000)), 0 });
        enemyParty.push_back({ 3, 10000, getMaxHp(3, xpToLvl(15000)), 0 });
        enemyParty.push_back({ 13, 10000, getMaxHp(13, xpToLvl(15000)), 0 });
    }});

    // music handled on its own core
    multicore_launch_core1(playMusic);
}

void update(uint32_t tick) {
    forceDrawMap = false;

    switch (MainScene) {
        case TITLE_SCREEN:
            titleScreen->update(tick);
            break;
        case LOAD_GAME:
            loadGame->update(tick);
            break;
        case NEW_GAME:
            newGame->update(tick, message);
            message->update(tick);
            break;
        case OVERWORLD:
            if ((!menuOpen && !pickingStarter) || forceDrawMap) {
                player->update(tick, currentMap, npcs, message);
                map->update(tick);
                for (auto &npc : npcs) {
                    if (npc->map == currentMap) npc->update(tick, 1);
                }
                teleporter->update(tick);
            }
            if(pickingStarter || starterPicker->waitForCloseAnimation || starterPicker->waitForOpenAnimation) starterPicker->update(tick, npcs);
            menu->update(tick, message);
            message->update(tick);
            break;
        case BATTLE:
            battle->update(tick, message, menu, player);
            message->update(tick);
            break;
    }
}

void draw(uint32_t tick) {
    switch (MainScene) {
        case TITLE_SCREEN:
            titleScreen->draw(tick);
            break;
        case LOAD_GAME:
            loadGame->draw(tick);
            break;
        case NEW_GAME:
            newGame->draw(tick);
            message->draw(tick);
            break;
        case OVERWORLD:
            if ((!menuOpen && !pickingStarter) || forceDrawMap) {
                map->draw(tick, currentMap);
                player->draw(tick);
                map->drawAbove(tick, currentMap);
                for (auto &npc : npcs) {
                    if (npc->map == currentMap) npc->draw(tick);
                }
                teleporter->draw(tick, player);
            }
            if(pickingStarter || starterPicker->waitForCloseAnimation || starterPicker->waitForOpenAnimation) starterPicker->draw(tick);
            menu->draw(tick);
            message->draw(tick);
            break;
        case BATTLE:
            if (battleTransitionDone()) {
                battle->draw(tick, menu);
                message->draw(tick);
            }
            break;
    }

    // pen(15,15,15);
    // frect(0,112,120,9);
    // pen(0,0,0);
    // // text(str((virtualCamera.x - 52) * -1), 0, 112);
    // // text(str((virtualCamera.y - 52) * -1), 60, 112);
    // text(str(virtualCamera.x), 0, 112);
    // text(str(virtualCamera.y), 60, 112);
}
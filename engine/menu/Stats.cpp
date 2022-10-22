#include "engine/menu/Stats.hpp"

Stats::Stats() : BaseMenu(56, 86) {
    
}

void Stats::update(uint32_t tick) {
    BaseMenu::update(tick);
}

void Stats::draw(uint32_t tick) {
    BaseMenu::draw(tick);

    std::string setting;

    text("Name:", animX+4, 4 + (0 * 16));
    text(playerName, animX+10, 4 + (0 * 16) + 8);

    text("Money:", animX+4, 4 + (1 * 16));
    text(str(cashMoney), animX+10, 4 + (1 * 16) + 8);

    text("Patches:", animX+4, 4 + (2 * 16));
    text(str(patches), animX+10, 4 + (2 * 16) + 8);

    text("PiDex:" , animX+4, 4 + (3 * 16));
    int32_t caughtCount = 0;
    for (int32_t i; i < 24; i++) {
        if (caughtPimon[i]) caughtCount++;
    }
    text(str(caughtCount), animX+10, 4 + (3 * 16) + 8);

    std::string gameTimeString = "";
    uint32_t cTime = gameTime + time();
    if (cTime/(1000 * 3600) < 10) {
        gameTimeString.append("0");
    }
    gameTimeString.append(str(cTime/(1000 * 3600)));
    gameTimeString.append(":");
    if ((cTime/(1000 * 60) % 60) < 10) {
        gameTimeString.append("0");
    }
    gameTimeString.append(str((cTime/(1000 * 60) % 60)));
    gameTimeString.append(":");
    if ((cTime/(1000) % 60) < 10) {
        gameTimeString.append("0");
    }
    gameTimeString.append(str((cTime/(1000)) % 60));

    text("Time" , animX+4, 4 + (4 * 16));
    text(gameTimeString, animX+10, 4 + (4 * 16) + 8);
}
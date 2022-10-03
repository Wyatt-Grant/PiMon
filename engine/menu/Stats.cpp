#include "engine/menu/Stats.hpp"

Stats::Stats() {
    closing = true;
    animX = 120;
    waitForOpenAnimation = false;
    waitForCloseAnimation = false;
    pressedBack = false;
}

void Stats::update(uint32_t tick) {
    closing = false;
    if (pressed(B)) {
        waitForOpenAnimation = false;
        waitForCloseAnimation = true;
        pressedBack = true;
    }

    if (waitForOpenAnimation && animX > 64) {
        animX -= 8;
        if (animX < 64) animX = 64; 
    } else if (waitForCloseAnimation && animX < 120) {
        forceDrawMap = true;
        animX += 8;
        if (animX > 120) animX = 120; 
        if (animX == 120) {
            waitForCloseAnimation = false;
        }
    }

    if (pressedBack) {
        closing = true;
        pressedBack = false;
    }
}

void Stats::draw(uint32_t tick) {
    drawWindow(animX, 0, 56, 86);
    std::string setting;

    text("Name:", animX+4, 4 + (0 * 16));
    text(playerName, animX+10, 4 + (0 * 16) + 8);

    text("Money:", animX+4, 4 + (1 * 16));
    text(str(cashMoney), animX+10, 4 + (1 * 16) + 8);

    text("Patches:", animX+4, 4 + (2 * 16));
    text(str(patches), animX+10, 4 + (2 * 16) + 8);

    text("PiDex:" , animX+4, 4 + (3 * 16));
    text(str(patches), animX+10, 4 + (3 * 16) + 8);

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
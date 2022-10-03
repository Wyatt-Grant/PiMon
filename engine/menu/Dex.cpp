#include "engine/menu/Dex.hpp"

Dex::Dex() {
    closing = true;
    animX = 120;
    waitForOpenAnimation = false;
    waitForCloseAnimation = false;
    pressedBack = false;
}

void Dex::update(uint32_t tick) {
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

void Dex::draw(uint32_t tick) {
    drawWindow(animX, 0, 56, 86);
    text("Dex", animX + 4, 4);
}
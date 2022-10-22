#include "engine/menu/BaseMenu.hpp"

BaseMenu::BaseMenu(int32_t w,int32_t h) {
    closing = true;
    animX = 120;
    width = w;
    height = h;
    waitForOpenAnimation = false;
    waitForCloseAnimation = false;
    pressedBack = false;
}

void BaseMenu::close() {
    waitForOpenAnimation = false;
    waitForCloseAnimation = true;
    pressedBack = true;
}

void BaseMenu::update(uint32_t tick) {
    closing = false;
    if (pressed(B)) {
        close();
    }

    if (waitForOpenAnimation && animX > (120 - width)) {
        animX -= 8;
        if (animX < (120 - width)) animX = (120 - width); 
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

void BaseMenu::draw(uint32_t tick) {
    drawWindow(animX, 0, width, height);
}
#include "engine/menu/Dex.hpp"

Dex::Dex() {
    closing = true;
    animX = 120;
    waitForOpenAnimation = false;
    waitForCloseAnimation = false;
    pressedBack = false;
    dexIndex = 0;
    dexOffset = 0;
    heldUp = false;
    heldDown = false;
    heldCounter = 0;
}

void Dex::update(uint32_t tick) {
    closing = false;
    if (pressed(B)) {
        waitForOpenAnimation = false;
        waitForCloseAnimation = true;
        pressedBack = true;
    }

    if (waitForOpenAnimation && animX > 60) {
        animX -= 8;
        if (animX < 60) animX = 60; 
    } else if (waitForCloseAnimation && animX < 120) {
        forceDrawMap = true;
        animX += 8;
        if (animX > 120) animX = 120; 
        if (animX == 120) {
            waitForCloseAnimation = false;
            dexIndex = 0;
            dexOffset = 0;
        }
    }

    if (pressedBack) {
        closing = true;
        pressedBack = false;
    }

    if (pressed(UP) || heldUp) {
        if (dexIndex > 0) {
            dexIndex -= 1;
        } else {
            if (dexOffset > 0) {
                dexOffset -= 1;
            } 
        }
    }
    if (pressed(DOWN) || heldDown) {
        if (dexIndex < 2) {
            dexIndex += 1;
        } else {
            if (dexOffset < 21) {
                dexOffset += 1;
            } 
        }
    }

    if (button(UP)) {
        heldCounter += 1;
        if (heldCounter > 10) {
            heldUp = true;
        }
    } else if (button(DOWN)) {
        heldCounter += 1;
        if (heldCounter > 10) {
            heldDown = true;
        }
    } else {
        heldCounter = 0;
        heldUp = false;
        heldDown = false;
    }
}

void Dex::draw(uint32_t tick) {
    drawWindow(animX, 0, 60, 86);

    setPimonBuffer(dexOffset+dexIndex + 1);
    if (caughtPimon[dexOffset+dexIndex]) {
        text("c", 112, 4);
    }
    draw56sprite(animX + 2, 2);

    for (int32_t i = 0; i < 3; i++) {
        text(genericPimonData[dexOffset + i].name, animX + 8, 60 + (i * 8));
    }

    hline(animX+2, 58, 56);

    vline(animX+3, 56 + (dexIndex * 8) + 3, 8);
    vline(animX+4, 57 + (dexIndex * 8) + 3, 6);
    vline(animX+5, 58 + (dexIndex * 8) + 3, 4);
    vline(animX+6, 59 + (dexIndex * 8) + 3, 2);
}
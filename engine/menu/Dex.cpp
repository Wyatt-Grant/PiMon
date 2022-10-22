#include "engine/menu/Dex.hpp"

Dex::Dex() : BaseMenu(60, 86) {
    dexIndex = 0;
    dexOffset = 0;
    heldUp = false;
    heldDown = false;
    heldCounter = 0;
}

void Dex::update(uint32_t tick) {
    BaseMenu::update(tick);

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
    BaseMenu::draw(tick);

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
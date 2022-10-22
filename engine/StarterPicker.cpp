#include "engine/StarterPicker.hpp"

StarterPicker::StarterPicker() {
    animX = 120;
    waitForOpenAnimation = false;
    waitForCloseAnimation = false;
    dexIndex = 0;
    dexOffset = 0;
    heldUp = false;
    heldDown = false;
    heldCounter = 0;
}

void StarterPicker::update(uint32_t tick, std::vector<Npc*> npcs) {
    if (pressed(A)) {
        waitForOpenAnimation = false;
        waitForCloseAnimation = true;
        pickingStarter = false;
        int32_t chosen = (2*(dexOffset+dexIndex)) + 1;
        party.push_back({ chosen, 2, getMaxHp(chosen, xpToLvl(2)), 0 });
        playerStarter = chosen;
        freeMessagesFromMemory(npcs.at(17)->messages);
        npcs.at(17)->addMessage({ "Hey PLAYER\nI hope you enjoy\nyour PiMon!", 0, []() -> void { return; } });
        caughtPimon[chosen-1] = true;
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
            dexIndex = 0;
            dexOffset = 0;
        }
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
            if (dexOffset < 9) {
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

void StarterPicker::draw(uint32_t tick) {
    drawWindow(animX, 0, 60, 86);

    setPimonBuffer((2*(dexOffset+dexIndex)) + 1);
    draw56sprite(animX + 2, 2);

    for (int32_t i = 0; i < 3; i++) {
        text(genericPimonData[(2*(dexOffset+i))].name, animX + 8, 60 + (i * 8));
    }

    hline(animX+2, 58, 56);

    vline(animX+3, 56 + (dexIndex * 8) + 3, 8);
    vline(animX+4, 57 + (dexIndex * 8) + 3, 6);
    vline(animX+5, 58 + (dexIndex * 8) + 3, 4);
    vline(animX+6, 59 + (dexIndex * 8) + 3, 2);
}
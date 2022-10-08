#include "engine/menu/Bag.hpp"

Bag::Bag() {
    closing = true;
    animX = 120;
    waitForOpenAnimation = false;
    waitForCloseAnimation = false;
    pressedBack = false;
    menuIndex = 0;
    counter = 0;
}

void Bag::update(uint32_t tick) {
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
            menuIndex = 0;
        }
    }

    if (pressedBack) {
        closing = true;
        pressedBack = false;
    }

    counter = 0;
    int8_t counts[] = {potion, elixer, emerald, diamond, ruby, coffee, cure, icePack};
    for (int8_t i = 0; i < 8; i++) {
        if (counts[i] > 0) {
            counter += 1;
        }
    }

    if (pressed(UP)) {
        if (menuIndex > 0) {
            menuIndex -= 1;
        }
    }
    if (pressed(DOWN)) {
        if (menuIndex < counter-1) {
            menuIndex += 1;
        }
    }
}

void Bag::draw(uint32_t tick) {
    drawWindow(animX, 0, 56, 86);

    pen(themeR,themeG,themeB);
    std::string names[] = {"Potion","Elixer","Emerald","Diamond","Ruby","Coffee","Cure","IcePack"};
    int8_t counts[] = {potion, elixer, emerald, diamond, ruby, coffee, cure, icePack};
    counter = 0;
    for (int8_t i = 0; i < 8; i++) {
        if (counter == menuIndex) {
            selected = i;
        }
        if (counts[i] > 0) {
            text(names[i], animX + 10, 3 + (counter * 8));
            counter += 1;
        }
    }

    frect(animX+2, 0 + (8 * 8) + 3, 52, 17);

    vline(animX+4, 0 + (menuIndex * 8) + 3, 8);
    vline(animX+5, 1 + (menuIndex * 8) + 3, 6);
    vline(animX+6, 2 + (menuIndex * 8) + 3, 4);
    vline(animX+7, 3 + (menuIndex * 8) + 3, 2);

    pen(15,15,15);
    switch(selected) {
        case 0:
            text("heals\n20hp", animX + 4, 4 + (8 * 8));
            text("x", animX + 41, 4 + (9 * 8));
            text(str((int32_t) potion), animX + 48, 4 + (9 * 8));
            break;
        case 1:
            text("heals all\nhp", animX + 4, 4 + (8 * 8));
            text("x", animX + 41, 4 + (9 * 8));
            text(str((int32_t) elixer), animX + 48, 4 + (9 * 8));
            break;
        case 2:
            text("used to\ncatch", animX + 4, 4 + (8 * 8));
            text("x", animX + 41, 4 + (9 * 8));
            text(str((int32_t) emerald), animX + 48, 4 + (9 * 8));
            break;
        case 3:
            text("used to\ncatch", animX + 4, 4 + (8 * 8));
            text("x", animX + 41, 4 + (9 * 8));
            text(str((int32_t) diamond), animX + 48, 4 + (9 * 8));
            break;
        case 4:
            text("used to\ncatch", animX + 4, 4 + (8 * 8));
            text("x", animX + 41, 4 + (9 * 8));
            text(str((int32_t) ruby), animX + 48, 4 + (9 * 8));
            break;
        case 5:
            text("heals\nsleep", animX + 4, 4 + (8 * 8));
            text("x", animX + 41, 4 + (9 * 8));
            text(str((int32_t) coffee), animX + 48, 4 + (9 * 8));
            break;
        case 6:
            text("heals\npoison", animX + 4, 4 + (8 * 8));
            text("x", animX + 41, 4 + (9 * 8));
            text(str((int32_t) cure), animX + 48, 4 + (9 * 8));
            break;
        case 7:
            text("heals\nburn", animX + 4, 4 + (8 * 8));
            text("x", animX + 41, 4 + (9 * 8));
            text(str((int32_t) icePack), animX + 48, 4 + (9 * 8));
            break;
    }
}
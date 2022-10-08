#include "engine/menu/Menu.hpp"

Menu::Menu() {
    scene = MENU_BASE;
    menuIndex = 0;
    animX = 120;
    waitForOpenAnimation = false;
    waitForCloseAnimation = false;

    bag = new Bag();
    dex = new Dex();
    townMap = new TownMap();
    party = new Party();
    settings = new Settings();
    stats = new Stats();
}

void Menu::updateBase(uint32_t tick, Message *message) {
    if (pressed(UP) && !waiting) {
        if (menuIndex > 0) {
            menuIndex -= 1;
        }
    }
    if (pressed(DOWN) && !waiting) {
        if (menuIndex < 7) {
            menuIndex += 1;
        }
    }
    if (pressed(A) && !waiting) {
        switch(menuIndex) {
            case 0:
                dex->waitForOpenAnimation = true;
                dex->animX = 120;
                scene = MENU_DEX;
                break;
            case 1:
                party->waitForOpenAnimation = true;
                party->animX = 120;
                scene = MENU_PARTY;
                break;
            case 2:
                bag->waitForOpenAnimation = true;
                bag->animX = 120;
                scene = MENU_BAG;
                break;
            case 3:
                townMap->waitForOpenAnimation = true;
                townMap->animX = 120;
                scene = MENU_MAP;
                break;
            case 4:
                stats->waitForOpenAnimation = true;
                stats->animX = 120;
                scene = MENU_STATS;
                break;
            case 5:
                message->showMessage("Saving not done!");
                // menuOpen = false;
                // waitForOpenAnimation = false;
                // waitForCloseAnimation = true;
                break;
            case 6:
                settings->waitForOpenAnimation = true;
                settings->animX = 120;
                scene = MENU_SETTINGS;
                // waitForOpenAnimation = false;
                // waitForCloseAnimation = true;
                break;
            case 7:
                menuOpen = false;
                waitForOpenAnimation = false;
                waitForCloseAnimation = true;
                break;
        }
    }
}

void Menu::drawBase(uint32_t tick) {
    drawWindow(animX, 0, 56, 71);

    pen(themeR,themeG,themeB);
    text("PiDex", animX+10, 4);
    text("PiMon", animX+10, 12);
    text("Bag", animX+10, 20);
    text("Map", animX+10, 28);
    text("Stats", animX+10, 36);
    text("Save", animX+10, 44);
    text("Settings", animX+10, 52);
    text("Exit", animX+10, 60);

    vline(animX+4, 0 + (menuIndex * 8) + 4, 8);
    vline(animX+5, 1 + (menuIndex * 8) + 4, 6);
    vline(animX+6, 2 + (menuIndex * 8) + 4, 4);
    vline(animX+7, 3 + (menuIndex * 8) + 4, 2);
}

void Menu::handleOpenClose() {
    bool isAligned = virtualCamera.y % 16 == 0 && virtualCamera.x % 16 == 0;
    if (pressed(X) && isAligned && scene == MENU_BASE) {
        menuIndex = 0;
        scene = MENU_BASE;
        menuOpen = !menuOpen;
        waitForOpenAnimation = menuOpen;
        waitForCloseAnimation = !menuOpen;
    }

    if (pressed(B) && scene == MENU_BASE) {
        if (menuOpen) {
            menuOpen = false;
            waitForOpenAnimation = false;
            waitForCloseAnimation = true;
        }
    }

    if (waitForOpenAnimation && animX > 64) {
        animX -= 8;
        if (animX < 64) animX = 64; 
    } else if (waitForCloseAnimation && animX < 120) {
        forceDrawMap = true;
        animX += 8;
        if (animX > 120) {
            animX = 120;
        }
    } else {
        waitForCloseAnimation = false;
        waitForOpenAnimation = false;
    }

    if ((settings->closing && scene == MENU_SETTINGS)
    || (stats->closing && scene == MENU_STATS)
    || (townMap->closing && scene == MENU_MAP)
    || (dex->closing && scene == MENU_DEX)
    || (party->closing && scene == MENU_PARTY)
    || (bag->closing && scene == MENU_BAG)) {
        scene = MENU_BASE;
        waitForOpenAnimation = true;
    }
}

void Menu::update(uint32_t tick, Message *message) {
    handleOpenClose();

    if (menuOpen) {
        switch(scene) {
            case MENU_BASE:
                updateBase(tick, message);
                if (settings->waitForCloseAnimation || settings->waitForOpenAnimation) settings->update(tick);
                if (stats->waitForCloseAnimation || stats->waitForOpenAnimation) stats->update(tick);
                if (townMap->waitForCloseAnimation || townMap->waitForOpenAnimation) townMap->update(tick);
                if (dex->waitForCloseAnimation || dex->waitForOpenAnimation) dex->update(tick);
                if (party->waitForCloseAnimation || party->waitForOpenAnimation) party->update(tick);
                if (bag->waitForCloseAnimation || bag->waitForOpenAnimation) bag->update(tick, message);
                break;
            case MENU_BAG:
                bag->update(tick, message);
                break;
            case MENU_STATS:
                stats->update(tick);
                break;
            case MENU_MAP:
                townMap->update(tick);
                break;
            case MENU_DEX:
                dex->update(tick);
                break;
            case MENU_PARTY:
                party->update(tick);
                break;
            case MENU_SAVE:
                break;
            case MENU_SETTINGS:
                settings->update(tick);
                break;
            case MENU_EXIT:
                break;
        }
    }
}

void Menu::draw(uint32_t tick) {
    if (menuOpen || waitForCloseAnimation) {
        switch(scene) {
            case MENU_BASE:
                drawBase(tick);
                if (settings->waitForCloseAnimation || settings->waitForOpenAnimation) settings->draw(tick);
                if (stats->waitForCloseAnimation || stats->waitForOpenAnimation) stats->draw(tick);
                if (townMap->waitForCloseAnimation || townMap->waitForOpenAnimation) townMap->draw(tick);
                if (dex->waitForCloseAnimation || dex->waitForOpenAnimation) dex->draw(tick);
                if (party->waitForCloseAnimation || party->waitForOpenAnimation) party->draw(tick);
                if (bag->waitForCloseAnimation || bag->waitForOpenAnimation) bag->draw(tick);
                break;
            case MENU_BAG:
                if (waitForCloseAnimation || waitForOpenAnimation) drawBase(tick);
                bag->draw(tick);
                break;
            case MENU_STATS:
                if (waitForCloseAnimation || waitForOpenAnimation) drawBase(tick);
                stats->draw(tick);
                break;
            case MENU_MAP:
                if (waitForCloseAnimation || waitForOpenAnimation) drawBase(tick);
                townMap->draw(tick);
                break;
            case MENU_DEX:
                if (waitForCloseAnimation || waitForOpenAnimation) drawBase(tick);
                dex->draw(tick);
                break;
            case MENU_PARTY:
                if (waitForCloseAnimation || waitForOpenAnimation) drawBase(tick);
                party->draw(tick);
                break;
            case MENU_SAVE:
                break;
            case MENU_SETTINGS:
                if (waitForCloseAnimation || waitForOpenAnimation) drawBase(tick);
                settings->draw(tick);
                break;
            case MENU_EXIT:
                break;
        }
    }
}
#include "engine/menu/Settings.hpp"

Settings::Settings() : BaseMenu(56, 86) {
    menuIndex = 0;
    heldRight = false;
    heldLeft = false;
    heldCounter = 0;
}

void Settings::update(uint32_t tick) {
    BaseMenu::update(tick);

    if (pressed(UP)) {
        if (menuIndex > 0) {
            menuIndex -= 1;
        }
    }
    if (pressed(DOWN)) {
        if (menuIndex < 4) {
            menuIndex += 1;
        }
    }

    if (button(LEFT)) {
        heldCounter += 1;
        if (heldCounter > 10) {
            heldLeft = true;
        }
    } else if (button(RIGHT)) {
        heldCounter += 1;
        if (heldCounter > 10) {
            heldRight = true;
        }
    } else {
        heldCounter = 0;
        heldLeft = false;
        heldRight = false;
    }

    if (pressed(LEFT) || heldLeft) {
        switch(menuIndex) {
            case 0:
                themeR -= 1;
                break;
            case 1:
                themeG -= 1;
                break;
            case 2:
                themeB -= 1;
                break;
            case 3:
                playTick();
                volume -= 1;
                break;
            case 4:
                bright -= 1;
                break;
        }
    }
    if (pressed(RIGHT) || heldRight) {
        switch(menuIndex) {
            case 0:
                if ((themeG + themeB + themeR) < 43) themeR += 1;
                break;
            case 1:
                if ((themeG + themeB + themeR) < 43) themeG += 1;
                break;
            case 2:
                if ((themeG + themeB + themeR) < 43) themeB += 1;
                break;
            case 3:
                playTick();
                volume += 1;
                break;
            case 4:
                bright += 1;
                break;
        }
    }

    if (themeR > 15) {
        themeR = 15;
    }
    if (themeG > 15) {
        themeG = 15;
    }
    if (themeB > 15) {
        themeB = 15;
    }
    if (volume > 100) {
        volume = 100;
    }
    if (bright > 100) {
        bright = 100;
    }
    
    if (themeR < 0) {
        themeR = 0;
    }
    if (themeG < 0) {
        themeG = 0;
    }
    if (themeB < 0) {
        themeB = 0;
    }
    if (volume < 0) {
        volume = 0;
    }
    if (bright < 10) {
        bright = 10;
    }

    backlight(bright);
}

void Settings::draw(uint32_t tick) {
    BaseMenu::draw(tick);

    std::string setting;
    
    text("Theme R", animX+10, 4 + (0 * 16));
    setting = "< "; setting.append(str((int32_t) themeR)); setting.append(" >");
    text(setting, animX+18, 4 + (0 * 16) + 8);

    text("Theme G", animX+10, 4 + (1 * 16));
    setting = "< "; setting.append(str((int32_t) themeG)); setting.append(" >");
    text(setting, animX+18, 4 + (1 * 16) + 8);

    text("Theme B", animX+10, 4 + (2 * 16));
    setting = "< "; setting.append(str((int32_t) themeB)); setting.append(" >");
    text(setting, animX+18, 4 + (2 * 16) + 8);

    text("Volume" , animX+10, 4 + (3 * 16));
    setting = "< "; setting.append(str((int32_t) volume)); setting.append(" >");
    text(setting, animX+18, 4 + (3 * 16) + 8);

    text("Bright" , animX+10, 4 + (4 * 16));
    setting = "< "; setting.append(str((int32_t) bright)); setting.append(" >");
    text(setting, animX+18, 4 + (4 * 16) + 8);

    vline(animX+4, 0 + (menuIndex * 16) + 4, 8);
    vline(animX+5, 1 + (menuIndex * 16) + 4, 6);
    vline(animX+6, 2 + (menuIndex * 16) + 4, 4);
    vline(animX+7, 3 + (menuIndex * 16) + 4, 2);
}
#include "engine/menu/Party.hpp"

Party::Party() : BaseMenu(56, MainScene != BATTLE ? 92 : 83) {
    menuIndex = 0;
    partySwitch = -1;
}

void Party::update(uint32_t tick) {
    if (pressed(UP)) {
        if (menuIndex > 0) {
            menuIndex -= 1;
        }
    }
    if (pressed(DOWN)) {
        if (menuIndex < party.size()-1) {
            menuIndex += 1;
        }
    }

    if (pressed(Y) && MainScene != BATTLE) {
        if (partySwitch == -1) {
            partySwitch = menuIndex;
        } else {
            std::swap(party[partySwitch], party[menuIndex]);
            partySwitch = -1;
        }
}
}

void Party::draw(uint32_t tick) {
    BaseMenu::update(tick);
    
    for (int32_t i = 0; i < party.size(); i++) {
        if (i == partySwitch) {
            frect(animX + 2, (i*26) + 2, 52, 27);
            pen(15,15,15);
        } else if (i == 1) {
            pen(14,14,14);
            frect(animX + 2, (i*26) + 2, 52, 27);
            pen(themeR,themeG,themeB);
        }
        std::string txt = "";
        text(getPimonData(party, i).name, animX + 10, (i*26) + 4);
        txt = "L: ";
        text(txt.append(str(xpToLvl(party.at(i).xp))), animX + 10, (i*26) + 12);
        txt = "";
        txt.append(str(party.at(i).hp));
        txt.append("/");
        txt.append(str(getMaxHp(party.at(i).pimon_id, xpToLvl(party.at(i).xp))));
        text(txt, animX + 10, (i*26) + 20);


        pen(themeR,themeG,themeB);
    }

    if (menuIndex == partySwitch) pen(15,15,15);
    vline(animX+3, (menuIndex * 26) + 4, 8);
    vline(animX+4, (menuIndex * 26) + 5, 6);
    vline(animX+5, (menuIndex * 26) + 6, 4);
    vline(animX+6, (menuIndex * 26) + 7, 2);

    if (MainScene != BATTLE) {
        pen(themeR,themeG,themeB);
        hline(animX+2, 80, 35);
        vline(animX+37, 81, 9);
        text("Y swap",animX+3,82);
    }
}
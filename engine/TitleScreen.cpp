#include "engine/TitleScreen.hpp"

#include "sprites/Logo.cpp"

void TitleScreen::update(uint32_t tick) {
    if (time() > 1500 && (pressed(A) || pressed(B) || pressed(X) || pressed(Y))) {
        MainScene = OVERWORLD;
        changeSong = true;
    }
}

void TitleScreen::draw(uint32_t tick) {
    pen(0, 0, 0);
    clear();

    if (time() < 1500) {
        pen(15, 15, 15);
        text("Created By", 32, 40);
        text("Wyatt Grant", 30, 60);
    } else {
        if (logoY < 2) logoY++;
        pen(15, 15, 15);
        if (time() % 1000 < 500 && logoY == 2) {
            text("Press any button", 20, 112);   
        }
        text("v0.2", 100, 56);

        drawLogoMonster(16, 56);
        drawLogoCharacter(50, 56);
        drawLogo(2,logoY);
    }
}
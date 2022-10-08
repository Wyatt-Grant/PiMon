#include "engine/LoadGame.hpp"

LoadGame::LoadGame() {
    menuIndex = 0;
}

void LoadGame::update(uint32_t tick) {
    if (pressed(UP)) {
        if (menuIndex > 0) {
            menuIndex -= 1;
        }
    }
    if (pressed(DOWN)) {
        if (menuIndex < 1) {
            menuIndex += 1;
        }
    }

   if (pressed(A)) {
        if (menuIndex == 0) {
            MainScene = OVERWORLD;
            changeSong = true;
        } else if (menuIndex == 1) {
            MainScene = NEW_GAME;
            // changeSong = true;
        }
    }
}

void LoadGame::draw(uint32_t tick) {
    pen(0, 0, 0);
    clear();

    drawWindow(0,0,64,24);
    text("Continue", 10, 4);
    text("New Game", 10, 12);

    vline(4, 0 + (menuIndex * 8) + 4, 8);
    vline(5, 1 + (menuIndex * 8) + 4, 6);
    vline(6, 2 + (menuIndex * 8) + 4, 4);
    vline(7, 3 + (menuIndex * 8) + 4, 2);
}
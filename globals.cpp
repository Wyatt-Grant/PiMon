#include "globals.hpp"

// stuff needed to save the game
Point virtualCamera = {0, 0};
std::string playerName = "Wyatt";
std::string rivalName = "Bob";
int32_t playerAvatar = 1;
int32_t playerStarter = 1;
int32_t cashMoney = 0;
int32_t patches = 0;
int32_t gameTime = 0;
//settings menu
int8_t volume = 100;
int8_t bright = 50;
int8_t themeR = 2;
int8_t themeG = 2;
int8_t themeB = 2;


// regular globs
bool waiting = false;
SCENE MainScene = TITLE_SCREEN;
bool changeSong = false;
int32_t transitionCounter = 0;
int32_t transitionDone = false;
buffer_t *enemyFront = NULL;
bool menuOpen = false;
bool forceDrawMap = false;



void noCornerBox(int32_t x, int32_t y, int32_t w, int32_t h) {
    hline(x+1, y,   w-2);
    hline(x+1, y+h-1, w-2);
    vline(x, y+1,   h-2);
    if (x+w-1 < 120) {
        vline(x+w-1, y+1, h-2);
    }
}

void drawWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    if (x + w > 122) {
        w = 122 - x;
    }

    pen(15,15,15);
    noCornerBox(x,y,w,h);
    frect(x+1,y+1,w-2,h-2);
    pen(themeR,themeG,themeB);
    noCornerBox(x+1,y+1,w-2,h-2);
}

void playTick() {
    voice_t tickSound = voice(20,0,0,0,0,0,0,0,0);
    play(tickSound, 480, 20, volume);
}
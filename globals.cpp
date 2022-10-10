#include "globals.hpp"
#include "Sprites.cpp"
#include <math.h>

#include "maps/town1/outside/town1_outside_colliders.cpp"
#include "maps/town1/outside/town1_outside_tilemap.cpp"
#include "maps/town1/outside/town1_outside_tileset.cpp"

#include "maps/town1/inside/town1_inside_colliders.cpp"
#include "maps/town1/inside/town1_inside_tilemap.cpp"
#include "maps/town1/inside/town1_inside_tileset.cpp"

// stuff needed to save the game
Point virtualCamera = {0, 0};
std::string playerName = "Wyatt";
std::string rivalName = "Bob";
int32_t playerAvatar = 1;
int32_t playerStarter = 1;
int32_t cashMoney = 0;
int32_t patches = 0;
int32_t gameTime = 0;
std::vector<trainerPimon> party;
int32_t currentMap = 0; // 1 == outside 0 == inside
bool caughtPimon[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

//items
int8_t potion = 3; // heal hp
int8_t elixer = 3; // heal hp
int8_t ruby = 3; // catching
int8_t emerald = 3; // catching
int8_t diamond = 3; // catching
int8_t coffee = 3;// heal sleep
int8_t cure = 0; // heal poison
int8_t icePack = 3; // heal burn & bruise

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
std::vector<trainerPimon> enemyParty;
bool isWildBattle = false;

#include "PimonData.cpp"

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

int32_t xpToLvl(int32_t _xp) {
    return (int32_t) log2(_xp);
}

int32_t lvlToXp(int32_t _lvl) {
    return (int32_t) pow(2, _lvl);
}

// pixel perfect spite
// prevents weird artifcats when you to *try* and draw "outside" the buffer
// allows you to be kind of lazy with animations
void ppSprite(int32_t spriteOffset, int32_t posX, int32_t posY) {
    int32_t underflow = -8;
    int32_t overflow = 120;

    if (posY >= underflow && posX >= underflow && posY <= overflow && posX <= overflow) {
        for (int32_t y = 0; y < 8; y++) {
            for (int32_t x = 0; x < 8; x++) {
                if (posX + x >= 0 && posY + y >= 0) {
                    uint32_t sx = ((spriteOffset * 8) % _ss->w) + x;
                    uint32_t sy = (((spriteOffset * 8) / _ss->w) * 8) + y;
                    blit(_ss, sx, sy, 1, 1, posX + x, posY + y);
                }
            }
        }
    }
}

void draw56sprite(uint32_t _x, uint32_t _y) {
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 7; y++) {
            int32_t offset = (y * 7) + x;
            int32_t adjustedX = (x*8)+_x;
            int32_t adjustedY = (y*8)+_y;
            if (adjustedX > 0 && adjustedY > 0) {
                sprite(offset, adjustedX, adjustedY);
            } else {
                ppSprite(offset, adjustedX, adjustedY);
            }
        }
    }
}

pimon getPimonData(std::vector<trainerPimon> p, int32_t index) {
    return genericPimonData[p.at(index).pimon_id - 1];
}

int32_t getMaxHp(int32_t pimon_id, int32_t lvl) {
    return genericPimonData[pimon_id-1].hp * lvl;
}

void setPimonBuffer(uint32_t number) {
    switch(number) {
        case 1:
            spritesheet(pimon_1_sprite_sheet);
            break;
        case 2:
            spritesheet(pimon_2_sprite_sheet);
            break;
        case 3:
            spritesheet(pimon_3_sprite_sheet);
            break;
        case 4:
            spritesheet(pimon_4_sprite_sheet);
            break;
        case 5:
            spritesheet(pimon_5_sprite_sheet);
            break;
        case 6:
            spritesheet(pimon_6_sprite_sheet);
            break;
        case 7:
            spritesheet(pimon_7_sprite_sheet);
            break;
        case 8:
            spritesheet(pimon_8_sprite_sheet);
            break;
        case 9:
            spritesheet(pimon_9_sprite_sheet);
            break;
        case 10:
            spritesheet(pimon_10_sprite_sheet);
            break;
        case 11:
            spritesheet(pimon_11_sprite_sheet);
            break;
        case 12:
            spritesheet(pimon_12_sprite_sheet);
            break;
        case 13:
            spritesheet(pimon_13_sprite_sheet);
            break;
        case 14:
            spritesheet(pimon_14_sprite_sheet);
            break;
        case 15:
            spritesheet(pimon_15_sprite_sheet);
            break;
        case 16:
            spritesheet(pimon_16_sprite_sheet);
            break;
        case 17:
            spritesheet(pimon_17_sprite_sheet);
            break;
        case 18:
            spritesheet(pimon_18_sprite_sheet);
            break;
        case 19:
            spritesheet(pimon_19_sprite_sheet);
            break;
        case 20:
            spritesheet(pimon_20_sprite_sheet);
            break;
        case 21:
            spritesheet(pimon_21_sprite_sheet);
            break;
        case 22:
            spritesheet(pimon_22_sprite_sheet);
            break;
        case 23:
            spritesheet(pimon_23_sprite_sheet);
            break;
        case 24:
            spritesheet(pimon_24_sprite_sheet);
            break;
        default:
            break;
    }
}

void setPimonBackBuffer(uint32_t number) {
    switch(number) {
        case 1:
            spritesheet(pimon_back_1_sprite_sheet);
            break;
        case 2:
            spritesheet(pimon_back_2_sprite_sheet);
            break;
        case 3:
            spritesheet(pimon_back_3_sprite_sheet);
            break;
        case 4:
            spritesheet(pimon_back_4_sprite_sheet);
            break;
        case 5:
            spritesheet(pimon_back_5_sprite_sheet);
            break;
        case 6:
            spritesheet(pimon_back_6_sprite_sheet);
            break;
        case 7:
            spritesheet(pimon_back_7_sprite_sheet);
            break;
        case 8:
            spritesheet(pimon_back_8_sprite_sheet);
            break;
        case 9:
            spritesheet(pimon_back_9_sprite_sheet);
            break;
        case 10:
            spritesheet(pimon_back_10_sprite_sheet);
            break;
        case 11:
            spritesheet(pimon_back_11_sprite_sheet);
            break;
        case 12:
            spritesheet(pimon_back_12_sprite_sheet);
            break;
        case 13:
            spritesheet(pimon_back_13_sprite_sheet);
            break;
        case 14:
            spritesheet(pimon_back_14_sprite_sheet);
            break;
        case 15:
            spritesheet(pimon_back_15_sprite_sheet);
            break;
        case 16:
            spritesheet(pimon_back_16_sprite_sheet);
            break;
        case 17:
            spritesheet(pimon_back_17_sprite_sheet);
            break;
        case 18:
            spritesheet(pimon_back_18_sprite_sheet);
            break;
        case 19:
            spritesheet(pimon_back_19_sprite_sheet);
            break;
        case 20:
            spritesheet(pimon_back_20_sprite_sheet);
            break;
        case 21:
            spritesheet(pimon_back_21_sprite_sheet);
            break;
        case 22:
            spritesheet(pimon_back_22_sprite_sheet);
            break;
        case 23:
            spritesheet(pimon_back_23_sprite_sheet);
            break;
        case 24:
            spritesheet(pimon_back_24_sprite_sheet);
            break;
        default:
            break;
    }
}

bool isSuperEffective(int32_t attackType, int32_t defenseType) {
    switch (attackType) {
        case NONE:
            return false;
        case FIRE:
            if (defenseType == AIR) return true;
            return false;
        case WATER:
            if (defenseType == FIRE) return true;
            return false;
        case EARTH:
            if (defenseType == WATER) return true;
            return false;
        case AIR:
            if (defenseType == EARTH) return true;
            return false;
    }
    return false;
}

bool isNotVeryEffective(int32_t attackType, int32_t defenseType) {
    switch (attackType) {
        case NONE:
            return false;
        case FIRE:
            if (defenseType == WATER) return true;
            return false;
        case WATER:
            if (defenseType == EARTH) return true;
            return false;
        case EARTH:
            if (defenseType == AIR) return true;
            return false;
        case AIR:
            if (defenseType == FIRE) return true;
            return false;
    }
    return false;
}

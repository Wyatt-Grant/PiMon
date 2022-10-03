#include <picosystem.hpp>
#include <stdint.h>
#include <string>
#include "types.hpp"

using namespace picosystem;

extern Point virtualCamera;
extern bool waiting;
extern SCENE MainScene;
extern std::string playerName;
extern int32_t playerAvatar;
extern std::string rivalName;
extern int32_t playerStarter;
extern bool changeSong;
extern int32_t transitionCounter;
extern int32_t transitionDone;
extern bool forceDrawMap;
extern buffer_t *enemyFront;
extern int8_t logoY;
extern bool menuOpen;
extern int8_t volume;
extern int8_t bright;
extern int8_t themeR;
extern int8_t themeG;
extern int8_t themeB;
extern int32_t cashMoney;
extern int32_t patches;
extern int32_t gameTime;

void drawWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void playTick();
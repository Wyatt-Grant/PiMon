#include "globals.hpp"

Point virtualCamera = {0, 0};
bool waiting = false;
SCENE MainScene = TITLE_SCREEN;
std::string playerName = "Wyatt";
std::string rivalName = "Bob";
int32_t playerAvatar = 1;
bool changeSong = false;


int32_t transitionCounter = 0;
int32_t transitionDone = false;

buffer_t *enemyFront = NULL;

int8_t logoY = -56;
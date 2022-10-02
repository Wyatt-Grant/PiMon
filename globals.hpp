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
extern bool changeSong;
extern int32_t transitionCounter;
extern int32_t transitionDone;

extern buffer_t *enemyFront;

extern int8_t logoY;
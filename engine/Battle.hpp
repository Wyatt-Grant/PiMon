#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "engine/Message.hpp"

using namespace picosystem;

class Battle {       
    private:
        bool waitingForStartAnimation;
        int32_t animPlayer;
        int32_t animEnemy;

        enum SCENE { BATTLE_INTRO_TEXT, BATTLE_INTRO_ANIMATION, BATTLE_ENEMY_TRAINER_TEXT, BATTLE_MONSTER_TRAINER_TEXT };
        SCENE scene;

        void noCornerBox(int32_t x, int32_t y, int32_t w, int32_t h);
        void drawWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        void drawCharacter1Back(int32_t _x, int32_t _y);
        void ppSprite(buffer_t *buffer, int32_t spriteOffset, int32_t posX, int32_t posY);
        void drawEnemyTrainerBack(int32_t _x, int32_t _y);
        
    public:
        Battle();
        void draw(uint32_t tick);
        void update(uint32_t tick, Message *message);
};
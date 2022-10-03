#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

using namespace picosystem;

class TitleScreen {       
    private:
        int8_t logoY;
        
        void ppSpriteLogo(buffer_t *buffer, int32_t spriteOffset, int32_t posX, int32_t posY);
        void drawLogoCharacter(int32_t _x, int32_t _y);
        void drawLogoMonster(int32_t _x, int32_t _y);
        void drawLogo(int32_t _x, int32_t _y); 

    public:
        TitleScreen();
        void draw(uint32_t tick);
        void update(uint32_t tick);
};
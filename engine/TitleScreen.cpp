#include "engine/TitleScreen.hpp"

#include "sprites/Logo.cpp"

TitleScreen::TitleScreen() {
    logoY = -56;
}

void TitleScreen::ppSpriteLogo(buffer_t *buffer, int32_t spriteOffset, int32_t posX, int32_t posY) {
    int32_t underflow = -8;
    int32_t overflow = 120;

    if (posY >= underflow && posX >= underflow && posY <= overflow && posX <= overflow) {
        for (int32_t y = 0; y < 8; y++) {
            for (int32_t x = 0; x < 8; x++) {
                if (posX + x >= 0 && posY + y >= 0) {
                    uint32_t sx = ((spriteOffset * 8) % buffer->w) + x;
                    uint32_t sy = (((spriteOffset * 8) / buffer->w) * 8) + y;
                    blit(buffer, sx, sy, 1, 1, posX + x, posY + y);
                }
            }
        }
    }
}

void TitleScreen::drawLogoCharacter(int32_t _x, int32_t _y) {
    switch(playerAvatar) {
        case 1:
            spritesheet(character1_logo_buffer);
            break;
        case 2:
            spritesheet(character2_logo_buffer);
            break;
        case 3:
            spritesheet(character3_logo_buffer);
            break;
    }
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 7; y++) {
            int32_t offset = (y * 7) + x;
            sprite(offset, x*8+_x, y*8+_y);
        }
    }
}

void TitleScreen::drawLogoMonster(int32_t _x, int32_t _y) {
    switch(playerStarter) {
        case 1:
            spritesheet(monster1_logo_buffer);
            break;
        case 2:
            spritesheet(monster2_logo_buffer);
            break;
        case 3:
            spritesheet(monster3_logo_buffer);
            break;
        case 4:
            spritesheet(monster4_logo_buffer);
            break;
    }
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 7; y++) {
            int32_t offset = (y * 7) + x;
            sprite(offset, x*8+_x, y*8+_y);
        }
    }
}

void TitleScreen::drawLogo(int32_t _x, int32_t _y) {
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 7; y++) {
            int32_t offset = (y * 15) + x;
            if ((y*8+_y) > 0) {
                spritesheet(logo_buffer);
                sprite(offset, x*8+_x, y*8+_y);
            } else {
                ppSpriteLogo(logo_buffer, offset, x*8+_x, y*8+_y);
            }
        }
    }
}

void TitleScreen::update(uint32_t tick) {
    if (time() > 3000 && (pressed(A) || pressed(B) || pressed(X) || pressed(Y))) {
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
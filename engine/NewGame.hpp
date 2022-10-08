#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "engine/Message.hpp"

using namespace picosystem;

class NewGame {       
    private:
        enum NEW_GAME_SCENE {
            TEXT_1,
            TEXT_2,
            TEXT_3,
            TEXT_4,
            TEXT_5,
            TEXT_6,
            TEXT_7,
            TEXT_8,
            NEW_GAME_END,
            NAME_INPUT,
            AVATAR_INPUT,
            RIVAL_INPUT,
        };
        NEW_GAME_SCENE scene;

        // i should probably generalise this input system ...but fuck it
        bool upperCaseMode;
        const std::string LETTERS1[32] = {
            "a", "b", "c", "d", "e", "f", "g", "h",
            "i", "j", "k", "l", "m", "n", "o", "p",
            "q", "r", "s", "t", "u", "v", "w", "x",
            "y", "z", " ", "-", "_", "!", "?", "."
        };
        const std::string LETTERS2[32] = {
            "A", "B", "C", "D", "E", "F", "G", "H",
            "I", "J", "K", "L", "M", "N", "O", "P",
            "Q", "R", "S", "T", "U", "V", "W", "X",
            "Y", "Z", " ", "-", "_", "!", "?", "."
        };
        int32_t textCursorX;
        int32_t textCursorY;
        int32_t startCursor;

        void handleTextCursor();
        void handleAvatarInput();
        void drawProf();
        void drawCharacterChooser(int32_t avatar);
        void drawRivalName();
        void drawName();
        void drawArrow(int32_t x, int32_t y);
        void drawLetters();

    public:
        NewGame();
        void draw(uint32_t tick);
        void update(uint32_t tick, Message *message);
};
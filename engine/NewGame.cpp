#include "engine/NewGame.hpp"

NewGame::NewGame() {
    scene = TEXT_1;
    upperCaseMode = true;
    textCursorX = 0;
    textCursorY = 0;
    startCursor = 0;
}

void NewGame::handleTextCursor() {
    if (pressed(UP)) {
        textCursorY -= 1;
    }
    if (pressed(DOWN)) {
        textCursorY += 1;
    }
    if (pressed(LEFT)) {
        textCursorX -= 1;
    }
    if (pressed(RIGHT)) {
        textCursorX += 1;
    }
    if (textCursorY < 0) {
        textCursorY = 0;
    }
    if (textCursorY > 3) {
        textCursorY = 3;
    }
    if (textCursorX < 0) {
        textCursorX = 0;
    }
    if (textCursorX > 7) {
        textCursorX = 7;
    }

    if (scene == NAME_INPUT) {
        if (pressed(A) && playerName.size() < 12) {
            if (upperCaseMode) {
                playerName.append(LETTERS2[(textCursorY * 8) + textCursorX]);
            } else {
                playerName.append(LETTERS1[(textCursorY * 8) + textCursorX]);
            }
        }
        if (pressed(B) && playerName.size() > 0) {
            playerName.pop_back();
        }
        if (pressed(X) && playerName.size() > 0) {
            scene = TEXT_3;
        }
    } else if (scene == RIVAL_INPUT) {
        if (pressed(A) && playerName.size() < 12) {
            if (upperCaseMode) {
                rivalName.append(LETTERS2[(textCursorY * 8) + textCursorX]);
            } else {
                rivalName.append(LETTERS1[(textCursorY * 8) + textCursorX]);
            }
        }
        if (pressed(B) && playerName.size() > 0) {
            rivalName.pop_back();
        }
        if (pressed(X) && playerName.size() > 0) {
            scene = TEXT_7;
        }
    }

    if (pressed(Y)) {
        upperCaseMode = !upperCaseMode;
    }
}


void NewGame::handleAvatarInput() {
    if (pressed(LEFT)) {
        playerAvatar -= 1;
    }
    if (pressed(RIGHT)) {
        playerAvatar += 1;
    }
    if (playerAvatar < 1) {
        playerAvatar = 1;
    }
    if (playerAvatar > 3) {
        playerAvatar = 3;
    }

    if (pressed(X)) {
        scene = TEXT_5;
    }
}

void NewGame::update(uint32_t tick, Message *message) {
    std::string msg = "";
    switch (scene) {
        case TEXT_1:
            message->showMessages({
                { "Hello and welcome to\nthe world of PiMon!", 0, []() -> void { return; } },
                { "This world is\ninhabited by strange\nmonsters called", 0, []() -> void { return; } },
                { "Pico Monsters or\nPiMon for short.", 0, []() -> void { return; } },
                { "Some people keep\nPiMon as pets. Others\nuse them to Fight!", 0, []() -> void { return; } },
                { "My name is Dr. Pine.\nI've devoted my life\nto studying PiMon.", 0, []() -> void { return; } },
                { "Before we begin\nwhat is your name?", 0, []() -> void { return; } }
            });
            scene = TEXT_2;
            break;
        case TEXT_2:
            if (!waiting) scene = NAME_INPUT;
            break;
        case NAME_INPUT:
            handleTextCursor();
            break;
        case TEXT_3:
            message->showMessages({
                { "What a nice name!\nNice to meet you\nPLAYER!", 0, []() -> void { return; } },
                { "Now let me get a\nbetter look at you...", 0, []() -> void { return; } },
            });
            scene = TEXT_4;
            break;
        case TEXT_4:
            if (!waiting) scene = AVATAR_INPUT;
            break;
        case AVATAR_INPUT:
            handleAvatarInput();
            break;
        case TEXT_5:
            message->showMessages({
                { "Ah now i can see you\nclearly!", 0, []() -> void { return; } },
                { "Your very own PiMon\njourney is about to\nbegin!", 0, []() -> void { return; } },
                { "Your neighbour...\nWhat was his name?", 0, []() -> void { return; } },
            });
            scene = TEXT_6;
            break;
        case TEXT_6:
            if (!waiting) scene = RIVAL_INPUT;
            break;
        case RIVAL_INPUT:
            handleTextCursor();
            break;
        case TEXT_7:
            message->showMessages({
                { "Ah yes his name was\nRIVAL!", 0, []() -> void { return; } },
                { "Looks like you're\nready to begin! Have\nfun!", 0, []() -> void { return; } },
            });
            scene = TEXT_8;
            break;
        case TEXT_8:
            if (!waiting) scene = NEW_GAME_END;
            break;
        case NEW_GAME_END:
            MainScene = OVERWORLD;
            changeSong = true;
            break;
    }
}

void NewGame::drawLetters() {
    drawWindow(0, 23, 120, 50);
    drawWindow(14, 3, 88, 16);
    pen(0, 0, 0);
    for (int n = 0; n < 4; n++) {
        for (int i = 0; i < 8; i++) {
            if (upperCaseMode) {
                text(LETTERS2[i + (n * 8)], 10 + (i * 13), 26 + (n * 12));
            } else {
                text(LETTERS1[i + (n * 8)], 10 + (i * 13), 26 + (n * 12));
            }
        }
    }
}

void  NewGame::drawArrow(int32_t x, int32_t y) {
    pen(0, 0, 0);
    vline(x,   y,   7);
    vline(x+1, y+1, 5);
    vline(x+2, y+2, 3);
    vline(x+3, y+3, 1);
}

void  NewGame::drawName() {
    pen(0, 0, 0);
    text(playerName, 20, 7);

    pen(15, 15, 15);
    text("X save", 0, 112);
    text("Y case", 88, 112);
    text("A select", 0, 104);
    text("B back", 88, 104);
}

void  NewGame::drawRivalName() {
    pen(0, 0, 0);
    text(rivalName, 20, 7);

    pen(15, 15, 15);
    text("X save", 0, 112);
    text("Y case", 88, 112);
    text("A select", 0, 104);
    text("B back", 88, 104);
}

void  NewGame::drawCharacterChooser(int32_t avatar) {
    drawWindow(24, 14, 72, 60);
    
    switch(avatar) {
        case 1:
            spritesheet(character_1_overworld_buffer);
            break;
        case 2:
            spritesheet(character_2_overworld_buffer);
            break;
        case 3:
            spritesheet(character_3_overworld_buffer);
            break;
    }
    
    sprite(0,74,55);
    sprite(1,82,55);
    sprite(24,74,63);
    sprite(25,82,63);

    switch(avatar) {
        case 1:
            spritesheet(character_1_front_buffer);
            break;
        case 2:
            spritesheet(character_2_front_buffer);
            break;
        case 3:
            spritesheet(character_3_front_buffer);
            break;
    }
    draw56sprite(32, 16);

    pen(0,0,0);
    if (avatar < 3) {
        vline(89,40,8);
        vline(90,41,6);
        vline(91,42,4);
        vline(92,43,2);
    }
    if (avatar > 1) {
        vline(30,40,8);
        vline(29,41,6);
        vline(28,42,4);
        vline(27,43,2);
    }

    pen(15,15,15);
    text("X save", 0, 0);
}

void  NewGame::drawProf() {
    spritesheet(npc_1_front_buffer);
    draw56sprite(32, 16);
}

void NewGame::draw(uint32_t tick) {
    pen(0, 0, 0);
    clear();

    switch (scene) {
        case NAME_INPUT:
            drawLetters();
            drawName();
            drawArrow(5 + (textCursorX * 13), 26 + (textCursorY * (12)));
            break;
        case AVATAR_INPUT:
            drawCharacterChooser(playerAvatar);
            break;
        case RIVAL_INPUT:
            drawLetters();
            drawRivalName();
            drawArrow(5 + (textCursorX * 13), 26 + (textCursorY * (12)));
            break;
        case NEW_GAME_END:
            break;
        default:
            drawProf();
            break;
    }
}
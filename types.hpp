#pragma once

enum Direction { up, down, left, right };
enum SCENE {
    TITLE_SCREEN,
    NEWGAME_INTRO,
    OVERWORLD,
    BATTLE,
};

struct Point {
    int32_t x;
    int32_t y;
};
struct Text {
    std::string text;
    int32_t flag;
    void (*callback)(); //limitation: when you have multple "pages" or text, only the callback on the last one is called
};
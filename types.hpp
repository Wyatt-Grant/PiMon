#pragma once

enum Direction { up, down, left, right };
enum SCENE {
    TITLE_SCREEN,
    LOAD_GAME,
    NEW_GAME,
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
// types
const int32_t FIRE = 1;
const int32_t WATER = 2;
const int32_t EARTH = 3;
const int32_t AIR = 4;

// status
const int32_t NONE = 0; // also use for types
const int32_t BURNED = 1;
const int32_t SLEEPING = 2;
const int32_t CONFUSED = 3;

// damage types
const int32_t NO_DAMAGE = 1;
const int32_t PHYSICAL_DAMAGE = 2;
const int32_t SPECIAL_DAMAGE = 3;

//move target
const int32_t TARGET_USER = 1;
const int32_t TARGET_OPPONENT = 2;
const int32_t TARGET_ALL = 3;
const int32_t TARGET_FIELD = 4;

//move effects
const int32_t BASIC_ATTACK = 1;
const int32_t INCREASED_CRIT_ATTACK = 2;
const int32_t BURN_ATTACK = 4;
const int32_t SLEEP_ATTACK = 5;
const int32_t CONFUSION_ATTACK = 6;
const int32_t RAISE_USER_SPEED = 7;
const int32_t RAISE_USER_ATTACK = 8;
const int32_t RAISE_USER_DEFENSE = 9;
const int32_t RAISE_USER_SP_ATTACK = 10;
const int32_t RAISE_USER_SP_DEFENSE = 11;
const int32_t LOWER_ENEMY_SPEED = 12;
const int32_t LOWER_ENEMY_ATTACK = 13;
const int32_t LOWER_ENEMY_DEFENSE = 14;
const int32_t LOWER_ENEMY_SP_ATTACK = 15;
const int32_t LOWER_ENEMY_SP_DEFENSE = 16;

// status effects
const int32_t BURN_STATUS = 1;
const int32_t SLEEP_STATUS = 2;
const int32_t CONFUSE_STATUS = 3;

struct move {
    int32_t id;
    std::string name;
    int32_t type;
    int32_t power;
    int32_t accuracy;
    int32_t target_id;
    int32_t damage_type;
    int32_t effect_id;
    int32_t effect_chance;
};
struct pimon {
    int32_t id;
    std::string name;
    int32_t type;

    int32_t hp;
    int32_t attack;
    int32_t defense;
    int32_t spatk;
    int32_t spdef;
    int32_t speed;

    std::vector<move> moves;
};
struct trainerPimon {
    int32_t pimon_id;
    int32_t xp;
    int32_t hp;
    int32_t status;
};
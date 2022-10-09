#include <picosystem.hpp>
#include <stdint.h>
#include <string>
#include "types.hpp"

using namespace picosystem;

//pimon sprites
extern buffer_t *pimon_1_sprite_sheet;
extern buffer_t *pimon_2_sprite_sheet;
extern buffer_t *pimon_3_sprite_sheet;
extern buffer_t *pimon_4_sprite_sheet;
extern buffer_t *pimon_5_sprite_sheet;
extern buffer_t *pimon_6_sprite_sheet;
extern buffer_t *pimon_7_sprite_sheet;
extern buffer_t *pimon_8_sprite_sheet;
extern buffer_t *pimon_9_sprite_sheet;
extern buffer_t *pimon_10_sprite_sheet;
extern buffer_t *pimon_12_sprite_sheet;
extern buffer_t *pimon_13_sprite_sheet;
extern buffer_t *pimon_14_sprite_sheet;
extern buffer_t *pimon_15_sprite_sheet;
extern buffer_t *pimon_16_sprite_sheet;
extern buffer_t *pimon_17_sprite_sheet;
extern buffer_t *pimon_18_sprite_sheet;
extern buffer_t *pimon_19_sprite_sheet;
extern buffer_t *pimon_20_sprite_sheet;
extern buffer_t *pimon_21_sprite_sheet;
extern buffer_t *pimon_22_sprite_sheet;
extern buffer_t *pimon_23_sprite_sheet;
extern buffer_t *pimon_24_sprite_sheet;

extern buffer_t *pimon_back_1_sprite_sheet;
extern buffer_t *pimon_back_2_sprite_sheet;
extern buffer_t *pimon_back_3_sprite_sheet;
extern buffer_t *pimon_back_4_sprite_sheet;
extern buffer_t *pimon_back_5_sprite_sheet;
extern buffer_t *pimon_back_6_sprite_sheet;
extern buffer_t *pimon_back_7_sprite_sheet;
extern buffer_t *pimon_back_8_sprite_sheet;
extern buffer_t *pimon_back_9_sprite_sheet;
extern buffer_t *pimon_back_10_sprite_sheet;
extern buffer_t *pimon_back_12_sprite_sheet;
extern buffer_t *pimon_back_13_sprite_sheet;
extern buffer_t *pimon_back_14_sprite_sheet;
extern buffer_t *pimon_back_15_sprite_sheet;
extern buffer_t *pimon_back_16_sprite_sheet;
extern buffer_t *pimon_back_17_sprite_sheet;
extern buffer_t *pimon_back_18_sprite_sheet;
extern buffer_t *pimon_back_19_sprite_sheet;
extern buffer_t *pimon_back_20_sprite_sheet;
extern buffer_t *pimon_back_21_sprite_sheet;
extern buffer_t *pimon_back_22_sprite_sheet;
extern buffer_t *pimon_back_23_sprite_sheet;
extern buffer_t *pimon_back_24_sprite_sheet;

// npc sprites
extern buffer_t *npc_1_front_buffer;
extern buffer_t *npc_2_front_buffer;
extern buffer_t *npc_3_front_buffer;
extern buffer_t *npc_4_front_buffer;
extern buffer_t *npc_5_front_buffer;
extern buffer_t *npc_6_front_buffer;
extern buffer_t *npc_7_front_buffer;
extern buffer_t *npc_8_front_buffer;
extern buffer_t *npc_9_front_buffer;
extern buffer_t *npc_10_front_buffer;
extern buffer_t *npc_11_front_buffer;

extern buffer_t *npc_1_overworld_buffer;
extern buffer_t *npc_2_overworld_buffer;
extern buffer_t *npc_3_overworld_buffer;
extern buffer_t *npc_4_overworld_buffer;
extern buffer_t *npc_5_overworld_buffer;
extern buffer_t *npc_6_overworld_buffer;
extern buffer_t *npc_7_overworld_buffer;
extern buffer_t *npc_8_overworld_buffer;
extern buffer_t *npc_9_overworld_buffer;
extern buffer_t *npc_10_overworld_buffer;
extern buffer_t *npc_11_overworld_buffer;

// TitleScreen
extern buffer_t *logo_buffer;

// player
extern buffer_t *character_1_overworld_buffer;
extern buffer_t *character_1_front_buffer;
extern buffer_t *character_2_overworld_buffer;
extern buffer_t *character_2_front_buffer;
extern buffer_t *character_3_overworld_buffer;
extern buffer_t *character_3_front_buffer;
extern buffer_t *character_1_back_buffer;
extern buffer_t *character_2_back_buffer;
extern buffer_t *character_3_back_buffer;

//other
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
extern int8_t potion;
extern int8_t elixer;
extern int8_t ruby;
extern int8_t emerald;
extern int8_t diamond;
extern int8_t coffee;
extern int8_t cure;
extern int8_t icePack;
extern std::vector<trainerPimon> party;
extern std::vector<trainerPimon> enemyParty;
extern bool isWildBattle;
extern int32_t currentMap;

extern pimon genericPimonData[];

//maps
extern const int16_t town1_outside_colliders[80][80];
extern const int16_t town1_outside_above[80][80];
extern const int16_t town1_outside_below[80][80];
extern buffer_t *town_1_outside_tileset_buffer;

extern const int16_t town1_inside_colliders[80][80];
extern const int16_t town1_inside_above[80][80];
extern const int16_t town1_inside_below[80][80];
extern buffer_t *town_1_inside_tileset_buffer;

// helpers
void drawWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void playTick();
void ppSprite(buffer_t *buffer, int32_t spriteOffset, int32_t posX, int32_t posY);
void draw56sprite(uint32_t _x, uint32_t _y);
pimon getPimonData(std::vector<trainerPimon> p, int32_t index);
void setPimonBuffer(uint32_t number);
void setPimonBackBuffer(uint32_t number);
int32_t xpToLvl(int32_t _xp);
int32_t lvlToXp(int32_t _lvl);
int32_t getMaxHp(int32_t pimon_id, int32_t lvl);
bool isNotVeryEffective(int32_t attackType, int32_t defenseType);
bool isSuperEffective(int32_t attackType, int32_t defenseType);
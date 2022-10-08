#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "engine/Message.hpp"
#include "engine/menu/Menu.hpp"

using namespace picosystem;

class Battle {       
    private:
        bool waitingForStartAnimation;
        int32_t animPlayer;
        int32_t animEnemy;
        int32_t actionIndex;
        bool animSwitched;

        int32_t playerPartyIndex;
        int32_t enemyPartyIndex;

        bool showEffectiveText;
        bool wasCrit;
        bool wasSuperEffective;
        bool playerIsFirst;
        int32_t enemyMoveIndex;
        int32_t damage;
        bool waitingForPartySwitch;
        int32_t switchToTarget;

        enum SCENE {
            BATTLE_INTRO_TEXT,
            BATTLE_INTRO_ANIMATION,
            BATTLE_ENEMY_NAME_TEXT,
            BATTLE_PARTY_NAME_TEXT,
            BATTLE_WAIT_FOR_INTRO_END,

            BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT,
            BATTLE_WAIT_FOR_PLAYER_MOVE_INPUT,
            BATTLE_WAIT_FOR_PLAYER_PARTY_INPUT,
            BATTLE_WAIT_FOR_PLAYER_BAG_INPUT,

            BATTLE_DETERMINE_ORDER,
            BATTLE_WAIT_FOR_PLAYER_MOVE,
            BATTLE_WAIT_FOR_ENEMY_MOVE,
            BATTLE_WAIT_FOR_PLAYER_DAMAGE,
            BATTLE_WAIT_FOR_ENEMY_DAMAGE,
            BATTLE_WAIT_FOR_PLAYER_SWITCH,
            BATTLE_WAIT_FOR_ENEMY_SWITCH,

            BATTLE_OPEN_PARTY,

            BATTLE_RUN_AWAY,
            BATTLE_WIN,
            BATTLE_LOSE,

            END_BATTLE,
        };
        SCENE scene;

        void drawCharacter1Back(int32_t _x, int32_t _y);
        void ppSprite(buffer_t *buffer, int32_t spriteOffset, int32_t posX, int32_t posY);
        void drawEnemyTrainer(int32_t _x, int32_t _y);
        void slideInPlayer();
        void slideInEnemy();
        void slideOutPlayer();
        void slideOutEnemy();
        void slideInPlayerAndEnemy();
        void slideOutPlayerAndEnemy();
        void drawPlayerPartySprite(int32_t _x, int32_t _y);
        void drawEnemyPartySprite(int32_t _x, int32_t _y);
        void drawActions();
        void drawMoves();
        void handlePlayerSelectActionInput(Menu *menu);
        void handlePlayerSelectMoveInput();
        void drawMainView();
        int32_t calcDamage(trainerPimon attacker, pimon defender, move usedMove);
        void setNextPartyPimonIndex();
        void setNextEnemyPartyPimonIndex();
        
    public:
        Battle();
        void draw(uint32_t tick, Menu *menu);
        void update(uint32_t tick, Message *message, Menu *menu);
};
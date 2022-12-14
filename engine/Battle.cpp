#include "engine/Battle.hpp"

Battle::Battle() {
    waitingForStartAnimation = true;
    animPlayer = -56;
    animEnemy = 120;
    scene = BATTLE_INTRO_TEXT;
    actionIndex = 0;
    showEffectiveText = false;
    wasCrit = false;
    wasSuperEffective = false;
    playerIsFirst = false;
    playerPartyIndex = 0;
    enemyPartyIndex = 0;
    enemyMoveIndex = 0;
    animSwitched = false;
    waitingForPartySwitch = false;
    switchToTarget = 0;
    caught = false;
    gemLevel = 0;
}

void Battle::setNextPartyPimonIndex() {
    for (int i = 0; i < party.size(); i++) {
        if (party.at(i).hp > 0) {
            playerPartyIndex = i;
            return;
        }
    }

    scene = BATTLE_LOSE;
}

void Battle::setNextEnemyPartyPimonIndex() {
    for (int i = 0; i < enemyParty.size(); i++) {
        if (enemyParty.at(i).hp > 0) {
            enemyPartyIndex = i;
            return;
        }
    }

    scene = BATTLE_WIN;
}

int32_t Battle::calcDamage(trainerPimon attacker, pimon defender, move usedMove) {
    if (usedMove.damage_type == NO_DAMAGE) {
        return 0;
    }

    int32_t level = xpToLvl(attacker.xp);
    int32_t crit = 1;
    wasCrit = false;
    if (rand() % 16 == 0) {
        crit = 2;
            wasCrit = true;
    }

    int32_t power = usedMove.power;
    int32_t attack = genericPimonData[attacker.pimon_id-1].attack;
    int32_t defense = defender.defense;
    if (usedMove.damage_type == SPECIAL_DAMAGE) {
        attack = genericPimonData[attacker.pimon_id-1].spatk;
        defense = defender.spdef;
    }
    float stab = 1;
    if (usedMove.type == genericPimonData[attacker.pimon_id-1].type) {
        stab = 1.5;
    }
    float random = 1 - (((rand() % 15) + 1)/100);

    float type = 1;
    if (isSuperEffective(usedMove.type, defender.type)) {
        type = 2;
    } else if (isNotVeryEffective(usedMove.type, defender.type)) {
        type = 0.5;
    }

    showEffectiveText = false;
    wasSuperEffective = false;
    if (type == 2) {
        showEffectiveText = true;
        wasSuperEffective = true;
    }
    if (type == 0.5) {
        showEffectiveText = true;
        wasSuperEffective = false;
    }

    int32_t dam = (((float)((((float)(2 * level * crit)/(float)5) + 2) * power * (float)attack/(float)defense)/(float)50) + 2) * stab * type * random;
    return dam*10;
}

void Battle::slideInPlayer() {
    if (animPlayer < 0) {
        animPlayer +=2;
    }
}
void Battle::slideInEnemy() {
    if (animEnemy > 64) {
        animEnemy-=2;
    }
}
void Battle::slideOutPlayer() {
    if (animPlayer > -56) {
        animPlayer-=2;
    }
}
void Battle::slideOutEnemy() {
    if (animEnemy < 120) {
        animEnemy+=2;
    }
}
void Battle::slideInPlayerAndEnemy() {
    slideInPlayer();
    slideInEnemy();
}
void Battle::slideOutPlayerAndEnemy() {
    slideOutPlayer();
    slideOutEnemy();
}

void Battle::handlePlayerSelectActionInput(Menu *menu) {
    if (pressed(UP) && actionIndex > 1) {
        actionIndex -= 2;
    }
    if (pressed(DOWN) && actionIndex < 2) {
        actionIndex += 2;
    }
    if (pressed(LEFT) && actionIndex > 0 && actionIndex != 2) {
        actionIndex -= 1;
    }
    if (pressed(RIGHT) && actionIndex < 3 && actionIndex != 1) {
        actionIndex += 1;
    }

    if (pressed(A)) {
        switch(actionIndex) {
            case 0:
                scene = BATTLE_WAIT_FOR_PLAYER_MOVE_INPUT;
                break;
            case 1:
                scene = BATTLE_OPEN_BAG;
                menu->bag->waitForOpenAnimation = true;
                menu->bag->animX = 120;
                break;
            case 2:
                scene = BATTLE_OPEN_PARTY;
                menu->partyMenu->waitForOpenAnimation = true;
                menu->partyMenu->animX = 120;
                break;
            case 3:
                scene = BATTLE_RUN_AWAY;
                break;
        }
    }
}

void Battle::handlePlayerSelectMoveInput() {
    int32_t lvl = xpToLvl(party.at(playerPartyIndex).xp);

    if (pressed(UP) && actionIndex > 1) {
        actionIndex -= 2;
    }
    if (pressed(DOWN) && actionIndex < 2) {
        if (lvl > 9 && actionIndex == 0) {
            actionIndex += 2;
        } else if (lvl > 14 && actionIndex == 1) {
            actionIndex += 2;
        }
    }
    if (pressed(LEFT) && actionIndex > 0 && actionIndex != 2) {
        actionIndex -= 1;
    }
    if (pressed(RIGHT) && actionIndex < 3 && actionIndex != 1) {
        if (actionIndex == 0 && lvl > 4) {
            actionIndex += 1;
        } else if (actionIndex == 2 && lvl > 14) {
            actionIndex += 1;
        }
    }

    if (pressed(A)) {
        // switch(actionIndex) {
        //     case 0:
        //         break;
        //     case 1:
        //         break;
        //     case 2:
        //         break;
        //     case 3:
        //         break;
        // }
        scene = BATTLE_DETERMINE_ORDER;
    }

    if (pressed(B)) {
        scene = BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
    }
}

void Battle::update(uint32_t tick, Message *message, Menu *menu, Player *player) {
    std::string msg = "";

    // slide animations don't respect the waiting flag
    switch(scene) {
        case BATTLE_INTRO_TEXT:
        case BATTLE_INTRO_ANIMATION:
        case BATTLE_ENEMY_NAME_TEXT:
            slideInPlayerAndEnemy();
            break;
        case BATTLE_PARTY_NAME_TEXT:
            slideOutPlayerAndEnemy();
            break;
        case BATTLE_WAIT_FOR_INTRO_END:
            slideInPlayerAndEnemy();
            break;
        case END_BATTLE:
            break;
        case BATTLE_WAIT_FOR_PLAYER_SWITCH:
            if (animSwitched) {
                slideInPlayer();
            } else {
                slideOutPlayer();
            }
            if (menu->partyMenu->waitForCloseAnimation || menu->partyMenu->waitForOpenAnimation) menu->partyMenu->update(tick);
            if (menu->bag->waitForCloseAnimation || menu->bag->waitForOpenAnimation) menu->bag->update(tick, message);
            break;
        case BATTLE_WAIT_FOR_ENEMY_SWITCH:
            if (animSwitched) {
                slideInEnemy();
            } else {
                slideOutEnemy();
            }
            break;
        case BATTLE_OPEN_PARTY:
            if (pressed(B)) {
                scene = BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
            }
            if (pressed(A)) {
                if (party.at(menu->partyMenu->menuIndex).hp > 0 && menu->partyMenu->menuIndex != playerPartyIndex) {
                    menu->partyMenu->close();
                    switchToTarget = menu->partyMenu->menuIndex;
                    message->showMessage("go some guy!");
                    waitingForPartySwitch = true;
                }
            }

            if (waitingForPartySwitch) {
                if (animSwitched) {
                    slideInPlayer();
                } else {
                    slideOutPlayer();
                }
                if (animPlayer == -56) {
                    playerPartyIndex = switchToTarget;
                    animSwitched = true;
                }
                if (animSwitched && animPlayer == 0) {
                    scene = BATTLE_WAIT_FOR_ENEMY_MOVE;
                }
            }
            menu->partyMenu->update(tick);
            break;
        case BATTLE_OPEN_BAG:
            if (pressed(B) && !menu->bag->partyOpen) {
                scene = BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
            }
            if (pressed(A) && menu->bag->partyOpen) {
                menu->bag->waitForOpenAnimation = false;
                menu->bag->waitForCloseAnimation = true;
                menu->bag->pressedBack = true;
                waitingForPartySwitch = true; //just prevents player from attacking after enemy, even if slower. should probably rename
                scene = BATTLE_WAIT_FOR_ENEMY_MOVE;
            }
            if (pressed(A) && (menu->bag->selected == 2 || menu->bag->selected == 3 || menu->bag->selected == 4) && isWildBattle) { // use gem
                if (party.size() < 3) { // party not full
                    if (menu->bag->selected == 2) { //emerald
                        emerald -= 1;
                        gemLevel = 1;
                    }
                    if (menu->bag->selected == 3) { //diamond
                        diamond -= 1;
                        gemLevel = 2;
                    }
                    if (menu->bag->selected == 4) { //ruby
                        ruby -= 1;
                        gemLevel = 0;
                    }
                    menu->bag->waitForOpenAnimation = false;
                    menu->bag->waitForCloseAnimation = true;
                    menu->bag->pressedBack = true;
                    waitingForPartySwitch = true; //just prevents player from attacking after enemy, even if slower. should probably rename
                    scene = BATTLE_USE_GEM;
                } else {
                    message->showMessage("party is full!");
                    menu->bag->waitForOpenAnimation = false;
                    menu->bag->waitForCloseAnimation = true;
                    menu->bag->pressedBack = true;
                    scene = BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
                }
            }
            menu->bag->update(tick, message);
            break;
        default:
            if (menu->partyMenu->waitForCloseAnimation || menu->partyMenu->waitForOpenAnimation) menu->partyMenu->update(tick);
            if (menu->bag->waitForCloseAnimation || menu->bag->waitForOpenAnimation) menu->bag->update(tick, message);
            break;
    }
    
    if (!waiting) {
        switch(scene) {
            case BATTLE_INTRO_TEXT:
                setNextEnemyPartyPimonIndex();
                setNextPartyPimonIndex();
                if (isWildBattle) {
                    scene = BATTLE_PARTY_NAME_TEXT;
                } else {
                    scene = BATTLE_INTRO_ANIMATION;
                }
                caught = false;
                break;
            case BATTLE_INTRO_ANIMATION:
                message->showMessage("Trainer would like to\nbattle!");
                scene = BATTLE_ENEMY_NAME_TEXT;
                break;
            case BATTLE_ENEMY_NAME_TEXT:
                msg = "Trainer sent out\n";
                message->showMessage(msg.append(getPimonData(party, enemyPartyIndex).name));
                scene = BATTLE_PARTY_NAME_TEXT;
                break; 
            case BATTLE_PARTY_NAME_TEXT:
                msg = "Go ";
                message->showMessage(msg.append(getPimonData(party, playerPartyIndex).name));
                scene = BATTLE_WAIT_FOR_INTRO_END;
                break;
            case BATTLE_WAIT_FOR_INTRO_END:
                scene = BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
                break;
            case BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT:
                animPlayer = 0;
                animEnemy = 64;
                animSwitched =  false;
                handlePlayerSelectActionInput(menu);
                break;
            case BATTLE_WAIT_FOR_PLAYER_MOVE_INPUT:
                handlePlayerSelectMoveInput();
                break;
            case BATTLE_RUN_AWAY:
                message->showMessage("you ran away!");
                scene = END_BATTLE;
                break;
            case BATTLE_DETERMINE_ORDER:
                if (getPimonData(enemyParty, enemyPartyIndex).speed > getPimonData(party, playerPartyIndex).speed) {
                    playerIsFirst = false;
                } else {
                    playerIsFirst = true;
                }

                scene = playerIsFirst ? BATTLE_WAIT_FOR_PLAYER_MOVE : BATTLE_WAIT_FOR_ENEMY_MOVE;
                break;
            case BATTLE_WAIT_FOR_PLAYER_MOVE:
                if (party.at(playerPartyIndex).status == SLEEPING) {
                    if ((rand() % 3) == 1) { // if woke up, 1/3 chance
                        msg = getPimonData(party, playerPartyIndex).name;
                        msg.append("\nwoke up and used\n");
                        msg.append(getPimonData(party, playerPartyIndex).moves.at(actionIndex).name);
                        msg.append("!");
                        damage = calcDamage(party.at(playerPartyIndex), getPimonData(enemyParty, enemyPartyIndex), getPimonData(party, playerPartyIndex).moves.at(actionIndex));
                        message->showMessage(msg);
                        party.at(playerPartyIndex).status = NONE;
                        scene = BATTLE_WAIT_FOR_PLAYER_DAMAGE;
                    } else {
                        msg = getPimonData(party, playerPartyIndex).name;
                        message->showMessage(msg.append("\nis sleeping!"));
                        scene = playerIsFirst ? BATTLE_WAIT_FOR_ENEMY_MOVE : BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
                    }
                } else if (party.at(playerPartyIndex).status == BURNED) {
                    if ((rand() % 5) == 1) { // if unburned, 1/5 chance
                        msg = getPimonData(party, playerPartyIndex).name;
                        msg.append("'s\nburn healed\nand used ");
                        msg.append(getPimonData(party, playerPartyIndex).moves.at(actionIndex).name);
                        msg.append("!");
                        damage = calcDamage(party.at(playerPartyIndex), getPimonData(enemyParty, enemyPartyIndex), getPimonData(party, playerPartyIndex).moves.at(actionIndex));
                        message->showMessage(msg);
                        party.at(playerPartyIndex).status = NONE;
                        scene = BATTLE_WAIT_FOR_PLAYER_DAMAGE;
                    } else {
                        msg = getPimonData(party, playerPartyIndex).name;
                        msg.append("'s burn\nreduces damage.\nused ");
                        msg.append(getPimonData(party, playerPartyIndex).moves.at(actionIndex).name);
                        msg.append("!");
                        damage = calcDamage(party.at(playerPartyIndex), getPimonData(enemyParty, enemyPartyIndex), getPimonData(party, playerPartyIndex).moves.at(actionIndex));
                        damage = damage/2;
                        message->showMessage(msg);
                        scene = BATTLE_WAIT_FOR_PLAYER_DAMAGE;
                    }
                } else {
                    msg = getPimonData(party, playerPartyIndex).name;
                    damage = calcDamage(party.at(playerPartyIndex), getPimonData(enemyParty, enemyPartyIndex), getPimonData(party, playerPartyIndex).moves.at(actionIndex));
                    message->showMessage(msg.append(" used\n").append(getPimonData(party, playerPartyIndex).moves.at(actionIndex).name).append("!"));
                }

                scene = BATTLE_WAIT_FOR_PLAYER_DAMAGE;
                break;
            case BATTLE_WAIT_FOR_ENEMY_MOVE:
                if (enemyParty.at(enemyPartyIndex).status == SLEEPING) {
                    if ((rand() % 3) == 1) { // if woke up, 1/3 chance
                        message->showMessage(msg.append("\nwoke up!"));
                        enemyParty.at(enemyPartyIndex).status = NONE;

                        msg = getPimonData(enemyParty, enemyPartyIndex).name;
                        msg.append("\nwoke up and used\n");
                        msg.append(getPimonData(enemyParty, enemyPartyIndex).moves.at(enemyMoveIndex).name);
                        msg.append("!");
                        damage = calcDamage(enemyParty.at(enemyPartyIndex), getPimonData(party, playerPartyIndex), getPimonData(enemyParty, enemyPartyIndex).moves.at(enemyMoveIndex));
                        message->showMessage(msg);
                        enemyParty.at(enemyMoveIndex).status = NONE;
                        scene = BATTLE_WAIT_FOR_ENEMY_DAMAGE;
                    } else {
                        msg = getPimonData(enemyParty, enemyPartyIndex).name;
                        message->showMessage(msg.append("\nis sleeping!"));
                        scene = playerIsFirst ? BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT : BATTLE_WAIT_FOR_PLAYER_MOVE;
                    }
                } else if (enemyParty.at(enemyPartyIndex).status == BURNED) {
                    if ((rand() % 5) == 1) { // if unburned, 1/5 chance
                        msg = getPimonData(enemyParty, enemyPartyIndex).name;
                        msg.append("'s\nburn healed\nand used ");
                        msg.append(getPimonData(enemyParty, enemyPartyIndex).moves.at(enemyMoveIndex).name);
                        msg.append("!");
                        damage = calcDamage(enemyParty.at(enemyPartyIndex), getPimonData(party, playerPartyIndex), getPimonData(enemyParty, enemyPartyIndex).moves.at(enemyMoveIndex));
                        message->showMessage(msg);
                        scene = BATTLE_WAIT_FOR_ENEMY_DAMAGE;
                    } else {
                        msg = getPimonData(enemyParty, enemyPartyIndex).name;
                        msg.append("'s burn\nreduces damage.\nused ");
                        msg.append(getPimonData(enemyParty, enemyPartyIndex).moves.at(enemyMoveIndex).name);
                        msg.append("!");
                        damage = calcDamage(enemyParty.at(enemyPartyIndex), getPimonData(party, playerPartyIndex), getPimonData(enemyParty, enemyPartyIndex).moves.at(enemyMoveIndex));
                        damage = damage/2;
                        message->showMessage(msg);
                        enemyParty.at(enemyMoveIndex).status = NONE;
                        scene = BATTLE_WAIT_FOR_ENEMY_DAMAGE;
                    }
                } else {
                    msg = getPimonData(enemyParty, enemyPartyIndex).name;
                    enemyMoveIndex = rand() % ((xpToLvl(enemyParty.at(0).xp)/5) + 1);
                    damage = calcDamage(enemyParty.at(enemyPartyIndex), getPimonData(party, playerPartyIndex), getPimonData(enemyParty, enemyPartyIndex).moves.at(enemyMoveIndex));
                    message->showMessage(msg.append(" used\n").append(getPimonData(enemyParty, enemyPartyIndex).moves.at(enemyMoveIndex).name).append("!"));
                    scene = BATTLE_WAIT_FOR_ENEMY_DAMAGE;
                }
                actionIndex = 0;
                break;
            case BATTLE_WAIT_FOR_PLAYER_DAMAGE:
                if (getPimonData(party, playerPartyIndex).moves.at(actionIndex).effect_id == SLEEP_ATTACK) {
                    if (enemyParty.at(enemyPartyIndex).status == SLEEPING) {
                        msg = getPimonData(enemyParty, enemyPartyIndex).name;
                        message->showMessage(msg.append("\nis already asleep..."));
                    } else if ((rand() % 2) == 1) { // 50/50 chance
                        msg = getPimonData(enemyParty, enemyPartyIndex).name;
                        message->showMessage(msg.append("\nfell asleep!"));
                        enemyParty.at(enemyPartyIndex).status = SLEEPING;
                    } else {
                        msg = getPimonData(enemyParty, enemyPartyIndex).name;
                        message->showMessage(msg.append("\nmanaged to stay\nawake!"));
                    }
                    scene = playerIsFirst ? BATTLE_WAIT_FOR_ENEMY_MOVE : BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
                } else if (getPimonData(party, playerPartyIndex).moves.at(actionIndex).effect_id == BURN_ATTACK) {
                    if (enemyParty.at(enemyPartyIndex).status == BURNED) {
                        msg = getPimonData(enemyParty, enemyPartyIndex).name;
                        message->showMessage(msg.append("\nis already burned..."));
                    } else if ((rand() % 2) == 1) { // 50/50 chance
                        msg = getPimonData(enemyParty, enemyPartyIndex).name;
                        message->showMessage(msg.append("\ngot burned!"));
                        enemyParty.at(enemyPartyIndex).status = BURNED;
                    } else {
                        msg = getPimonData(enemyParty, enemyPartyIndex).name;
                        message->showMessage(msg.append("\nmanaged to avoid\ngetting burned!"));
                    }
                    scene = playerIsFirst ? BATTLE_WAIT_FOR_ENEMY_MOVE : BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
                } else {
                    if (damage == 0) {
                        scene = playerIsFirst ? BATTLE_WAIT_FOR_ENEMY_MOVE : BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
                    } else {
                        enemyParty.at(enemyPartyIndex).hp--;
                        damage--;
                        if (enemyParty.at(enemyPartyIndex).hp == 0) {
                            msg = getPimonData(enemyParty, enemyPartyIndex).name;
                            message->showMessage(msg.append("\nhas fainted!"));
                            scene = BATTLE_WAIT_FOR_ENEMY_SWITCH;
                            party.at(playerPartyIndex).xp += (enemyParty.at(enemyPartyIndex).xp * 5);
                        }
                    }
                }
                break;
            case BATTLE_WAIT_FOR_ENEMY_DAMAGE:
                if (getPimonData(enemyParty, enemyPartyIndex).moves.at(enemyMoveIndex).effect_id == SLEEP_ATTACK) {
                    if (party.at(playerPartyIndex).status == SLEEPING) {
                        msg = getPimonData(party, playerPartyIndex).name;
                        message->showMessage(msg.append("\nis already asleep..."));
                    } else if ((rand() % 2) == 1) { // 50/50 chance
                        msg = getPimonData(party, playerPartyIndex).name;
                        message->showMessage(msg.append("\nfell asleep!"));
                        party.at(playerPartyIndex).status = SLEEPING;
                    } else {
                        msg = getPimonData(party, playerPartyIndex).name;
                        message->showMessage(msg.append("\nmanaged to stay\nawake!"));
                    }
                    scene = playerIsFirst ? BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT : BATTLE_WAIT_FOR_PLAYER_MOVE;
                } else if (getPimonData(enemyParty, enemyPartyIndex).moves.at(enemyMoveIndex).effect_id == BURN_ATTACK) {
                    if (party.at(playerPartyIndex).status == BURNED) {
                        msg = getPimonData(party, playerPartyIndex).name;
                        message->showMessage(msg.append("\nis already burned..."));
                    } else if ((rand() % 2) == 1) { // 50/50 chance
                        msg = getPimonData(party, playerPartyIndex).name;
                        message->showMessage(msg.append("\ngot burned!"));
                        party.at(playerPartyIndex).status = BURNED;
                    } else {
                        msg = getPimonData(party, playerPartyIndex).name;
                        message->showMessage(msg.append("\nmanaged to avoid\ngetting burned!"));
                    }
                    scene = playerIsFirst ? BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT : BATTLE_WAIT_FOR_PLAYER_MOVE;
                } else {
                    if (damage == 0) {
                        scene = playerIsFirst ? BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT : BATTLE_WAIT_FOR_PLAYER_MOVE;
                        if (waitingForPartySwitch) {
                            scene = BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
                            waitingForPartySwitch = false;
                        }
                    } else {
                        party.at(playerPartyIndex).hp--;
                        damage--;
                        if (party.at(playerPartyIndex).hp == 0) {
                            msg = getPimonData(party, playerPartyIndex).name;
                            message->showMessage(msg.append("\nhas fainted!"));
                            scene = BATTLE_WAIT_FOR_PLAYER_SWITCH;
                        }
                    }
                }
                break;
            case BATTLE_WAIT_FOR_PLAYER_SWITCH:
                if (animPlayer == -56) {
                    animSwitched = true;
                    setNextPartyPimonIndex();
                }
                if (animSwitched && animPlayer == 0) {
                    scene = BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
                }
                break;
            case BATTLE_WAIT_FOR_ENEMY_SWITCH:
                if (animEnemy == 120) {
                    animSwitched = true;
                    setNextEnemyPartyPimonIndex();
                }
                if (animSwitched && animEnemy == 64) {
                    scene = BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT;
                }
                break;
            case BATTLE_USE_GEM:
                msg = "PLAYER used a\nPico Gem!";
                message->showMessage(msg);
                scene = ((rand() % (4 - gemLevel)) != 1) ? BATTLE_USE_GEM_FAILED : BATTLE_USE_GEM_SUCCESS;
                break;
            case BATTLE_USE_GEM_SUCCESS:
                msg = "PLAYER caught\n";
                message->showMessage(msg.append(getPimonData(enemyParty, 0).name).append("!"));
                party.push_back(enemyParty.at(0));
                caught = true;
                caughtPimon[enemyParty.at(0).pimon_id-1] = true;
                scene = END_BATTLE;
                break; 
            case BATTLE_USE_GEM_FAILED:
                msg = "Shoot!\nIt got away!";
                message->showMessage(msg);
                scene = BATTLE_WAIT_FOR_ENEMY_MOVE;
                break; 
            case BATTLE_LOSE:
                message->showMessage("you lose!");
                scene = END_BATTLE;
                for (auto &tpimon : party) {
                    tpimon.hp = getMaxHp(tpimon.pimon_id, xpToLvl(tpimon.xp));
                }
                currentMap = 0;
                virtualCamera = {-240, -208};
                player->inGrass = false;
                break;
            case BATTLE_WIN:
                message->showMessage("you win!");
                scene = END_BATTLE;
                break;
            case END_BATTLE:
                animSwitched = false;
                MainScene = OVERWORLD;
                changeSong = true;
                waitingForStartAnimation = true;
                animPlayer = -56;
                animEnemy = 120;
                scene = BATTLE_INTRO_TEXT;

                for (auto &tpimon : party) {
                    if (xpToLvl(tpimon.xp) > 11 && (tpimon.pimon_id % 2 == 1)) { // if lvl 12 and haven't evolved
                        tpimon.pimon_id += 1;
                        caughtPimon[tpimon.pimon_id-1] = true;
                        msg = genericPimonData[tpimon.pimon_id - 1].name;
                        msg.append("\nevolved!");
                        message->showMessage(msg);
                    }
                }
                break;
        }
    }
}

void Battle::drawPlayerPartySprite(int32_t _x, int32_t _y) {
    setPimonBackBuffer(party.at(playerPartyIndex).pimon_id);

    if (scene == BATTLE_WAIT_FOR_ENEMY_DAMAGE && !waiting){
        if (time() % 250 < 125) {
            draw56sprite(_x, _y);
        }
    } else {
        if (scene == BATTLE_WAIT_FOR_PLAYER_MOVE && party.at(playerPartyIndex).status == NONE) {
            draw56sprite(_x+8, _y);
        } else {
            draw56sprite(_x, _y);
        }
    }
}

void Battle::drawEnemyPartySprite(int32_t _x, int32_t _y) {
    setPimonBuffer(enemyParty.at(enemyPartyIndex).pimon_id);

    if (caught) return;

    if (scene == BATTLE_WAIT_FOR_PLAYER_DAMAGE && !waiting){
        if (time() % 250 < 125) {
            draw56sprite(_x, _y);
        }
    } else {
        if (scene == BATTLE_WAIT_FOR_ENEMY_MOVE && enemyParty.at(enemyPartyIndex).status == NONE) {
            draw56sprite(_x-8, _y);
        } else {
            if (scene != BATTLE_USE_GEM_SUCCESS && scene != BATTLE_USE_GEM_FAILED) {
                draw56sprite(_x, _y);
            }
        }
    }
}

void Battle::drawCharacter1Back(int32_t _x, int32_t _y) {
    switch(playerAvatar) {
        case 1:
            spritesheet(character_1_back_buffer);
            break;
        case 2:
            spritesheet(character_2_back_buffer);
            break;
        case 3:
            spritesheet(character_3_back_buffer);
            break;
    }
    draw56sprite(_x, _y);
}

void Battle::drawEnemyTrainer(int32_t _x, int32_t _y) {
    spritesheet(enemyFront);
    draw56sprite(_x, _y);
}

void Battle::drawActions() {
    text("Fight", 10, 94);
    text("Party", 10, 106);
    text("Bag", 70, 94);
    text("Run", 70, 106);

    if (scene != BATTLE_OPEN_PARTY && scene != BATTLE_OPEN_BAG) {
        int cursorX = (actionIndex == 0 || actionIndex == 2) ? 4 : 64;
        int cursorY = (actionIndex == 0 || actionIndex == 1) ? 94 : 106;
        vline(cursorX, cursorY, 8);
        vline(cursorX+1, cursorY+1, 6);
        vline(cursorX+2, cursorY+2, 4);
        vline(cursorX+3, cursorY+3, 2);
    }
}

void Battle::drawMoves() {
    int32_t lvl = xpToLvl(party.at(playerPartyIndex).xp);
    if (lvl > 0)  text(getPimonData(party, playerPartyIndex).moves.at(0).name, 10, 94);
    if (lvl > 4)  text(getPimonData(party, playerPartyIndex).moves.at(1).name, 70, 94);
    if (lvl > 9)  text(getPimonData(party, playerPartyIndex).moves.at(2).name, 10, 106);
    if (lvl > 14) text(getPimonData(party, playerPartyIndex).moves.at(3).name, 70, 106);

    int cursorX = (actionIndex == 0 || actionIndex == 2) ? 4 : 64;
    int cursorY = (actionIndex == 0 || actionIndex == 1) ? 94 : 106;
    vline(cursorX, cursorY, 8);
    vline(cursorX+1, cursorY+1, 6);
    vline(cursorX+2, cursorY+2, 4);
    vline(cursorX+3, cursorY+3, 2);
}

void Battle::drawMainView() {
    std::string txt = "";

    text(getPimonData(enemyParty, enemyPartyIndex).name,1,1);
    txt = "L: ";
    text(txt.append(str(xpToLvl(enemyParty.at(enemyPartyIndex).xp))),1,9);
    txt = "";
    if (enemyParty.at(enemyPartyIndex).status == SLEEPING) txt = "SLP";
    if (enemyParty.at(enemyPartyIndex).status == CONFUSED) txt = "CNF";
    if (enemyParty.at(enemyPartyIndex).status == BURNED) txt = "BRN";
    text(txt,30,9);
    txt = "H: ";
    txt.append(str(enemyParty.at(enemyPartyIndex).hp));
    txt.append("/");
    txt.append(str(getMaxHp(enemyParty.at(enemyPartyIndex).pimon_id, xpToLvl(enemyParty.at(enemyPartyIndex).xp))));
    text(txt,1,17);

    text(getPimonData(party, playerPartyIndex).name,60,64);
    txt = "L: ";
    text(txt.append(str(xpToLvl(party.at(playerPartyIndex).xp))),60,72);
    txt = "";
    if (party.at(playerPartyIndex).status == SLEEPING) txt = "SLP";
    if (party.at(playerPartyIndex).status == CONFUSED) txt = "CNF";
    if (party.at(playerPartyIndex).status == BURNED) txt = "BRN";
    text(txt,90,72);
    txt = "H: ";
    txt.append(str(party.at(playerPartyIndex).hp));
    txt.append("/");
    txt.append(str(getMaxHp(party.at(playerPartyIndex).pimon_id, xpToLvl(party.at(playerPartyIndex).xp))));
    text(txt,60,80);

    drawPlayerPartySprite(animPlayer, 32);
    drawEnemyPartySprite(animEnemy, 0);
}

void Battle::draw(uint32_t tick, Menu *menu) {
    pen(15,15,15);
    clear();
    drawWindow(0, 88, 120, 32);

    switch(scene) {
        // case BATTLE_INTRO_TEXT:
        case BATTLE_INTRO_ANIMATION:
        case BATTLE_ENEMY_NAME_TEXT:
        case BATTLE_PARTY_NAME_TEXT:
            drawCharacter1Back(animPlayer, 32);
            drawEnemyTrainer(animEnemy, 0);
            break;
        // case BATTLE_WAIT_FOR_INTRO_END:
            // drawMainView();
            // break;
        case BATTLE_WAIT_FOR_PLAYER_ACTION_INPUT:
            drawMainView();
            drawActions();
            if (menu->partyMenu->waitForCloseAnimation || menu->partyMenu->waitForOpenAnimation) menu->partyMenu->draw(tick);
            if (menu->bag->waitForCloseAnimation || menu->bag->waitForOpenAnimation) menu->bag->draw(tick);
            break;
        case BATTLE_WAIT_FOR_PLAYER_MOVE_INPUT:
            drawMainView();
            drawMoves();
            if (menu->partyMenu->waitForCloseAnimation || menu->partyMenu->waitForOpenAnimation) menu->partyMenu->draw(tick);
            if (menu->bag->waitForCloseAnimation || menu->bag->waitForOpenAnimation) menu->bag->draw(tick);
            break;
        // case BATTLE_RUN_AWAY:
        // case END_BATTLE:
        //     drawMainView();
        //     break;
        case BATTLE_OPEN_PARTY:
            drawMainView();
            drawActions();
            menu->partyMenu->draw(tick);
            break;
        case BATTLE_OPEN_BAG:
            drawMainView();
            drawActions();
            menu->bag->draw(tick);
            break;
        default:
            drawMainView();
            if (menu->partyMenu->waitForCloseAnimation || menu->partyMenu->waitForOpenAnimation) menu->partyMenu->draw(tick);
            if (menu->bag->waitForCloseAnimation || menu->bag->waitForOpenAnimation) menu->bag->draw(tick);
            break;
    }
}
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"
#include "stdbool.h"

/*Handle the keyboard events*/
extern void KeyboardManager(SDL_Event event, GameState *gameState, fighter *player,fighter *enemy,background* bg, Time *T); //Handles the keyboard events

/*Animate the game*/
    /*LEFT KEY*/
extern void MovePlayerLeft(fighter *player,fighter *enemy, background *bg, Time *T);
extern void AnimatePlayerLeft(fighter *player);

    /*RIGHT KEY*/
extern void MovePlayerRight(fighter *player, fighter *enemy, background *bg, Time *T);
extern void AnimatePlayerRight(fighter *player);

    /*DOWN KEY*/
extern void AnimatePlayerDown(fighter *player);

    /*UP KEY*/
extern void AnimatePlayerUp(fighter *player, Time *T);

    /*KICKING KEY*/
extern void AnimatePlayerKick(fighter *player,fighter *enemy, Time *T);

extern void MoveEnemyRight(fighter *enemy, fighter *player, Time *T);

extern void MoveEnemyLeft(fighter *enemy, fighter *player, Time *T);

extern bool collision(SDL_Rect A, SDL_Rect B);

extern void PlayerHitEnemy(fighter *player, fighter *enemy);

#endif //EVENT_MANAGER_H

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"

/*Handle the keyboard events*/
extern void KeyboardManager(SDL_Event event, GameState *gameState, fighter *player,background* bg, Time *T); //Handles the keyboard events

/*Animate the game*/
    /*LEFT KEY*/
extern void MovePlayerLeft(fighter *player, background *bg, Time *T);
extern void AnimatePlayerLeft(fighter *player);

    /*RIGHT KEY*/
extern void MovePlayerRight(fighter *player, background *bg, Time *T);
extern void AnimatePlayerRight(fighter *player);

    /*DOWN KEY*/
extern void AnimatePlayerDown(fighter *player);

    /*UP KEY*/
extern void AnimatePlayerUp(fighter *player, Time *T);

    /*KICKING KEY*/
extern void AnimatePlayerKick(fighter *player,Time *T);

extern void AnimateEnemyRight(fighter *enemy, fighter *player, Time *T);

extern void AnimateEnemyRight(fighter *enemy, fighter *player, Time *T);


#endif //EVENT_MANAGER_H

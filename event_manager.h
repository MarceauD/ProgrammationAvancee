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
    extern void AnimateGameLeft(fighter *player, background *bg, Time *T);
    
    /*RIGHT KEY*/
    extern void AnimateGameRight(fighter *player, background *bg, Time *T);
    
    /*DOWN KEY*/
    extern void AnimateGameDown(fighter *player, Time *T);
    
    /*UP KEY*/
    extern void AnimateGameUp(fighter *player, Time *T);
    
    /*KICKING KEY*/
    extern void AnimateGameKick(fighter *player,Time *T);


#endif //EVENT_MANAGER_H

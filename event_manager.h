#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "defines.h"
#include "SDL/SDL.h"
#include "graphics.h"
#include "gamestate.h"

extern void KeyboardManager(SDL_Event event, GameState *gameState, fighter *player,background* bg, Time *T); //Handles the keyboard events

extern void AnimateGameLeft(fighter *player, background *bg, Time *T); //Animate the game when left key is pushed
extern void AnimateGameRight(fighter *player, background *bg, Time *T); //Animate the game when right key is pushed
extern void AnimateGameDown(fighter *player, Time *T); //Animate the game when down key is pushed
extern void AnimateGameUp(fighter *player, Time *T); //Animate the game when up key is pushed
extern void AnimateGameKick(fighter *player,Time *T); //Animate the game when fighter wants to kick
#endif //EVENT_MANAGER_H

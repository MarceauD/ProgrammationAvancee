#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"
#include "stdbool.h"
#include "animations.h"

/*Handle the keyboard events during the game*/
extern void KeyboardManagerGame(SDL_Event event, GameState *gameState, fighter *player,fighter *enemy,fighter * enemy_r,background* bg, Time *T);

/*Handle the keyboard events during the pause*/
extern void KeyboardManagerPause(SDL_Event Event, GameState *G);

/*Handle the keyboard events during the menu*/
extern void KeyboardManagerMenu(SDL_Event event, GameState *G);

/*Hande the keyboard events during the end menu*/
extern void KeyboardManagerEndMenu(SDL_Event event, GameState *gameState);

#endif //KEYBOARD_H

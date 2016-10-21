#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"
#include "stdbool.h"
#include "animations.h"

/*Handle the keyboard events*/
extern void KeyboardManagerGame(SDL_Event event, GameState *gameState, fighter *player,fighter *enemy,background* bg, Time *T);
extern void KeyboardManagerPause(SDL_Event Event, GameState *G);

#endif //EVENT_MANAGER_H

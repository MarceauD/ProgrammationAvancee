#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"
#include "stdbool.h"

/*Handle the keyboard events*/
extern void KeyboardManager(SDL_Event event, GameState *gameState, fighter *player,fighter *enemy,background* bg, Time *T); 

#endif //EVENT_MANAGER_H

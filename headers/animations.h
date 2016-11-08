#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"
#include "stdbool.h"
#include "keyboard.h"
#include "event_manager.h"

extern void AnimatePlayerLeft(fighter *player);

extern void AnimatePlayerRight(fighter *player);

extern void AnimatePlayerDown(fighter *player);

extern void AnimatePlayerUp(fighter *player, Time *T);

extern void AnimatePlayerKick(fighter *player,fighter *enemy, Time *T, int delay);

extern void AnimatePlayerDeath(fighter *player, Time *T);

extern void CheckAnimations(fighter *player, fighter *enemy, Time *T);


#endif //ANIMATIONS_H

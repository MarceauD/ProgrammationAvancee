#ifndef MOVING_H
#define MOVING_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"
#include "stdbool.h"
#include "keyboard.h"
#include "animations.h"


extern void MovePlayerLeft(fighter *player,fighter *enemy, background *bg, Time *T);

extern void MovePlayerRight(fighter *player, fighter *enemy, background *bg, Time *T);

extern void MoveEnemyRight(fighter *enemy, fighter *player, Time *T);

extern void MoveEnemyLeft(fighter *enemy, fighter *player, Time *T);

#endif //MOVING_H

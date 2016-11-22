#ifndef MOVING_H
#define MOVING_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"
#include "stdbool.h"
#include "keyboard.h"
#include "animations.h"

/*move the player or the background to the left*/
extern void MovePlayerLeft(fighter *player,fighter *enemy, background *bg, Time *T, GameState *gs);

/*move the player or the background to the right*/
extern void MovePlayerRight(fighter *player, fighter *enemy, background *bg, Time *T);

/*move the enemy right*/
extern void MoveEnemyRight(fighter *enemy, fighter *player, Time *T);

/*move the enemy left*/
extern void MoveEnemyLeft(fighter *enemy, fighter *player, Time *T);

/*in case of a animation caused by the position of the player ( end of levels )*/
extern void AnimatePlayer(fighter * player, Time *T, background * bg, GameState *gs);

#endif //MOVING_H

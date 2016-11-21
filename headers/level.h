#ifndef LEVEL_H
#define LEVEL_H

#include "graphics.h"
#include "gamestate.h"
#include <stdbool.h>
#include <stdio.h>
#include "SDL.h"

fighter * whichFighter(fighter enemyLeft[ENEMYS_LVL1]);
void MoveEnemys(fighter enemyLeft[ENEMYS_LVL1],fighter *player, Time *T, Time *T1,bool launchEnemy[ENEMYS_LVL1], int *k);
void BlitEnemys(fighter enemyLeft[ENEMYS_LVL1], SDL_Surface * screen, bool launchEnemy[ENEMYS_LVL1],Time *T);

#endif //LEVEL_H

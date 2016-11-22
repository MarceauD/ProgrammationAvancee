#ifndef LEVEL_H
#define LEVEL_H

#include "graphics.h"
#include "gamestate.h"
#include <stdbool.h>
#include <stdio.h>
#include "SDL.h"

/*returns which fighter is the first to encounter the player*/
extern fighter * whichFighter(fighter enemyLeft[ENEMYS_LVL1]);

/*move all the enemies according to their positions and actions*/
extern void MoveEnemies(fighter enemyLeft[ENEMYS_LVL1],fighter *player, Time *T, Time *T1,bool launchEnemy[ENEMYS_LVL1], int *k);

/*blit all the enemies if they are alive and already launched*/
extern void BlitEnemies(fighter enemyLeft[ENEMYS_LVL1], SDL_Surface * screen, bool launchEnemy[ENEMYS_LVL1],Time *T);

/*move to the next level*/
extern void ChangeLevel(fighter *player, background *bg, GameState *gs);

#endif //LEVEL_H

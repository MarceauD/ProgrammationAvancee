#ifndef LEVEL_H
#define LEVEL_H

#include "graphics.h"
#include "gamestate.h"
#include <stdbool.h>
#include <stdio.h>
#include "SDL.h"

/*returns which fighter is the first to encounter the player*/
extern fighter * whichFighter(fighter enemyLeft[ENEMIES_LVL1]);

/*move all the enemies according to their positions and actions*/
extern void MoveEnemies(fighter enemyLeft[ENEMIES_LVL1],fighter *player, Time *T, Time *T1,bool launchEnemy[ENEMIES_LVL1], int *k,int TimeBetweenEnemies[ENEMIES_LVL1]);

extern void MoveEnemiesLeft(fighter enemyRight[ENEMIES_LVL2], fighter *player, Time *T, Time *T1,bool launchEnemyRight[ENEMIES_LVL2], int *cpt, int TimeBetweenEnemiesRight[ENEMIES_LVL2]);

/*blit all the enemies if they are alive and already launched*/
extern void BlitEnemies(fighter enemyLeft[ENEMIES_LVL1], SDL_Surface * screen, bool launchEnemy[ENEMIES_LVL1],Time *T);

/*move to the next level*/
extern void ChangeLevel(fighter *player, background *bg, GameState *gs);

extern void resetTabEnemies(fighter enemies[ENEMIES_LVL1]);

extern void resetTabLaunch(bool launchEnemy[ENEMIES_LVL1]);

#endif //LEVEL_H

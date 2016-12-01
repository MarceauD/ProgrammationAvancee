#ifndef LEVEL_H
#define LEVEL_H

#include "graphics.h"
#include "gamestate.h"
#include <stdbool.h>
#include <stdio.h>
#include "SDL.h"

/*returns which fighter is the first to encounter the player*/
extern fighter * whichFighter(int N,fighter enemyLeft[N]);

/*move all the enemies according to their positions and actions*/
extern void MoveEnemies(int N,fighter enemyLeft[N],fighter *player, Time *T, Time *T1,bool launchEnemy[N], int *k,int TimeBetweenEnemies[N]);

extern void MoveEnemiesLeft(int N,fighter enemyRight[N], fighter *player, Time *T, Time *T1,bool launchEnemyRight[N], int *cpt, int TimeBetweenEnemiesRight[N]);

/*blit all the enemies if they are alive and already launched*/
extern void BlitEnemies(int N,fighter enemyLeft[N], SDL_Surface * screen, bool launchEnemy[N],Time *T);

/*move to the next level*/
extern void ChangeLevel(fighter *player, background *bg, GameState *gs);

extern void resetTabEnemies(int N,fighter enemies[N]);

extern void resetTabLaunch(int N,bool launchEnemy[N]);

#endif //LEVEL_H

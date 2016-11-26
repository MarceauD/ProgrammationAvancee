#ifndef CLEANING_FUNCTIONS_H
#define CLEANING_FUNCTIONS_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"
#include "stdbool.h"
#include "keyboard.h"
#include "moving.h"
#include "event_manager.h"
#include "animations.h"
#include "moving.h"
#include "queue.h"
#include "interface.h"
#include "level.h"

extern GameState gameState;
extern background bg;
extern LPV LPView;
extern Pause P;

extern Time T;
extern Time T1;

extern bool allDead;
extern bool createdEnemyl;
extern bool cleanedEnemyl;
extern bool cleanedl[ENEMIES_LVL1];
extern bool createdl[ENEMIES_LVL1];
extern bool launchEnemyl[ENEMIES_LVL1];

extern int k;
extern int i;
extern int TimeBetweenEnemies[ENEMIES_LVL1];

extern SDL_Event event;
extern SDL_Surface *screen;
extern SDL_Surface * icon;

extern fighter enemyl;
extern fighter enemyLeft[ENEMIES_LVL1];
extern fighter player;
extern fighter demo;
extern fighter *temp_enemy_right;






void InitGame (/*GameState gameState,fighter player,fighter demo,background bg,Time T,LPV LPView,Pause P,bool allDead,int k,SDL_Event event,fighter enemy,bool createdEnemy, bool cleanedEnemy, int i,int TimeBetweenEnemies*/);
void CleanVariables(SDL_Surface *screen, fighter player,fighter enemy,fighter enemyLeft[ENEMIES_LVL1],bool cleaned[ENEMIES_LVL1], bool created[ENEMIES_LVL1], background bg, LPV LPView, Pause P, SDL_Surface * icon);

#endif //CLEANING_FUNCTIONS_H

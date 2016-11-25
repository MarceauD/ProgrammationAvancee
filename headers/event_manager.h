#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"
#include "stdbool.h"
#include "keyboard.h"
#include "moving.h"

extern bool collision(SDL_Rect A, SDL_Rect B);

extern void PlayerHitEnemy(fighter *player, fighter *enemy);

extern void EnemyAttackRight(fighter *enemy, fighter *player, Time *T);

extern void EnemyAttackLeft(fighter *enemy,fighter * player, Time *T);
#endif //EVENT_MANAGER_H


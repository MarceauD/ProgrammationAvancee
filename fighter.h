#ifndef FIGHTER_H
#define FIGHTER_H

#include "SDL/SDL.h"
#include "stdbool.h"

struct fighter{
    SDL_Surface* sprite;
    SDL_Rect source;
    SDL_Rect rcSprite; //sprite's position on screen
    int lifepoints;
    int damage;
    SDL_Rect hitbox;
};

typedef struct fighter fighter;

extern fighter init_fighter();
extern bool isAlive(fighter F);
extern int read_lifepoints(fighter F);
extern int read_damage(fighter F);
extern fighter write_lifepoints(int lifepoints, fighter F);
extern fighter write_damage(int damage, fighter F);
extern void FreeFighter(fighter F);


#endif // FIGHTER_H

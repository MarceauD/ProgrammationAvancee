#ifndef FIGHTER_H
#define FIGHTER_H

#include "SDL/SDL.h"
#include "stdbool.h"
#include "defines.h"


enum rotation{
    LEFT,
    RIGHT,
};

enum position{
    STANDING,
    KNELT,
};

struct fighter{
    SDL_Surface* sprite;
    SDL_Rect source;
    SDL_Rect rcSprite; //sprite's position on screen
    int lifepoints;
    int damage;
    enum rotation r; //which side does the fighters look towards 0 : LEFT, 1 : RIGHT, default is right
    enum position p; //standing up : 1, kneeling down : 0
    SDL_Rect hitbox;
};

typedef struct fighter fighter;


struct background{
    SDL_Surface* surface;
    SDL_Rect source;
    SDL_Rect rcBG;
};

typedef struct background background;

/*STRUCT FIGHTER OPERATIONS*/
extern fighter init_fighter(); //initialise a fighter structure
extern bool isAlive(fighter F); //check if the fighter's lifepoints are down to zero
extern int read_lifepoints(fighter F); //return the amount of lifepoints that a fighter has
extern int read_damage(fighter F); //return the current damage that a fighter can deal
extern fighter write_lifepoints(int lifepoints, fighter F); //changes the amount of lifepoints of a fighter
extern fighter write_damage(int damage, fighter F); //changes the amount of damage that a fighter deals
extern void FreeFighter(fighter F); //free the memory used by the fighter structure

/*STRUCT BACKGROUND OPERATIONS*/
extern background init_background(); //initialise a background structure
extern void FreeBackground(background bg); //free the memory used by the background structure


extern SDL_Surface* loadImage(SDL_Surface* sprite,char* file); //load a BMP Image

#endif // FIGHTER_H

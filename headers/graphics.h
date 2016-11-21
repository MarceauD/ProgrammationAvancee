#include "SDL.h"
#include "stdbool.h"
#include "defines.h"
#include "gamestate.h"
#include "animations.h"

#ifndef FIGHTER_H
#define FIGHTER_H

enum rotation{
    LEFT,
    RIGHT,
};

enum fighter_kind{
    PLAYER,
    GRABBING_ENEMY,
    PUNCHING_ENEMY,
    KNIVES_THROWING_ENEMY,
};

typedef enum fighter_kind fighter_kind;

enum position{
    STANDING,
    KNELT,
    JUMP,
    KICK,
    DYING,
    DEAD,
    ANIMATED,
};

struct fighter{
    SDL_Surface* sprite;
    SDL_Rect source;

    /*sprite's position on screen*/
    SDL_Rect rcSprite;
    int lifepoints;
    int damage;

    enum rotation r;

    enum fighter_kind f;

    enum position p;
    SDL_Rect hitbox;

    int previousTime;
};

typedef struct fighter fighter;


struct background{
    SDL_Surface* surface;
    SDL_Rect source;
    SDL_Rect rcBG;
};

typedef struct background background;

/*STRUCT FIGHTER OPERATIONS*/
/*initialise a fighter structure*/
extern fighter init_fighter(fighter_kind FK);

/*check if the fighter's lifepoints are down to zero*/
extern bool isAlive(fighter F);

/*return the amount of lifepoints that a fighter has*/
extern int read_lifepoints(fighter F);

/*return the current damage that a fighter can deal*/
extern int read_damage(fighter F);

/*changes the amount of lifepoints of a fighter*/
extern fighter write_lifepoints(int lifepoints, fighter F);

/*changes the amount of damage that a fighter deals*/
extern fighter write_damage(int damage, fighter F);

/*free the memory used by the fighter structure*/
extern void FreeFighter(fighter F);

/*STRUCT BACKGROUND OPERATIONS*/
/*initialise a background structure*/
extern background init_background();

/*free the memory used by the background structure*/
extern void FreeBackground(background bg);

/*load a BMP Image*/
extern SDL_Surface* loadImage(SDL_Surface* sprite,char* file);


extern void BlitImages(background *bg, fighter *player, SDL_Surface *screen, Time *T);

extern void BlitImagesConditions(fighter *player, SDL_Surface *screen, Time *T);
#endif // FIGHTER_H

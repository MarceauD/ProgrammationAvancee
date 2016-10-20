#ifndef INTERFACE_H
#define INTERFACE_H

#include "gamestate.h"
#include "defines.h"
#include "graphics.h"
#include "SDL.h"

struct LifePointsView{
     SDL_Surface *sprite;
     SDL_Rect source;
     SDL_Rect rcSprite;
};

typedef struct LifePointsView LPV;

LPV init_LPV(fighter player);
extern void ViewLifepoints(LPV *LifePointsView, fighter player, SDL_Surface *screen);
extern void ViewScore(GameState GS);
extern void ViewTime(GameState GS);
extern void FreeLPV(LPV Lifepoints);


#endif //INTERFACE_H

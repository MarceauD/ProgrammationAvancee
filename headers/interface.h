#ifndef INTERFACE_H
#define INTERFACE_H

#include "gamestate.h"
#include "defines.h"
#include "graphics.h"
#include "gamestate.h"
#include "keyboard.h"

#include "SDL.h"

struct Pause{
    SDL_Surface *sprite;
    SDL_Rect rcSprite;
};

typedef struct Pause Pause;

struct LifePointsView{
     SDL_Surface *sprite;
     SDL_Rect source;
     SDL_Rect rcSprite;
};

typedef struct LifePointsView LPV;

extern LPV init_LPV(fighter player);
extern void ViewLifepoints(LPV *LifePointsView, fighter player, SDL_Surface *screen);
extern void ViewScore(GameState GS);
extern void ViewTime(GameState GS);
extern void FreeLPV(LPV Lifepoints);

extern Pause init_Pause();
extern void PauseGame(Pause P, GameState *G, SDL_Surface *screen);
extern void FreePause(Pause P);

extern void Menu(SDL_Surface * menu, SDL_Surface * Rect, SDL_Rect rcRect, SDL_Rect *source,Time *T, SDL_Event event, GameState *gameState,SDL_Surface * screen, fighter * demo);
extern void init_Menu(SDL_Rect *rcRect, SDL_Rect *source, fighter *demo);
#endif //INTERFACE_H

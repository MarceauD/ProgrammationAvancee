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

/*initialize a LifePointsView structure*/
extern LPV init_LPV(fighter player);

/*blit the LifePointView according to the player lifepoints*/
extern void ViewLifepoints(LPV *LifePointsView, fighter player, SDL_Surface *screen);

/*blit the score*/
extern void ViewScore(GameState GS);

/*blit the time since the beginning of the game*/
extern void ViewTime(GameState GS);

/*free a LifePointsView structure*/
extern void FreeLPV(LPV Lifepoints);

/*initialize a Pause structure*/
extern Pause init_Pause();

/*blit the pause image and handle the keyboard while pause is on*/
extern void PauseGame(Pause P, GameState *G, SDL_Surface *screen);

/*free the memory allowed to a Pause structure*/
extern void FreePause(Pause P);

/*handle the menu at the beginning of the game, blit images, animate the demo fighter and handle keyboard events*/
extern void Menu(SDL_Surface * menu, SDL_Surface * Rect, SDL_Rect rcRect, SDL_Rect *source,Time *T, SDL_Event event, GameState *gameState,SDL_Surface * screen, fighter * demo);

/*initialize the menu ( could also be done with a structure as for LPV, or Pause )*/
extern void init_Menu(SDL_Rect *rcRect, SDL_Rect *source, fighter *demo);

extern void EndMenuVictory(SDL_Surface *screen,GameState * gameState, Time *T);

#endif //INTERFACE_H

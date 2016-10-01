#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "defines.h"
#include "gamestate.h"
#include "fighter.h"

#include "SDL/SDL.h"



bool contact(SDL_Rect * a, SDL_Rect * b){
  bool found;
  if(a->x == b->x - SPRITE_WIDTH || b->x + SPRITE_WIDTH == a->x){
    found = true;
  }
  return found;
}

int main(int argc, char *argv[]){


    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        printf("Unable to init SDL :%s",SDL_GetError());
        return 1;
    }


    SDL_WM_SetCaption(GAME_TITLE,GAME_TITLE);

    SDL_Surface* screen, *bg, *bgGrass;
    SDL_Rect rcBG, rcBGGrass;
    fighter player;
    GameState gameState;
    Uint8 *keystate;

    SDL_Event event;

    gameState = DefaultGameState();

    player = init_fighter();


    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    if (!screen){
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    bg = SDL_CreateRGBSurface(0,BACKGROUND_WIDTH,BACKGROUND_HEIGHT,32,0,0,0,0);

    if(!bg){
        printf("Unable to load the background %s\n",SDL_GetError());
        return 1;
    }

    bgGrass = SDL_CreateRGBSurface(0,BACKGROUND_WIDTH,BOTTOM_HEIGHT,32,0,0,0,0);

    if(!bgGrass){
        printf("Unable to load the grass %s\n",SDL_GetError());
        return 1;
    }

    SDL_FillRect(bg,NULL,SDL_MapRGB(bg->format, 0,0,255));
    SDL_FillRect(bgGrass,NULL,SDL_MapRGB(bgGrass->format,0,255,0));

    rcBG.x = 0;
    rcBG.y = TOP_HEIGHT ;

    rcBGGrass.x = 0;
    rcBGGrass.y = SCREEN_HEIGHT - BOTTOM_HEIGHT;

    while(!isOver(gameState)){
      if (SDL_PollEvent(&event)){
	switch (event.type){
	case SDL_QUIT:
	  gameState.EndProgram = true;;
	  break;
	  }

     }

      keystate = SDL_GetKeyState(NULL);
      if(keystate[SDLK_ESCAPE]){
	gameState.EndProgram = true;
      }
       if (keystate[SDLK_LEFT]){
        player.rcSprite.x = player.rcSprite.x - 1;
      }
      if (keystate[SDLK_RIGHT]){
	player.rcSprite.x = player.rcSprite.x + 1;
      }
      if (player.rcSprite.x < 0 ){
	player.rcSprite.x = 0;
      }
    if (player.rcSprite.x > SCREEN_WIDTH - SPRITE_WIDTH){
        player.rcSprite.x = SCREEN_WIDTH - SPRITE_WIDTH;
    }


      SDL_BlitSurface(bg,NULL,screen,&rcBG);
      SDL_BlitSurface(player.sprite,player.source,screen,&player.rcSprite);
      SDL_BlitSurface(bgGrass,NULL,screen,&rcBGGrass);

      SDL_UpdateRect(screen, 0, 0, 0, 0);

    }

    SDL_FreeSurface(bg);
    SDL_FreeSurface(screen);
    FreeFighter(player);
    SDL_FreeSurface(bgGrass);

    SDL_Quit();

    return 0;
}

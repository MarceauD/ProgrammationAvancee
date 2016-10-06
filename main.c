#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "defines.h"
#include "gamestate.h"
#include "fighter.h"

#include "SDL/SDL.h"


//test if a SDL_Rect structure touches another ( USELESS FOR NOW )
bool contact(SDL_Rect * a, SDL_Rect * b){
  return (a->x == b->x - SPRITE_WIDTH || b->x + SPRITE_WIDTH == a->x);
}

//handle the event generates by the keyboard
void KeyboardManager(SDL_Event event, GameState *gameState, fighter *player,SDL_Rect* rcSrc){
    Uint8 *keystate;
    if (SDL_PollEvent(&event)){
	switch (event.type){
	case SDL_QUIT:
	  gameState->EndProgram = true;
	  break;
	  }
     }
      keystate = SDL_GetKeyState(NULL);
      if(keystate[SDLK_ESCAPE]){
	gameState->EndProgram = true;
      }
       if (keystate[SDLK_LEFT]){
        rcSrc->x = rcSrc->x - 1;
        if (rcSrc->x <= 0){
            rcSrc->x = 0;
            player->rcSprite.x = player->rcSprite.x - 1;
            if(player->rcSprite.x <= 0){
                player->rcSprite.x = 0;
            }
        }
      }
      if (keystate[SDLK_RIGHT]){
        rcSrc->x = rcSrc->x + 1;
        if (rcSrc->x > BACKGROUND_WIDTH - SCREEN_WIDTH){
            rcSrc->x = BACKGROUND_WIDTH - SCREEN_WIDTH;
            player->rcSprite.x = player->rcSprite.x + 1;
            if(player->rcSprite.x > SCREEN_WIDTH - SPRITE_WIDTH){
                player->rcSprite.x = SCREEN_WIDTH - SPRITE_WIDTH;
            }
        }
      }

}

int main(int argc, char *argv[]){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        printf("Unable to init SDL :%s",SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption(GAME_TITLE,GAME_TITLE);

    SDL_Surface* screen, *bg, *bgGrass,*temp;
    SDL_Rect rcBG, rcSrc;
    fighter player;
    GameState gameState;
    SDL_Event event;

    gameState = DefaultGameState();
    player = init_fighter();

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    if (!screen){
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    temp = SDL_LoadBMP("background.bmp");
    bg = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp); /// temporary image

    if(!bg){
        printf("Unable to load the background %s\n",SDL_GetError());
        return 1;
    }

    bgGrass = SDL_CreateRGBSurface(0,BACKGROUND_WIDTH,BOTTOM_HEIGHT,32,0,0,0,0);

    if(!bgGrass){
        printf("Unable to load the grass %s\n",SDL_GetError());
        return 1;
    }


    rcBG.x = 0;
    rcBG.y = TOP_HEIGHT ;

    rcSrc.x = BACKGROUND_WIDTH / 2;
    rcSrc.y = 0;
    rcSrc.w = SCREEN_WIDTH;
    rcSrc.h = SCREEN_HEIGHT;

    while(!isOver(gameState)){

        KeyboardManager(event,&gameState,&player,&rcSrc);


      SDL_BlitSurface(bg,&rcSrc,screen,&rcBG);
      SDL_BlitSurface(player.sprite,NULL,screen,&player.rcSprite);

      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_Delay(2);
    }

    SDL_FreeSurface(bg);
    SDL_FreeSurface(screen);
    FreeFighter(player);
    SDL_FreeSurface(bgGrass);

    SDL_Quit();

    return 0;
}

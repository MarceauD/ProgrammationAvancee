#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "defines.h"
#include "gamestate.h"

#include "SDL/SDL.h"



bool contact(SDL_Rect * a, SDL_Rect* b){
  bool found;
  if(a->x == b->x - SPRITE_WIDTH || b->x + SPRITE_WIDTH == a->x){
    found = true;
  }
  return found;   
}

int main(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        printf("Unable to init SDL :%s",SDL_GetError());
        return 1;
    }

    
    SDL_WM_SetCaption(GAME_TITLE,GAME_TITLE);

    SDL_Surface* screen, *bg, *sprite, *enemy, *temp;
    SDL_Rect rcSprite, rcEnemy;
    GameState gameState;
    Uint8 *keystate;
  
    SDL_Event event;
    
    gameState = DefaultGameState();

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    if (!screen){
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    sprite = SDL_CreateRGBSurface(0,SPRITE_WIDTH,SPRITE_HEIGHT,32,0,0,0,0);

    if(!sprite){
      printf("Unable to load the sprite player %s\n",SDL_GetError());
      return 1;
    }

    enemy = SDL_CreateRGBSurface(0,SPRITE_WIDTH,SPRITE_HEIGHT,32,0,0,0,0);
    
    if(!enemy){
      printf("Unable to load the sprite enemy %s\n",SDL_GetError());
      return 1;
    }

    temp = SDL_LoadBMP("background.bmp");
    bg = SDL_DisplayFormat(temp);

    rcSprite.x = DEFAULT_SPRITE_POSITION_X;
    rcSprite.y = DEFAULT_SPRITE_POSITION_Y;

    rcEnemy.x = DEFAULT_ENEMY_POSITION_X;
    rcEnemy.y = DEFAULT_ENEMY_POSITION_Y;

    

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
      if(rcSprite.y != DEFAULT_SPRITE_POSITION_Y){
	while(rcSprite.y != DEFAULT_SPRITE_POSITION_Y){
	  rcSprite.y = rcSprite.y + 1;
	}
      }
      if(!contact(&rcEnemy,&rcSprite)){
       if (keystate[SDLK_LEFT]){
	rcSprite.x = rcSprite.x - 1;
      }
      }
      if (keystate[SDLK_RIGHT]){
	rcSprite.x = rcSprite.x + 1;
      }
      if (rcSprite.x < 0 ){
	rcSprite.x = 0;
      }
      else if(rcSprite.x > SCREEN_WIDTH - SPRITE_WIDTH ){
	rcSprite.x = SCREEN_WIDTH - SPRITE_WIDTH;
	}
 
      SDL_FillRect(sprite,NULL,SDL_MapRGB(sprite->format, 255,0,0));

      SDL_BlitSurface(bg,NULL,screen,NULL);
      SDL_BlitSurface(sprite,NULL,screen,&rcSprite);
      SDL_BlitSurface(enemy,NULL,screen,&rcEnemy);
      
      SDL_UpdateRect(screen, 0, 0, 0, 0);

      if(!contact(&rcEnemy,&rcSprite)){
	rcEnemy.x = rcEnemy.x + 1;
      }
    }

    SDL_FreeSurface(bg);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(sprite);
    SDL_FreeSurface(enemy);
    SDL_FreeSurface(temp);

    SDL_Quit();

    return 0;
}

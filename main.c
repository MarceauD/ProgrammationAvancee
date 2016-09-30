#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "defines.h"

#include "SDL/SDL.h"

int main(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        printf("Unable to init SDL :%s",SDL_GetError());
        return 1;
    }

    

    SDL_WM_SetCaption(GAME_TITLE,GAME_TITLE);

    SDL_Surface* screen, *bg, *sprite, *enemy;
    SDL_Rect rcSprite, rcEnemy;
    Uint8 *keystate;
    bool done;
    done = false;

    SDL_Event event;
    
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    if (!screen){
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    bg = SDL_CreateRGBSurface(0,SCREEN_WIDTH,SCREEN_HEIGHT,32,0,0,0,0);


    if(!bg){
        printf("Unable to load the background %s\n", SDL_GetError());
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

    rcSprite.x = DEFAULT_SPRITE_POSITION_X;
    rcSprite.y = DEFAULT_SPRITE_POSITION_Y;

    rcEnemy.x = DEFAULT_ENEMY_POSITION_X;
    rcEnemy.y = DEFAULT_ENEMY_POSITION_Y;

    while(!done){
      if (SDL_PollEvent(&event)){
	switch (event.type){
	case SDL_QUIT:
	  done = true;
	  break;
	case SDL_KEYDOWN:
	  switch(event.key.keysym.sym){
	  case SDLK_ESCAPE:
	  case SDLK_q:
	    done = true;
	    break;
	  }
	  break;
      }
     }
      
      keystate = SDL_GetKeyState(NULL);

      if (keystate[SDLK_LEFT]){
	rcSprite.x = rcSprite.x - 1;
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
      
	       

      SDL_FillRect(bg,NULL, SDL_MapRGB(bg->format, 0,255,0));
      SDL_FillRect(sprite,NULL,SDL_MapRGB(sprite->format, 255,0,0));

      SDL_BlitSurface(bg,NULL,screen,NULL);
      SDL_BlitSurface(sprite,NULL,screen,&rcSprite);
      SDL_BlitSurface(enemy,NULL,screen,&rcEnemy);
      
      SDL_UpdateRect(screen, 0, 0, 0, 0);

      if(rcEnemy.x != rcSprite.x - SPRITE_WIDTH){
	rcEnemy.x = rcEnemy.x + 1;
      }
    }

    SDL_FreeSurface(bg);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(sprite);
    SDL_FreeSurface(enemy);

    SDL_Quit();

    return 0;
}

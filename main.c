#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "defines.h"
#include "gamestate.h"
#include "graphics.h"

#include "SDL/SDL.h"

//handle the event generates by the keyboard
void KeyboardManager(SDL_Event event, GameState *gameState, fighter *player,background* bg, Time *T){
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
        bg->source.x = bg->source.x - 1;
        if(player->rotation == 1){
        player->source.x = 3 * SPRITE_WIDTH + 5;
        player->source.y = SPRITE_HEIGHT;
        player->rotation = 0;
        }

        update_currentTime(T);
        if(time_gap(*T) > 250){
            player->source.x = player->source.x - SPRITE_WIDTH;
            update_previousTime(T);
        }
        if(player->source.x < 5){
            player->source.x = 3 * SPRITE_WIDTH + 5;
        }
        if (bg->source.x <= 0){
            bg->source.x = 0;
            player->rcSprite.x = player->rcSprite.x - 1;
            if(player->rcSprite.x <= 0){
                player->rcSprite.x = 0;
            }
        }
      }
      if (keystate[SDLK_RIGHT]){
        bg->source.x = bg->source.x + 1;
        if(player->rotation == 0){
            player->source.x = 5;
            player->source.y = 0;
            player->rotation = 1;
        }
        update_currentTime(T);
        if(time_gap(*T) > 250){
            player->source.x = player->source.x + SPRITE_WIDTH;
            update_previousTime(T);
        }
        if(player->source.x > SPRITE_WIDTH * 3){
            player->source.x = 5;
        }


        if (bg->source.x > BACKGROUND_WIDTH - SCREEN_WIDTH){
            bg->source.x = BACKGROUND_WIDTH - SCREEN_WIDTH;
            player->rcSprite.x = player->rcSprite.x + 1;
            if(player->rcSprite.x > SCREEN_WIDTH - SPRITE_WIDTH){
                player->rcSprite.x = SCREEN_WIDTH - SPRITE_WIDTH;
            }
        }
      }

}

int main(int argc, char *argv[]){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        printf("Unable to init SDL :%s\n",SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption(GAME_TITLE,GAME_TITLE);

    SDL_Surface* screen;
    fighter player;
    GameState gameState;
    background bg;
    Time T;
    SDL_Event event;

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    if (!screen){
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_EnableKeyRepeat(10, 10);


    gameState = init_GameState();
    player = init_fighter();
    bg = init_background();
    T = init_Time();

    while(!isOver(gameState)){

        KeyboardManager(event,&gameState,&player,&bg,&T);

        SDL_BlitSurface(bg.surface,&bg.source,screen,&bg.rcBG);
        SDL_BlitSurface(player.sprite,&player.source,screen,&player.rcSprite);

        SDL_UpdateRect(screen, 0, 0, 0, 0);
        SDL_Delay(5);
    }

    SDL_FreeSurface(screen);
    FreeFighter(player);
    FreeBackground(bg);
    SDL_Quit();

    return 0;
}


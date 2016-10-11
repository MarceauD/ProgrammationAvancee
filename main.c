#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "defines.h"
#include "gamestate.h"
#include "graphics.h"
#include "event_manager.h"

#include "SDL/SDL.h"

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
        if(player.p == JUMP){
            AnimateGameUp(&player, &T);
        }
        if(player.p == KICK){
            AnimateGameKick(&player,&T);
        }
        SDL_BlitSurface(bg.surface,&bg.source,screen,&bg.rcBG);
        SDL_BlitSurface(player.sprite,&player.source,screen,&player.rcSprite);

        SDL_UpdateRect(screen, 0, 0, 0, 0);
        SDL_Delay(10);
    }

    SDL_FreeSurface(screen);
    FreeFighter(player);
    FreeBackground(bg);
    SDL_Quit();

    return 0;
}


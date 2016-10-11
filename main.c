#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "defines.h"
#include "gamestate.h"
#include "graphics.h"
#include "event_manager.h"

int main (int argc, char *argv[]) {

        /* explication : ?*/
        if (SDL_Init(SDL_INIT_VIDEO) < 0){
                printf("Unable to init SDL :%s\n",SDL_GetError());
                return 1;
        }
        
	/* set the title bar */
        SDL_WM_SetCaption(GAME_TITLE,GAME_TITLE);
    
        /*definition des variables*/
        SDL_Surface* screen;
        fighter player;
        GameState gameState;
        background bg;
        Time T;
        SDL_Event event;
        
	/* create window */
        screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

        /* explications ? */
        if (!screen){
                printf("Unable to set 640x480 video: %s\n", SDL_GetError());
                return 1;
        }

	/* set keyboard repeat */
        SDL_EnableKeyRepeat(10, 10);

        /*initialisation des variables */
        gameState = init_GameState();
        player = init_fighter();
        bg = init_background();
        T = init_Time();

	/* message pump */
        while(!isOver(gameState)){

                /*Handle the keyboard events*/
                KeyboardManager(event,&gameState,&player,&bg,&T);
                
                //animate the player jumping
                if(player.p == JUMP){
                        AnimateGameUp(&player, &T);
                }
                
                //animate the player kicking
                if(player.p == KICK){
                        AnimateGameKick(&player,&T);
                }
            
		/* draw the surface */
                SDL_BlitSurface(bg.surface,&bg.source,screen,&bg.rcBG);
                
		/* draw the player */
                SDL_BlitSurface(player.sprite,&player.source,screen,&player.rcSprite);

		/* update the screen */
                SDL_UpdateRect(screen, 0, 0, 0, 0);
                
                /*ca attends 10 millisecondes avant de passer à la suite*/
                SDL_Delay(10);
        }
        
	/* clean up */
        //SDL_FreeSurface(background); Ce qu'il y avait avant, pk t'as mis un FreeBackground au lieu d'un SDL_FreeSurface explique :)
        //SDL_FreeSurface(theme);
        SDL_FreeSurface(screen);
        FreeFighter(player);
        FreeBackground(bg);
        SDL_Quit();

        return 0;
}


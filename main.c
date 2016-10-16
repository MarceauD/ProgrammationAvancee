#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "h/defines.h"
#include "h/gamestate.h"
#include "h/graphics.h"
#include "h/event_manager.h"

int main () {

    /* explication : ?*/
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
            printf("Unable to init SDL :%s\n",SDL_GetError());
            return 1;
    }

/* set the title bar */
    SDL_WM_SetCaption(GAME_TITLE,GAME_TITLE);

    /*definition des variables*/
    SDL_Surface* screen;
    fighter player, enemy;
    GameState gameState;
    background bg;
    Time T;
    SDL_Event event;

/* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    if (!screen){
            printf("Unable to set 640x480 video: %s\n", SDL_GetError());
            return 1;
    }

/* set keyboard repeat */
    SDL_EnableKeyRepeat(10, 10);

    /*initialisation des variables */
    gameState = init_GameState();
    player = init_fighter(0);
    enemy = init_fighter(1);
    bg = init_background();
    T = init_Time();

/* message pump */
    while(!isOver(gameState)){

       	/*Handle the keyboard events*/
        KeyboardManager(event,&gameState,&player,&enemy,&bg,&T);
        MoveEnemyRight(&enemy,&player,&T);
            //animate the player jumping
        if(player.p == JUMP){
            AnimatePlayerUp(&player,&T);
        }
            //animate the player kicking
        if(player.p == KICK){
            AnimatePlayerKick(&player,&enemy,&T);
        }
	

        /* draw the surface */
        SDL_BlitSurface(bg.surface,&bg.source,screen,&bg.rcBG);

    /* draw the player if he is alive */
    if(isAlive(player)){
            SDL_BlitSurface(player.sprite,&player.source,screen,&player.rcSprite);
	}
    /*same for ennemis*/
	if(isAlive(enemy)){
        	SDL_BlitSurface(enemy.sprite,&enemy.source,screen,&enemy.rcSprite);
	}

    /* update the screen */
        SDL_UpdateRect(screen, 0, 0, 0, 0);

//         SDL_Delay(10);
    }

/* clean up */
    SDL_FreeSurface(screen);
    FreeFighter(player);
    FreeBackground(bg);
    SDL_Quit();

    return 0;
}


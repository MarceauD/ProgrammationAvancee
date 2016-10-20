#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "SDL.h"
#include "headers/defines.h"
#include "headers/gamestate.h"
#include "headers/graphics.h"
#include "headers/event_manager.h"
#include "headers/queue.h"
#include "headers/interface.h"
#include "headers/level.h"

int main (int argc, char *argv[]) {

    /*freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);*/

/* set the title bar */
    SDL_WM_SetCaption(GAME_TITLE,GAME_TITLE);

    /*definition des variables*/
    SDL_Surface* screen;
	SDL_Event event;
	int n, i, j, k, alea_enemy, relaunch;
    fighter player, enemy, enemysLeft[100];
    GameState gameState;
    background bg;
	LPV LPView;
	Time T;

/* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

/* set keyboard repeat */
    SDL_EnableKeyRepeat(10, 10);

    /*initialisation des variables */
    gameState = init_GameState();
    player = init_fighter(PLAYER);
    enemy = init_fighter(GRABBING_ENEMY);
    bg = init_background();
    T = init_Time();
    LPView = init_LPV(player);
	Level(1);
	relaunch = 1;
	n = 0;
	
	for (i=0; i<Left; i++)
	{	
		enemysLeft[i] = init_fighter(1);//on charge 10 ennemis (de type 1 pr l'instant)
		if (i>0)
			enemysLeft[i].rcSprite.x = enemysLeft[i-1].rcSprite.x + 100;
	}

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
	if(!isAlive(player)){
        	AnimatePlayerDeath(&player,&T);
		if(player.p == DYING){
			SDL_BlitSurface(player.sprite,&player.source,screen,&player.rcSprite);
		}
	}
	else{
		SDL_BlitSurface(player.sprite,&player.source,screen,&player.rcSprite);
	}
	
	/*n = 0*/
	while (n+1 < Left)	//tant qu'on a notre file d'ennemis, ici 500
	{
		k = n;
		alea_enemy = rand()%3;
		printf("\nenemy position per default = %d \n", DEFAULT_ENEMY_POSITION_X - (DEFAULT_SPRITE_POSITION_X - 200));
		printf("\nalea_enemy = %d \n", alea_enemy);
		
		/*for (j=n; j<= n+alea_enemy; j++)
		{
			if(isAlive(enemysLeft[j]))
			{
				printf("\n	enemysLeft[%d].rcSprite.x = %d\n",j-1, enemysLeft[j-1].rcSprite.x);
						enemysLeft[j].rcSprite.x = enemysLeft[j-1].rcSprite.x - 10;
						printf("\n	enemysLeft[%d].rcSprite.x = %d\n",j, enemysLeft[j].rcSprite.x);
					} 
		        MoveEnemyRight(&enemysLeft[j],&player,&T);
				/printf("\n	enemysLeft[%d].rcSprite.x = %d\n",0, enemysLeft[0].rcSprite.x);
				
			}
			printf("\n	Dessine enemy[%d]\n",j);
		}
		*/
		n += alea_enemy+1;
		printf("\n	n = %d + %d = %d \n", k,alea_enemy+1,n);
	}
	for (j=0; j<10; j++)
	{
		SDL_BlitSurface(enemysLeft[j].sprite,&enemysLeft[j].source,screen,&enemysLeft[j].rcSprite);
    	MoveEnemyRight(&enemysLeft[j],&player,&T);
	}
		
	
	ViewLifepoints(&LPView,player,screen);
	
    /* update the screen */
        SDL_UpdateRect(screen, 0, 0, 0, 0);
	
        SDL_Delay(10);
    }

/* clean up */
    SDL_FreeSurface(screen);
    FreeFighter(player);
    FreeFighter(enemy);
    FreeBackground(bg);
    FreeLPV(LPView);
    SDL_Quit();

    return 0;
}


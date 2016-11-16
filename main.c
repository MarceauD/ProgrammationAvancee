#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "SDL.h"
#include "headers/defines.h"
#include "headers/gamestate.h"
#include "headers/event_manager.h"
#include "headers/graphics.h"
#include "headers/animations.h"
#include "headers/moving.h"
#include "headers/queue.h"
#include "headers/interface.h"
#include "headers/level.h"



void CleanVariables(SDL_Surface *screen, fighter player, background bg, Time T, LPV LPView, Pause P);
void CleanVariables(SDL_Surface *screen, fighter player, background bg, Time T, LPV LPView, Pause P){
    SDL_FreeSurface(screen);
    FreeFighter(player);
    FreeBackground(bg);
    FreeLPV(LPView);
    FreePause(P);
}

int main (int argc, char *argv[]) {

    /*freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);*/

/* set the title bar */
    SDL_WM_SetCaption(GAME_TITLE,GAME_TITLE);

    /*definition des variables*/
    SDL_Surface* screen,*menu,*Rect;
    SDL_Rect rcRect, source;
	SDL_Event event;
	//int n, i, j, k, alea_enemy, relaunch;
    fighter player, demo, enemy /*enemysLeft[100]*/;
    GameState gameState;
    background bg;
	LPV LPView;
	Time T;
	Pause P;

    //bool launch_enemy2 = false;
    fighter enemyLeft[10];
    bool launchEnemy[10];
    //fighter enemy2;
    fighter* temp_enemy;

/* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

/* set keyboard repeat */
    SDL_EnableKeyRepeat(10, 10);

    /*initialisation des variables */
    gameState = init_GameState();
    player = init_fighter(PLAYER);
    demo = init_fighter(PLAYER);
    enemy = init_fighter(GRABBING_ENEMY);
    bg = init_background();
    T = init_Time();
    LPView = init_LPV(player);
    P = init_Pause();

    int k = 0;
    //enemy2 = init_fighter(GRABBING_ENEMY);


    for (int i=0; i<10; i++){
	enemyLeft[i] = init_fighter(GRABBING_ENEMY);
    }

    for(int i=0; i<10;i++){
	launchEnemy[i] = false;
    }

/* message pump */

    /*TODO : RANGER TOUT CE MERDIER DANS DES FONCTIONS*/


    menu = loadImage(NULL,"sprites/menu.bmp");
    Rect = loadImage(NULL,"sprites/entertocontinue.bmp");
    rcRect.x = 0;
    rcRect.y = 280;
    source.x = 0;
    source.y = 0;
    source.w = 800;
    source.h = 50;
    demo.rcSprite.x = SCREEN_WIDTH / 2 - SPRITE_WIDTH;
    demo.rcSprite.y = SCREEN_HEIGHT / 2 - SPRITE_HEIGHT / 2 ;
    while(gameState.inMenu){
        KeyboardManagerMenu(event,&gameState);
        SDL_BlitSurface(menu,NULL,screen,NULL);
        SDL_BlitSurface(demo.sprite,&demo.source,screen,&demo.rcSprite);
        update_currentTime(&T);
        if(time_gap(T) > 350){
            if(source.y == 0){
                source.y = 50;
            }
            else{
                source.y = 0;
            }
            update_previousTime(&T);
        }
        SDL_BlitSurface(Rect,&source,screen,&rcRect);
        AnimatePlayerKick(&demo,&enemy,&T,250);
        SDL_UpdateRect(screen,0,0,0,0);
    }
    SDL_FreeSurface(menu);
    SDL_FreeSurface(Rect);
    FreeFighter(demo);


    while(!isOver(gameState)){
    if(!gameState.inPause){
        int i = 0;
	while(!isAlive(enemyLeft[i])){
		i = i + 1;
	}
	printf("%u\n",i);
	if(i >= 10){
		temp_enemy = &enemyLeft[i-2];
	} else {
		temp_enemy = &enemyLeft[i];
	}

       	/*Handle the keyboard events*/
        KeyboardManagerGame(event,&gameState,&player,temp_enemy,&bg,&T);
        MoveEnemyRight(&enemyLeft[0],&player,&T);
        update_currentTime(&T);
        if(T.currentTime > (k + 1) * 2000){
            launchEnemy[k] = true;
	    k = k + 1;
        }
	for(int j=1; j < 10 ; j ++){
		if(launchEnemy[j]){
		    if(isAlive(enemyLeft[j-1])){
		        MoveEnemyRight(&enemyLeft[j],&enemyLeft[j-1],&T);
		    }
		    else{
		        MoveEnemyRight(&enemyLeft[j],&player,&T);
		    }
		}
	}


            //animate the player jumping
        CheckAnimations(&player,temp_enemy,&T);

        /* draw the surface */

        BlitImages(&bg, &player, screen, &T);
	for(int i = 0; i < 10; i ++ ){
		if(launchEnemy[i]){
		    BlitImagesConditions(&enemyLeft[i],screen,&T);
		}
	}
		

	ViewLifepoints(&LPView,player,screen);
    }
    else{
        PauseGame(P,&gameState,screen);
    }
        /* update the screen */
        SDL_UpdateRect(screen, 0, 0, 0, 0);

        SDL_Delay(10);
    }

/* clean up */
    CleanVariables(screen, player, bg, T, LPView, P);
    for(int i = 0; i < 10; i ++){
	FreeFighter(enemyLeft[i]);
    }
    SDL_Quit();
    return 0;
}


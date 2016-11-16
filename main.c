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



void CleanVariables(SDL_Surface *screen, fighter player, fighter enemy, background bg, Time T, LPV LPView, Pause P);
void CleanVariables(SDL_Surface *screen, fighter player, fighter enemy, background bg, Time T, LPV LPView, Pause P){
    SDL_FreeSurface(screen);
    FreeFighter(player);
    FreeFighter(enemy);
    FreeBackground(bg);
    FreeLPV(LPView);
    FreePause(P);
}

int main (int argc, char *argv[]) {

    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

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

    bool launch_enemy2 = false;
	fighter enemy2;
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

    enemy2 = init_fighter(GRABBING_ENEMY);

    /*Level(1);
	relaunch = 1;
	n = 0;

	for (i=0; i<Left; i++)
	{
		enemysLeft[i] = init_fighter(GRABBING_ENEMY);//on charge 10 ennemis (de type 1 pr l'instant)
	}*/

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
        if(isAlive(enemy)){
            temp_enemy = &enemy;
        }
        else{
            temp_enemy = &enemy2;
        }

        if(temp_enemy == &enemy){
            printf("TAPE LE PREMIER\n");
        }
        else{
            if(temp_enemy == &enemy2){
                printf("TAPE LE DEUXIEME\n");
            }
        }
       	/*Handle the keyboard events*/
        KeyboardManagerGame(event,&gameState,&player,temp_enemy,&bg,&T);
        MoveEnemyRight(&enemy,&player,&T);
        update_currentTime(&T);
        if(T.currentTime > 1000){
            launch_enemy2 = true;
        }
        if(launch_enemy2){
            if(isAlive(enemy)){
                MoveEnemyRight(&enemy2,&enemy,&T);
            }
            else{
                MoveEnemyRight(&enemy2,&player,&T);
            }
        }


            //animate the player jumping
        CheckAnimations(&player,temp_enemy,&T);

        /* draw the surface */

        BlitImages(&bg, &player, &enemy, screen, &T);
        if(launch_enemy2){
            BlitImagesConditions(&enemy2,screen,&T);
        }
		//tant qu'on a notre file d'ennemis Left
		/*for (j=0; j<1; j++)
		{
			SDL_BlitSurface(enemysLeft[j].sprite,&enemysLeft[j].source,screen,&enemysLeft[j].rcSprite);
			MoveEnemyRight(&enemysLeft[j],&player,&T);
		}*/

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
    CleanVariables(screen, player, enemy, bg, T, LPView, P);
    FreeFighter(enemy2);
    free(temp_enemy);
    SDL_Quit();
    return 0;
}


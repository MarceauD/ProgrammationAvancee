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

    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    /* set the title bar */
    SDL_WM_SetCaption(GAME_TITLE,GAME_TITLE);

    /*DEFINE VARIABLES*/
    SDL_Surface* screen,*menu,*Rect;
    SDL_Rect rcRect, source;
	SDL_Event event;
    fighter player, demo, enemy;
    GameState gameState;
    background bg;
	LPV LPView;
	Time T,T1;
	Pause P;

    fighter enemyLeft[10];
    bool launchEnemy[10];
    bool allDead = false;

    fighter* temp_enemy;

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    SDL_EnableKeyRepeat(10, 10);

    /*INIT ALL VARIABLES*/
    gameState = init_GameState();
    player = init_fighter(PLAYER);
    demo = init_fighter(PLAYER);
    enemy = init_fighter(GRABBING_ENEMY);
    bg = init_background();
    T = T1 = init_Time();
    LPView = init_LPV(player);
    P = init_Pause();

    int k = 0;

    int i;
    for (i=0; i<ENEMYS_LVL1; i++){
        enemyLeft[i] = init_fighter(GRABBING_ENEMY);
    }

    for(i=0; i<ENEMYS_LVL1;i++){
        launchEnemy[i] = false;
    }

    /*MENU*/
    menu = loadImage(NULL,"sprites/menu.bmp");
    Rect = loadImage(NULL,"sprites/entertocontinue.bmp");
    init_Menu(&rcRect,&source,&demo);
    while(gameState.inMenu){
        Menu(menu,Rect,rcRect,&source,&T,event,&gameState,screen,&demo);
    }
    SDL_FreeSurface(menu);
    SDL_FreeSurface(Rect);
    FreeFighter(demo);

    /*GAME*/
    while(!isOver(gameState)){
        if(!gameState.inPause){
            if(!allDead){
                temp_enemy = whichFighter(enemyLeft);
            }

       	/*Handle the keyboard events*/
        KeyboardManagerGame(event,&gameState,&player,temp_enemy,&bg,&T);
        if(!allDead){
            MoveEnemys(enemyLeft,&player,&T,&T1,launchEnemy,&k);
        }
        CheckAnimations(&player,temp_enemy,&T);
        if(player.p == ANIMATED){
            AnimatePlayer(&player,&T);
        }
        BlitImages(&bg, &player, screen, &T);
        if(!allDead){
            BlitEnemys(enemyLeft,screen,launchEnemy,&T);
        }
        if(!isAlive(enemyLeft[ENEMYS_LVL1 - 1])){
            allDead = true;
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

    CleanVariables(screen, player, bg, T, LPView,P);
    SDL_Quit();
    return 0;
}


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



void CleanVariables(SDL_Surface *screen, fighter player, background bg, LPV LPView, Pause P, SDL_Surface * icon);
void CleanVariables(SDL_Surface *screen, fighter player, background bg, LPV LPView, Pause P, SDL_Surface * icon){
    if(screen != NULL){
        SDL_FreeSurface(screen);
    }
    FreeFighter(player);
    FreeBackground(bg);
    FreeLPV(LPView);
    FreePause(P);
    if(icon != NULL){
        SDL_FreeSurface(icon);
    }
}



int main (int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    /* set the title bar */
    SDL_WM_SetCaption(GAME_TITLE,NULL);

    SDL_Surface * icon;
    icon = SDL_LoadBMP("sprites/logo.bmp");
    if(icon){
        SDL_SetColorKey(icon,SDL_SRCCOLORKEY,SDL_MapRGB(icon->format,0,0,0));
    }
    SDL_WM_SetIcon(icon,NULL);

    /*DEFINE VARIABLES*/
    SDL_Surface* screen,*menu,*Rect;
    SDL_Rect rcRect, source;
    SDL_Event event;
    fighter player, demo;
    GameState gameState;
    background bg;
    LPV LPView;
    Time T,T1;
    Pause P;

    fighter enemyLeft[ENEMIES_LVL1];
    bool launchEnemy[ENEMIES_LVL1];
    bool allDead = false;
    int TimeBetweenEnemies[ENEMIES_LVL1];

    fighter enemyRight[ENEMIES_LVL2];
    bool launchEnemyRight[ENEMIES_LVL2];
    int TimeBetweenEnemiesRight[ENEMIES_LVL2];

    fighter* temp_enemy_left;
    fighter* temp_enemy_right;


    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    SDL_EnableKeyRepeat(10, 10);

    /*INIT ALL VARIABLES*/
    gameState = init_GameState();
    player = init_fighter(PLAYER);
    demo = init_fighter(PLAYER);
    bg = init_background();
    T = T1 = init_Time();
    LPView = init_LPV(player);
    P = init_Pause();



    int k = 0;
    int cpt = 0;

    int i;
    for (i=0; i<ENEMIES_LVL1; i++){
        enemyLeft[i] = init_fighter(GRABBING_ENEMY);
    }

    for(i = 0; i<ENEMIES_LVL2; i ++){
        enemyRight[i] = init_fighter(GRABBING_ENEMY);
        enemyRight[i].rcSprite.x = DEFAULT_SPRITE_POSITION_X + 500;
    }

    launchEnemy[0] = true;
    for(i=1; i<ENEMIES_LVL1;i++){
        launchEnemy[i] = false;
    }

    launchEnemyRight[0] =  true;
    for(i = 1; i<ENEMIES_LVL2;i++){
        launchEnemyRight[i] =  false;
    }

   for(i=0;i<ENEMIES_LVL1;i++){
	if(i == 3 || i == 5 || i == 8){
	TimeBetweenEnemies[i] = 2500;
	} else {
   	TimeBetweenEnemies[i] = 250;
   	}
    }

    for(i = 0; i < ENEMIES_LVL2; i ++){
        TimeBetweenEnemiesRight[i] = 500;
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
                temp_enemy_left = whichFighter(enemyLeft);
            }
       	/*Handle the keyboard events*/
            temp_enemy_right = whichFighter(enemyRight);

        KeyboardManagerGame(event,&gameState,&player,temp_enemy_left,temp_enemy_right,&bg,&T);
        if(!allDead){
                MoveEnemies(enemyLeft,&player,&T,&T1,launchEnemy,&k,TimeBetweenEnemies);
        }
        if(gameState.lvl == Level2){
            MoveEnemiesLeft(enemyRight,&player,&T,&T1,launchEnemyRight,&cpt,TimeBetweenEnemies);
        }

        CheckAnimations(&player,temp_enemy_left,temp_enemy_right,&T);
        if(player.p == ANIMATED){
            AnimatePlayer(&player,&T,&bg,&gameState);
        }

        BlitImages(&bg, &player, screen, &T);
        if(gameState.lvl == Level2){
            BlitEnemies(enemyRight,screen,launchEnemyRight,&T);
        }

        BlitEnemies(enemyLeft,screen,launchEnemy,&T);

        if(!isAlive(enemyLeft[ENEMIES_LVL1 - 1])){
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

    CleanVariables(screen, player, bg, LPView,P,icon);
    for(i=0; i<ENEMIES_LVL1; i ++){
	FreeFighter(enemyLeft[i]);
	}
	for(i = 0; i<ENEMIES_LVL2;i++){
        FreeFighter(enemyRight[i]);
	}
    SDL_Quit();
    return 0;
}


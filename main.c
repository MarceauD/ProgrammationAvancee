#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "SDL.h"
#include "headers/defines.h"
#include "headers/gamestate.h"
#include "headers/event_manager.h"
#include "headers/animations.h"
#include "headers/moving.h"
#include "headers/queue.h"
#include "headers/interface.h"
#include "headers/level.h"
#include "headers/cleaning_functions.h"

/*DEFINE VARIABLES*/
//LEFT
fighter enemyl,enemyLeft[ENEMIES_LVL1], *temp_enemy_left;
bool launchEnemyl[ENEMIES_LVL1], createdl[ENEMIES_LVL1], cleanedl[ENEMIES_LVL1],createdEnemyl,cleanedEnemyl;

//RIGHT
fighter enemyr,enemyRight[ENEMIES_LVL1], *temp_enemy_right;
bool launchEnemyr[ENEMIES_LVL1], createdr[ENEMIES_LVL1], cleanedr[ENEMIES_LVL1],createdEnemyr,cleanedEnemyr;


//NEUTRE
SDL_Surface* screen,*menu,*Rect, *gameoverpage, *icon;
SDL_Rect rcRect, source;
SDL_Event event;
fighter player, demo;
GameState gameState;
background bg;
LPV LPView;
Time T,T1;
Pause P;
bool allDead;
int TimeBetweenEnemies[ENEMIES_LVL1],k,i;

int main (/*int argc, char *argv[]*/)
{
  /*freopen("CON", "w", stdout);
  freopen("CON", "r", stdin);
  freopen("CON", "w", stderr);*/

  /*INIT ALL VARIABLES*/
  InitGame();

  /*MENU*/
  menu = loadImage(NULL,"sprites/menu.bmp");
  Rect = loadImage(NULL,"sprites/entertocontinue.bmp");
  init_Menu(&rcRect,&source,&demo);
  while(gameState.inMenu) Menu(menu,Rect,rcRect,&source,&T,event,&gameState,screen,&demo);
  SDL_FreeSurface(menu);
  SDL_FreeSurface(Rect);
  FreeFighter(demo);

  /*GAME*/
  while(!isOver(gameState) && !gameState.gameover){
    if(!gameState.inPause){
      if(!allDead){
        temp_enemy_right = whichFighter(enemyLeft);
      }
     	/*Handle the keyboard events*/
      KeyboardManagerGame(event,&gameState,&player,temp_enemy_right,temp_enemy_left,&bg,&T);
      if(!allDead){
        MoveEnemies(enemyLeft,&player,&T,&T1,launchEnemyl,&k,TimeBetweenEnemies);
      }
      CheckAnimations(&player,temp_enemy_right,temp_enemy_left,&T);
      if(player.p == ANIMATED){
        AnimatePlayer(&player,&T,&bg,&gameState);
      }

      BlitImages(&bg, &player, screen, &T);
      if(!allDead){
        BlitEnemies(enemyLeft,screen,launchEnemyl,&T);
      }
      if(!isAlive(enemyLeft[ENEMIES_LVL1 - 1])){
        allDead = true;
      }
      if(!isAlive(player)){
        gameState.gameover = true;
      }
      ViewLifepoints(&LPView,player,screen);
    }else{
      PauseGame(P,&gameState,screen);
    }

    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    SDL_Delay(10);
  }
  //GAMEOVER
  while(!isOver(gameState) && gameState.gameover){
    gameoverpage = loadImage(NULL,"sprites/gameover.bmp");
    Rect = loadImage(NULL,"sprites/entertoreplay.bmp");
    init_Menu(&rcRect,&source,&demo);
    while(gameState.gameover){
      Menu(gameoverpage,Rect,rcRect,&source,&T,event,&gameState,screen,&demo);
    }
    SDL_FreeSurface(gameoverpage);
    SDL_FreeSurface(Rect);
  }
  CleanVariables(screen, player,enemyl,enemyLeft,cleanedl,createdl, bg, LPView,P,icon);
  SDL_Quit();
  return 0;
}

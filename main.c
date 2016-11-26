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
SDL_Surface* screen,*menu,*Rect, *gameoverpage;
SDL_Rect rcRect, source;
SDL_Event event;
fighter player, enemy, demo,enemyLeft[ENEMIES_LVL1], *temp_enemy_left, *temp_enemy_right;
GameState gameState;
background bg;
LPV LPView;
Time T,T1;
Pause P;
bool launchEnemy[ENEMIES_LVL1],allDead, created[ENEMIES_LVL1], cleaned[ENEMIES_LVL1],createdEnemy,cleanedEnemy;
int TimeBetweenEnemies[ENEMIES_LVL1],k,i;

int main (/*int argc, char *argv[]*/)
{
  /*freopen("CON", "w", stdout);
  freopen("CON", "r", stdin);
  freopen("CON", "w", stderr);*/

  /* set the title bar, the icon... */
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption(GAME_TITLE,NULL);
  SDL_Surface * icon;
  icon = SDL_LoadBMP("sprites/logo.bmp");
  if(icon) SDL_SetColorKey(icon,SDL_SRCCOLORKEY,SDL_MapRGB(icon->format,0,0,0));
  SDL_WM_SetIcon(icon,NULL);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  SDL_EnableKeyRepeat(10, 10);

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
        temp_enemy_left = whichFighter(enemyLeft);
      }
     	/*Handle the keyboard events*/
      KeyboardManagerGame(event,&gameState,&player,temp_enemy_left,temp_enemy_right,&bg,&T);
      if(!allDead){
        MoveEnemies(enemyLeft,&player,&T,&T1,launchEnemy,&k,TimeBetweenEnemies);
      }
      CheckAnimations(&player,temp_enemy_left,temp_enemy_right,&T);
      if(player.p == ANIMATED){
        AnimatePlayer(&player,&T,&bg,&gameState);
      }

      BlitImages(&bg, &player, screen, &T);
      if(!allDead){
        BlitEnemies(enemyLeft,screen,launchEnemy,&T);
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
  CleanVariables(screen, player,enemy,enemyLeft,cleaned,created, bg, LPView,P,icon);
  SDL_Quit();
  return 0;
}

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

void CleanVariables(SDL_Surface *screen, fighter player,fighter enemy,fighter enemyLeft[ENEMIES_LVL1],bool cleaned[ENEMIES_LVL1], bool created[ENEMIES_LVL1], background bg, LPV LPView, Pause P, SDL_Surface * icon);
void CleanVariables(SDL_Surface *screen, fighter player,fighter enemy,fighter enemyLeft[ENEMIES_LVL1],bool cleaned[ENEMIES_LVL1], bool created[ENEMIES_LVL1], background bg, LPV LPView, Pause P, SDL_Surface * icon){
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
    for(int i=0; i<ENEMIES_LVL1; i ++){
      if (created[i] == true && cleaned[i] == false) {
        cleaned[i] = true;
        FreeFighter(enemyLeft[i]);
      }
    }
    FreeFighter(enemy);
}
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

void InitGame (/*GameState gameState,fighter player,fighter demo,background bg,Time T,LPV LPView,Pause P,bool allDead,int k,SDL_Event event,fighter enemy,bool createdEnemy, bool cleanedEnemy, int i,int TimeBetweenEnemies*/)
{
  gameState = init_GameState();
  player = init_fighter(PLAYER);
  demo = init_fighter(PLAYER);
  bg = init_background();
  T = T1 = init_Time();
  LPView = init_LPV(player);
  P = init_Pause();
  k = 0;
  allDead = false;
  event.type = 0;

  enemy = init_fighter(GRABBING_ENEMY_LEFT);
  createdEnemy = true;
  cleanedEnemy = false;
  //enemy.rcSprite.x = DEFAULT_SPRITE_POSITION_X + 300;
  temp_enemy_right = &enemy;

  for (i=0; i<ENEMIES_LVL1; i++){
      enemyLeft[i] = init_fighter(GRABBING_ENEMY_LEFT);
      created[i] = true;
      cleaned[i] = false;
      if (i>0) launchEnemy[i] = false;
      if (i==0) launchEnemy[i] = true;
      if(i == 3 || i == 5 || i == 8){
        TimeBetweenEnemies[i] = 2500;
    	}else {
       	TimeBetweenEnemies[i] = 250;
      }
  }
}

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

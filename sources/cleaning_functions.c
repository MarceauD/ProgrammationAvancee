#include "../headers/cleaning_functions.h"

void InitGame (/*GameState gameState,fighter player,fighter demo,background bg,Time T,LPV LPView,Pause P,bool allDead,int k,SDL_Event event,fighter enemy,bool createdEnemy, bool cleanedEnemy, int i,int TimeBetweenEnemies*/)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption(GAME_TITLE,NULL);
  icon = SDL_LoadBMP("sprites/logo.bmp");
  if(icon) SDL_SetColorKey(icon,SDL_SRCCOLORKEY,SDL_MapRGB(icon->format,0,0,0));
  SDL_WM_SetIcon(icon,NULL);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  SDL_EnableKeyRepeat(10, 10);

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

  enemyl = init_fighter(GRABBING_ENEMY_LEFT);
  createdEnemyl = true;
  cleanedEnemyl = false;
  //enemy.rcSprite.x = DEFAULT_SPRITE_POSITION_X + 300;
  temp_enemy_left = &enemyl;

  for (i=0; i<ENEMIES_LVL1; i++){
      enemyLeft[i] = init_fighter(GRABBING_ENEMY_LEFT);
      createdl[i] = true;
      cleanedl[i] = false;
      if (i>0) launchEnemyl[i] = false;
      if (i==0) launchEnemyl[i] = true;
      if(i == 3 || i == 5 || i == 8){
        TimeBetweenEnemies[i] = 2500;
    	}else {
       	TimeBetweenEnemies[i] = 250;
      }
  }
}

void CleanVariables(SDL_Surface *screen, fighter player,fighter enemy,fighter enemyLeft[ENEMIES_LVL1],bool cleaned[ENEMIES_LVL1], bool created[ENEMIES_LVL1], background bg, LPV LPView, Pause P, SDL_Surface * icon)
{
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

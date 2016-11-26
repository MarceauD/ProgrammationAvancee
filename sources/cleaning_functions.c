#include "../headers/cleaning_functions.h"

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

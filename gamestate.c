#include "gamestate.h"

/*GAMESTATE OPERATIONS*/
GameState init_GameState(){

  GameState gameState;
  gameState.EndProgram = false;
  gameState.inMenu = false;
  return gameState;
}



bool isinMenu(GameState gameState){
  return gameState.inMenu;
}

bool isOver(GameState gameState){
  return gameState.EndProgram;

}


/*TIME OPERATIONS*/

Time init_Time(){
    Time T;
    T.currentTime = 0;
    T.previousTime = 0;
    return T;
}



int time_gap(Time T){
    return T.currentTime - T.previousTime;
}

Time update_currentTime(Time *T){
    T->currentTime = SDL_GetTicks();
}

Time update_previousTime(Time *T){
    T->previousTime = T->currentTime;
}

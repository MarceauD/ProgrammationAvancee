#include "gamestate.h"


GameState DefaultGameState(){

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

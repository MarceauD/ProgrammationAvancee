#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "defines.h"
#include "stdbool.h"


struct GameState{
  bool EndProgram;
  bool inMenu;
};

typedef struct GameState GameState;

extern GameState DefaultGameState();
extern bool isOver(GameState gameState);
extern bool isinMenu(GameState gameState);

#endif //GAMESTATE_H

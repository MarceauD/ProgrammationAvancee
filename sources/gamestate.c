#include "../headers/gamestate.h"

/*GAMESTATE OPERATIONS*/

GameState init_GameState(){
    GameState gameState;
    gameState.EndProgram = false;
    gameState.inMenu = false;
    gameState.inPause = false;
    return gameState;
}

bool isinMenu(GameState gameState){
    return gameState.inMenu;
}


bool isOver(GameState gameState){
    return gameState.EndProgram;
}


GameState write_EndProgramStatus(bool B, GameState gameState){
    gameState.EndProgram = B;
    return gameState;
}


GameState write_MenuStatus(bool B, GameState gameState){
    gameState.inMenu = B;
    return gameState;
    }


bool read_ProgramStatus(GameState gameState){
    return gameState.EndProgram;
}
bool read_MenuStatus(GameState gameState){
    return gameState.inMenu;
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

void update_currentTime(Time *T){
    T->currentTime = SDL_GetTicks();
}


void update_previousTime(Time *T){
    T->previousTime = T->currentTime;
}



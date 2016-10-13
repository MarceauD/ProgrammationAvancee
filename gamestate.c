#include "gamestate.h"

/*GAMESTATE OPERATIONS*/
/*initialize gamestate*/
GameState init_GameState(){
    GameState gameState;
    gameState.EndProgram = false;
    gameState.inMenu = false;
    return gameState;
}
        /*pas compris*/
bool isinMenu(GameState gameState){
    return gameState.inMenu;
}

        /*gameover*/
bool isOver(GameState gameState){
    return gameState.EndProgram;
}

        /*pas compris*/
GameState write_EndProgramStatus(bool B, GameState gameState){
    gameState.EndProgram = B;
    return gameState;
}

        /*pas compris*/
GameState write_MenuStatus(bool B, GameState gameState){
    gameState.inMenu = B;
    return gameState;
    }

        /*pas compris*/
bool read_ProgramStatus(GameState gameState){
    return gameState.EndProgram;
}

        /*pas compris*/
bool read_MenuStatus(GameState gameState){
    return gameState.inMenu;
}


    /*TIME OPERATIONS*/
/*initialize time*/
Time init_Time(){
        Time T;
        T.currentTime = 0;
        T.previousTime = 0;
        return T;
}

/*pas compris*/
int time_gap(Time T){
    return T.currentTime - T.previousTime;
}

/*update time*/
void update_currentTime(Time *T){
    T->currentTime = SDL_GetTicks();
}

/*pas compris*/
void update_previousTime(Time *T){
    T->previousTime = T->currentTime;
}



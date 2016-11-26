#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "defines.h"
#include "stdbool.h"
#include "SDL.h"

enum Level{
    Level1,
    Level2,
    Level3,
};

struct GameState{
    bool EndProgram;
    bool inMenu;
    bool inPause;
    enum Level lvl;
};

typedef struct GameState GameState;

struct Time{
    int currentTime;
    int previousTime;
};

typedef struct Time Time;

/*GAMESTATE OPERATIONS*/
/*initialise a GameState structure*/
extern GameState init_GameState();

/*returns true if the program should end*/
extern bool isOver(GameState gameState);

/*returns true if the program should quit the menu*/
extern bool isinMenu(GameState gameState);

/*set the EndProgram variable*/
extern GameState write_EndProgramStatus(bool B, GameState gameState);

/*set the inMenu variable*/
extern GameState write_MenuStatus(bool B, GameState gameState);

/*returns the EndProgram status*/
extern bool read_ProgramStatus(GameState gameState);

/*returns the inMenu status*/
extern bool read_MenuStatus(GameState gameState);

/*TIME OPERATIONS*/
/*initialise a time structure*/
extern Time init_Time();

/*returns the gap between the current time and the previous time*/
extern int time_gap(Time T);

/*update the previous time, put the current time to the previous time*/
extern void update_previousTime(Time *T);

/*updates the current time with SDL_GetTicks()*/
extern void update_currentTime(Time *T);


#endif //GAMESTATE_H

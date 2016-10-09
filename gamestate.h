#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "defines.h"
#include "stdbool.h"
#include "SDL/SDL.h"

struct GameState{
  bool EndProgram;
  bool inMenu;
};

typedef struct GameState GameState;


struct Time{
    int currentTime;
    int previousTime;
};

typedef struct Time Time;


/*GAMESTATE OPERATIONS*/
extern GameState init_GameState(); //initialise a GameState structure
extern bool isOver(GameState gameState); //returns true if the program should end
extern bool isinMenu(GameState gameState); //returns true if the program should quit the menu
extern GameState write_EndProgramStatus(bool B, GameState gameState); //set the EndProgram variable
extern GameState write_MenuStatus(bool B, GameState gameState); //set the inMenu variable
extern bool read_ProgramStatus(GameState gameState); //returns the EndProgram status
extern bool read_MenuStatus(GameState gameState); //returns the inMenu status

/*TIME OPERATIONS*/
extern Time init_Time(); //initialise a time structure
extern int time_gap(Time T); //returns the gap between the current time and the previous time
extern void update_previousTime(Time *T); //update the previous time, put the current time to the previous time
extern void update_currentTime(Time *T); //updates the current time with SDL_GetTicks()


#endif //GAMESTATE_H

#include"../headers/event_manager.h"
#include "../headers/graphics.h"
#include "../headers/graphics.h"
/* handle keyboard*/
void KeyboardManager(SDL_Event event, GameState *gameState, fighter *player,fighter * enemy,background* bg, Time *T){
        Uint8 *keystate;
        if (SDL_PollEvent(&event)){
                switch (event.type){
                        case SDL_QUIT:
                                    *gameState = write_EndProgramStatus(true,*gameState);
                        break;
                }
        }
        keystate = SDL_GetKeyState(NULL);
        if(keystate[SDLK_ESCAPE]){
                *gameState = write_EndProgramStatus(true,*gameState);
        }

        if (keystate[SDLK_LEFT]){
            if(player->p == STANDING || player->p == KNELT){
                MovePlayerLeft(player,enemy, bg, T);
            }
        }

        if (keystate[SDLK_RIGHT]){
            if(player->p == STANDING || player->p == KNELT){
                MovePlayerRight(player,enemy, bg, T);
            }
        }

        if(keystate[SDLK_DOWN]){
            if(player->p == STANDING || player->p == KNELT){
                AnimatePlayerDown(player);
            }
        }

        if(keystate[SDLK_UP]){
            if(player->p != KICK){
                AnimatePlayerUp(player, T);
            }
        }

        if(keystate[SDLK_SPACE]){
            if(player->p != JUMP){
                AnimatePlayerKick(player, enemy,T);
            }
        }
	if(keystate[SDLK_o]){
		if(!isAlive(*enemy)){
			*enemy = init_fighter(1);
		}
	}
        if(keystate[SDLK_q]){
                *gameState = write_EndProgramStatus(true,*gameState);
        }

}
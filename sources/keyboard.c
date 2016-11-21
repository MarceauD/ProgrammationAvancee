#include"../headers/event_manager.h"

/* handle keyboard*/
void KeyboardManagerGame(SDL_Event event, GameState *gameState, fighter *player,fighter * enemy,background* bg, Time *T){
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
        if(keystate[SDLK_p]){
                gameState->inPause = true;
        }

        if (keystate[SDLK_LEFT]){
            if((player->p == STANDING) || (player->p == KNELT && player->p != DEAD && player->p != DYING && player->p != ANIMATED)){
                MovePlayerLeft(player,enemy, bg, T);
            }
        }

        if (keystate[SDLK_RIGHT]){
            if((player->p == STANDING) || (player->p == KNELT && player->p != DEAD && player->p != DYING && player->p != ANIMATED)){
                MovePlayerRight(player,enemy, bg, T);
            }
        }

        if(keystate[SDLK_DOWN]){
            if((player->p == STANDING) || (player->p == KNELT && player->p != DEAD && player->p != DYING && player->p != ANIMATED)){
                AnimatePlayerDown(player);
            }
        }

        if(keystate[SDLK_UP]){
            if(player->p != KICK && player->p != DEAD && player->p != DYING && player->p != ANIMATED){
                AnimatePlayerUp(player, T);
            }
        }

        if(keystate[SDLK_SPACE]){
            if(player->p != JUMP && player->p != DEAD && player->p != DYING && player->p != ANIMATED){
                AnimatePlayerKick(player, enemy,T,TIME_BTW_ANIMATIONS);
            }
        }
	if(keystate[SDLK_o]){
		if(!isAlive(*enemy)){
			*enemy = init_fighter(GRABBING_ENEMY);
		}
	}
        if(keystate[SDLK_q]){
                *gameState = write_EndProgramStatus(true,*gameState);
        }

}



void KeyboardManagerPause(SDL_Event Event, GameState *gameState){
        Uint8 *keystate;
        if (SDL_PollEvent(&Event)){
                switch (Event.type){
                        case SDL_QUIT:
                                    *gameState = write_EndProgramStatus(true,*gameState);
                        break;
                }
        }
        keystate = SDL_GetKeyState(NULL);
        if(keystate[SDLK_RETURN]){
            gameState->inPause = false;
        }
        if(keystate[SDLK_ESCAPE]){
            gameState->inPause = false;
            gameState->EndProgram = true;
        }

}

void KeyboardManagerMenu(SDL_Event event, GameState *G){
    Uint8 *keystate;
    if(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                    G->inMenu = false;
                    G->EndProgram = true;
                    break;
            }
    }
    keystate = SDL_GetKeyState(NULL);
    if(keystate[SDLK_RETURN]){
        G->inMenu = false;
    }
    if(keystate[SDLK_q] || keystate[SDLK_ESCAPE]){
        G->inMenu = false;
        G->EndProgram = true;
    }
}

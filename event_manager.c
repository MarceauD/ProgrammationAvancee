#include"event_manager.h"




void KeyboardManager(SDL_Event event, GameState *gameState, fighter *player,background* bg, Time *T){
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
        AnimateGameLeft(player, bg, T);
      }
      if (keystate[SDLK_RIGHT]){
        AnimateGameRight(player, bg, T);
      }
      if(keystate[SDLK_DOWN]){
        AnimateGameDown(player, T);
      }
      if(keystate[SDLK_UP]){
        AnimateGameUp(player, T);
      }
      if(keystate[SDLK_SPACE]){
        AnimateGameKick(player,T);
      }

}


void AnimateGameLeft(fighter *player, background *bg, Time *T){
    if(player->p == STANDING || player->p == KNELT){
        bg->source.x = bg->source.x - 1;
        if(player->source.x != SOURCE_POS_PLAYER_STANDING_LEFT_X && player->source.y != SOURCE_POS_PLAYER_STANDING_LEFT_Y){
        player->source.x = SOURCE_POS_PLAYER_STANDING_LEFT_X;
        player->source.y = SOURCE_POS_PLAYER_STANDING_LEFT_Y;
        player->r = LEFT;
        player->p = STANDING;
        }
        update_currentTime(T);
        if(time_gap(*T) >  TIME_BTW_ANIMATIONS){
            player->source.x = player->source.x + SOURCE_POS_PLAYER_STANDING_LEFT_ACC;
            update_previousTime(T);
        }
        if(player->source.x < SOURCE_POS_PLAYER_STANDING_LEFT_LIMIT_X){
            player->source.x = SOURCE_POS_PLAYER_STANDING_LEFT_X;
        }
        if (bg->source.x < SOURCE_POS_BG_LEFT_LIMIT_X){
            bg->source.x = SOURCE_POS_BG_LEFT_LIMIT_X;
            player->rcSprite.x = player->rcSprite.x - 1;
            if(player->rcSprite.x < RECT_POS_PLAYER_LEFT_LIMIT_X){
                player->rcSprite.x = RECT_POS_PLAYER_LEFT_LIMIT_X;
            }
        }
    }

}


void AnimateGameRight(fighter *player, background *bg, Time *T){
    if(player->p == STANDING || player->p == KNELT){
        bg->source.x = bg->source.x + 1;
        if(player->source.x != SOURCE_POS_PLAYER_STANDING_RIGHT_X && player->source.y != SOURCE_POS_PLAYER_STANDING_RIGHT_Y){
            player->source.x = SOURCE_POS_PLAYER_STANDING_RIGHT_X;
            player->source.y = SOURCE_POS_PLAYER_STANDING_RIGHT_Y;
            player->r = RIGHT;
            player->p = STANDING;
        }
        update_currentTime(T);
        if(time_gap(*T) > TIME_BTW_ANIMATIONS){
            player->source.x = player->source.x + SOURCE_POS_PLAYER_STANDING_RIGHT_ACC;
            update_previousTime(T);
        }
        if(player->source.x > SOURCE_POS_PLAYER_STANDING_RIGHT_LIMIT_X){
            player->source.x = SOURCE_POS_PLAYER_STANDING_RIGHT_X;
        }
        if (bg->source.x > SOURCE_POS_BG_RIGHT_LIMIT_X){
            bg->source.x = SOURCE_POS_BG_RIGHT_LIMIT_X;
            player->rcSprite.x = player->rcSprite.x + 1;
            if(player->rcSprite.x > RECT_POS_PLAYER_RIGHT_LIMIT_X){
                player->rcSprite.x = RECT_POS_PLAYER_RIGHT_LIMIT_X;
            }
        }
    }
}

void AnimateGameDown(fighter *player, Time *T){
    if(player->p != KICK){
        player->p = KNELT;
        if(player->r == RIGHT){
            player->source.x = SOURCE_POS_PLAYER_KNELT_RIGHT_X;
            player->source.y = SOURCE_POS_PLAYER_KNELT_Y;
        }
        if(player->r == LEFT){
            player->source.x = SOURCE_POS_PLAYER_KNELT_LEFT_X;
            player->source.y = SOURCE_POS_PLAYER_KNELT_Y;
        }
    }
}

void AnimateGameUp(fighter *player, Time *T){
    if(player->p == STANDING || player->p == KNELT || player->p == JUMP){
        if(player->p != JUMP){
                if(player->r == RIGHT){
                    player->source.x = SOURCE_POS_PLAYER_JUMP_RIGHT_X;
                    player->source.y = SOURCE_POS_PLAYER_JUMP_RIGHT_Y;
                }
                if(player->r == LEFT){
                    player->source.x = SOURCE_POS_PLAYER_JUMP_LEFT_X;
                    player->source.y = SOURCE_POS_PLAYER_JUMP_LEFT_Y;
                }
                player->p = JUMP;
        }
        if(player->r == RIGHT){
            update_currentTime(T);
            if(time_gap(*T) > TIME_BTW_ANIMATIONS - 50){
                player->source.x = player->source.x + SOURCE_POS_PLAYER_JUMP_RIGHT_X_ACC;
                if(player->source.x < SOURCE_POS_PLAYER_JUMP_RIGHT_X_ACC * 3){
                    player->rcSprite.y = player->rcSprite.y - JUMP_HEIGHT;
                }
                else{
                    player->rcSprite.y = player->rcSprite.y + JUMP_HEIGHT;
                }

                update_previousTime(T);
            }
            if(player->source.x > SOURCE_POS_PLAYER_JUMP_RIGHT_X_LIMIT){
                player->rcSprite.y = DEFAULT_SPRITE_POSITION_Y;
                player->p = STANDING;
            }
        }
        if(player->r == LEFT){
            update_currentTime(T);
            if(time_gap(*T) > TIME_BTW_ANIMATIONS - 50){
                player->source.x = player->source.x + SOURCE_POS_PLAYER_JUMP_LEFT_X_ACC;
                if(player->source.x > SOURCE_POS_PLAYER_JUMP_LEFT_X + 3 * SOURCE_POS_PLAYER_JUMP_LEFT_X_ACC){
                    player->rcSprite.y = player->rcSprite.y - JUMP_HEIGHT;
                }
                else{
                    player->rcSprite.y = player->rcSprite.y + JUMP_HEIGHT;
                }
                update_previousTime(T);
            }
            if(player->source.x < SOURCE_POS_PLAYER_JUMP_LEFT_X_LIMIT){
                player->rcSprite.y = DEFAULT_SPRITE_POSITION_Y;
                player->p = STANDING;
            }
        }
    }
}


void AnimateGameKick(fighter *player, Time *T){

    /* TODO  : RANGER LES VALEURS DANS DES #defines*/
    if(player->p == STANDING || player->p == KNELT || player->p == KICK){
        if(player->p != KICK){
            if(player->r == RIGHT){
                player->source.x = 2;
                player->source.y = 350;
            }
            if(player->r == LEFT)
            {
                player->rcSprite.x  = player->rcSprite.x - 10;
                player->source.x = 200;
                player->source.y = 415;
            }
            player->source.w = 50;
            player->p = KICK;
        }
        if(player->r == RIGHT){
            update_currentTime(T);
            if(time_gap(*T) > 100){
                player->source.x = player->source.x + 50;
                update_previousTime(T);
            }
            if(player->source.x > 4 * 50){
                player->p = STANDING;
                player->source.w = DEFAULT_SPRITE_WIDTH;
            }
        }
        if(player->r == LEFT){

            update_currentTime(T);
            if(time_gap(*T) > 100){
                player->source.x = player->source.x - 50;
                update_previousTime(T);
            }
            if(player->source.x < 50){
                player->p = STANDING;
                player->rcSprite.x = player->rcSprite.x + 10;
                player->source.w = DEFAULT_SPRITE_WIDTH;
            }
        }
    }



}


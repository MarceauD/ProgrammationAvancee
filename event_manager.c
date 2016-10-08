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

}


void AnimateGameLeft(fighter *player, background *bg, Time *T){
        bg->source.x = bg->source.x - 1;
        if(player->r == RIGHT || player->p == KNELT){
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


void AnimateGameRight(fighter *player, background *bg, Time *T){
        bg->source.x = bg->source.x + 1;
        if(player->r == LEFT || player->p == KNELT){
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

void AnimateGameDown(fighter *player, Time *T){
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


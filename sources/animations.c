#include "../headers/animations.h"

/*LEFT*/
void AnimatePlayerLeft(fighter *player){
    /*position the player in the right way to walk left*/
    if((player->source.x != SOURCE_POS_PLAYER_STANDING_LEFT_X && player->source.y != SOURCE_POS_PLAYER_STANDING_LEFT_Y)){
        player->source.x = SOURCE_POS_PLAYER_STANDING_LEFT_X;
        player->source.y = SOURCE_POS_PLAYER_STANDING_LEFT_Y;
        player->r = LEFT;
        player->p = STANDING;
	}
    /*animate left walking*/
	player->source.x = player->source.x + SOURCE_POS_PLAYER_STANDING_LEFT_ACC;
    if(player->source.x < SOURCE_POS_PLAYER_STANDING_LEFT_LIMIT_X){
        player->source.x = SOURCE_POS_PLAYER_STANDING_LEFT_X;
    }
}

/*RIGHT*/
void AnimatePlayerRight(fighter *player){
    if((player->source.x != SOURCE_POS_PLAYER_STANDING_RIGHT_X && player->source.y != SOURCE_POS_PLAYER_STANDING_RIGHT_Y) || player->p == KNELT){
        player->source.x = SOURCE_POS_PLAYER_STANDING_RIGHT_X;
        player->source.y = SOURCE_POS_PLAYER_STANDING_RIGHT_Y;
        player->r = RIGHT;
        player->p = STANDING;
    }
    player->source.x = player->source.x + SOURCE_POS_PLAYER_STANDING_RIGHT_ACC;
    if(player->source.x > SOURCE_POS_PLAYER_STANDING_RIGHT_LIMIT_X){
        player->source.x = SOURCE_POS_PLAYER_STANDING_RIGHT_X;
    }
}

/*DOWN*/
void AnimatePlayerDown(fighter *player){
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

/*UP*/
void AnimatePlayerUp(fighter *player, Time *T){
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
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            player->source.x = player->source.x + SOURCE_POS_PLAYER_JUMP_RIGHT_X_ACC;
            if(player->source.x < SOURCE_POS_PLAYER_JUMP_RIGHT_X_ACC * 3){
                player->rcSprite.y = player->rcSprite.y - JUMP_HEIGHT;
            }
            else{
                player->rcSprite.y = player->rcSprite.y + JUMP_HEIGHT;
            }

            player->previousTime = T->currentTime;
        }
        if(player->source.x > SOURCE_POS_PLAYER_JUMP_RIGHT_X_LIMIT){
            player->rcSprite.y = DEFAULT_SPRITE_POSITION_Y;
            player->p = STANDING;
        }
    }
    if(player->r == LEFT){
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            player->source.x = player->source.x + SOURCE_POS_PLAYER_JUMP_LEFT_X_ACC;

            if(player->source.x > SOURCE_POS_PLAYER_JUMP_LEFT_X + 3 * SOURCE_POS_PLAYER_JUMP_LEFT_X_ACC){
                player->rcSprite.y = player->rcSprite.y - JUMP_HEIGHT;
            }
            else{
                player->rcSprite.y = player->rcSprite.y + JUMP_HEIGHT;
            }

           player->previousTime = T->currentTime;
        }
        if(player->source.x < SOURCE_POS_PLAYER_JUMP_LEFT_LIMIT_X){
            player->rcSprite.y = DEFAULT_SPRITE_POSITION_Y;
            player->p = STANDING;
        }
    }
}

/*handeling kicks*/
void AnimatePlayerKick(fighter *player,fighter *enemy, Time *T){
/* TODO  : RANGER LES VALEURS DANS DES #defines*/

    if(player->p != KICK){
        if(player->r == RIGHT){
            player->source.x = SOURCE_POS_PLAYER_KICK_RIGHT_X;
            player->source.y = SOURCE_POS_PLAYER_KICK_RIGHT_Y;
        }

        if(player->r == LEFT) {
            player->rcSprite.x  = player->rcSprite.x - 25;
            player->source.x = SOURCE_POS_PLAYER_KICK_LEFT_X;
            player->source.y = SOURCE_POS_PLAYER_KICK_LEFT_Y;
        }

        player->source.w = 80;
        player->p = KICK;
    }
    if(player->r == RIGHT){
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            player->source.x = player->source.x + SOURCE_POS_PLAYER_KICK_RIGHT_ACC;
            player->previousTime = T->currentTime;
        }
        if(player->source.x > SOURCE_POS_PLAYER_KICK_RIGHT_LIMIT_X){
            player->p = STANDING;
            player->source.w = DEFAULT_SPRITE_WIDTH;
	    PlayerHitEnemy(player,enemy);
        }
    }
    if(player->r == LEFT){
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            player->source.x = player->source.x + SOURCE_POS_PLAYER_KICK_LEFT_ACC;
            player->previousTime = T->currentTime;
        }
        if(player->source.x < SOURCE_POS_PLAYER_KICK_LEFT_LIMIT_X){
            player->p = STANDING;
            player->rcSprite.x = player->rcSprite.x + 25;
            player->source.x = 1;
            player->source.w = DEFAULT_SPRITE_WIDTH;
	    PlayerHitEnemy(player, enemy);
        }
    }
}

void AnimatePlayerDeath(fighter *player, Time * T){
	if(player->p != DYING && player->p != DEAD){
		if(player->r == RIGHT){
			player->source.x = 205;
			player->source.y = 0;
			player->source.w = 80;
		}
		if(player->r == LEFT){
			player->source.x = 380;
			player->source.y = 106;
			player->source.w = 80;
		}
		player->p = DYING;
	}
	if(player->r == RIGHT){
			update_currentTime(T);
			if(T->currentTime - player->previousTime > 250){
			 player->source.x = player->source.x + 80;
           		 player->previousTime = T->currentTime;
        		}
        		if(player->source.x > 366 ){
			   player->source.x = 366;
			   player->p = DEAD;
			}
	}
	if(player->r == LEFT){
			update_currentTime(T);
			if(T->currentTime - player->previousTime > 250){
			 player->source.x = player->source.x - 80;
           		 player->previousTime = T->currentTime;
        		}
        		if(player->source.x < 220 ){
			   player->source.x = 220;
			   player->p = DEAD;
			}

	}
}

void CheckAnimations(fighter *player, fighter *enemy, Time *T){
    if(player->p == JUMP){
            AnimatePlayerUp(player,T);
    }
    if(player->p == KICK){
            AnimatePlayerKick(player,enemy,T);
    }
}

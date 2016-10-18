#include "../headers/event_manager.h"
#include "../headers/graphics.h"


/*collision detect*/
bool collision(SDL_Rect A, SDL_Rect B){
	return (A.x < B.x - (SPRITE_WIDTH) || B.x + (SPRITE_WIDTH) > A.x);
}



/*animations*/
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
        if(player->source.x < SOURCE_POS_PLAYER_JUMP_LEFT_X_LIMIT){
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
            player->source.x = 2;
            player->source.y = 350;
        }

        if(player->r == LEFT) {
            player->rcSprite.x  = player->rcSprite.x - 10;
            player->source.x = 200;
            player->source.y = 415;
        }

        player->source.w = 50;
        player->p = KICK;
    }
    if(player->r == RIGHT){
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            player->source.x = player->source.x + 50;
            player->previousTime = T->currentTime;
        }
        if(player->source.x > 4 * 50){
            player->p = STANDING;
            player->source.w = DEFAULT_SPRITE_WIDTH;
	    PlayerHitEnemy(player,enemy);
        }
    }
    if(player->r == LEFT){
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            player->source.x = player->source.x - 50;
            player->previousTime = T->currentTime;
        }
        if(player->source.x < 50){
            player->p = STANDING;
            player->rcSprite.x = player->rcSprite.x + 10;
            player->source.x = 1;
            player->source.w = DEFAULT_SPRITE_WIDTH;
	    PlayerHitEnemy(player, enemy);
        }
    }
}


/*hitbox*/
void PlayerHitEnemy(fighter *player, fighter *enemy){
	if(collision(player->rcSprite,enemy->rcSprite) && ((player->r == LEFT && enemy->r == RIGHT) || (player->r == RIGHT && enemy->r == LEFT))){
		*enemy = write_lifepoints(read_lifepoints(*enemy)-read_damage(*player),*enemy);
	}
}

void MovePlayerLeft(fighter *player,fighter *enemy, background *bg, Time *T){
        /*activate animation to move left*/
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            AnimatePlayerLeft(player);
            player->previousTime = T->currentTime;
        }
        if(!collision(player->rcSprite,enemy->rcSprite) || !isAlive(*enemy)){
            if (player->rcSprite.x < SCREEN_WIDTH/2 - SPRITE_WIDTH) {
                bg->source.x = bg->source.x - 1;
                MoveEnemyRight(enemy,player,T);
            }
            else{
            player->rcSprite.x = player->rcSprite.x - 1;
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

void MovePlayerRight(fighter *player, fighter *enemy, background *bg, Time *T){
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            AnimatePlayerRight(player);
            player->previousTime = T->currentTime;
        }
        if(!collision(player->rcSprite, enemy->rcSprite) || !isAlive(*enemy)){
            if (player->rcSprite.x > SCREEN_WIDTH/2 - SPRITE_WIDTH) {
                bg->source.x = bg->source.x + 1;

            }
            else{
                player->rcSprite.x = player->rcSprite.x + 1;
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

void MoveEnemyRight(fighter *enemy, fighter *player, Time *T){
    enemy->r = RIGHT;
    if(enemy->rcSprite.x < player->rcSprite.x - (SPRITE_WIDTH / 2)){
        update_currentTime(T);
        if(T->currentTime - enemy->previousTime > TIME_BTW_ANIMATIONS){
            AnimatePlayerRight(enemy);
            enemy->previousTime = T->currentTime;
        }
        enemy->rcSprite.x = enemy->rcSprite.x + 1;

    }
}



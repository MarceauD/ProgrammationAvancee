#include "../headers/moving.h"
#include "../headers/event_manager.h"
#include "../headers/graphics.h"
#include "../headers/animations.h"
#include "../headers/level.h"

void MovePlayerLeft(fighter *player,fighter *enemy,fighter *enemy_r, background *bg, Time *T, GameState *gs){
        /*activate animation to move left*/
        if(player->rcSprite.x <= 170 && gs->lvl == Level1){
                player->p = ANIMATED;
        }
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            AnimatePlayerLeft(player);
            player->previousTime = T->currentTime;
        }
        if((!collision(player->rcSprite,enemy->rcSprite) || !isAlive(*enemy)) && (!collision(player->rcSprite,enemy_r->rcSprite) || !isAlive(*enemy_r)) ){
            if (player->rcSprite.x < SCREEN_WIDTH/2 - SPRITE_WIDTH) {
                bg->source.x = bg->source.x - PLAYER_SPEED;
                MoveEnemyRight(enemy,player,T);
            }
            else{
            player->rcSprite.x = player->rcSprite.x - PLAYER_SPEED;
            }
            if (bg->source.x < SOURCE_POS_BG_LEFT_LIMIT_X){
                bg->source.x = SOURCE_POS_BG_LEFT_LIMIT_X;
                player->rcSprite.x = player->rcSprite.x - PLAYER_SPEED;
                if(player->rcSprite.x < RECT_POS_PLAYER_LEFT_LIMIT_X){
                    player->rcSprite.x = RECT_POS_PLAYER_LEFT_LIMIT_X;
                }
            }

        }
}

void AnimatePlayer(fighter * player, Time *T,background * bg, GameState *gs){
    if(player->p == ANIMATED){
        player->rcSprite.x -= 1;
        player->rcSprite.y -= 1.10;
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            AnimatePlayerLeft(player);
            player->previousTime = T->currentTime;
        }
    if(player->rcSprite.y <= 45){
        player->p = STANDING;
        ChangeLevel(player,bg,gs);
    }
    }
}

void MovePlayerRight(fighter *player, fighter *enemy,fighter * enemy_r, background *bg, Time *T){
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            AnimatePlayerRight(player);
            player->previousTime = T->currentTime;
        }
        printf("ENEMY LEFT COLLISION : %s\nENEMY RIGHT COLLISION : %s\n",(!collision(player->rcSprite, enemy->rcSprite) || !isAlive(*enemy))?"FALSE":"TRUE",(!collision(player->rcSprite,enemy_r->rcSprite) || !isAlive(*enemy_r))?"FALSE":"TRUE");
        if( (!collision(player->rcSprite, enemy->rcSprite) || !isAlive(*enemy)) && (!collision(player->rcSprite,enemy_r->rcSprite) || !isAlive(*enemy_r))){

            if (player->rcSprite.x > SCREEN_WIDTH/2 - SPRITE_WIDTH) {
                bg->source.x = bg->source.x + PLAYER_SPEED;

            }
            else{
                player->rcSprite.x = player->rcSprite.x + PLAYER_SPEED;
            }
            if (bg->source.x > SOURCE_POS_BG_RIGHT_LIMIT_X){
                bg->source.x = SOURCE_POS_BG_RIGHT_LIMIT_X;
                player->rcSprite.x = player->rcSprite.x + PLAYER_SPEED;
                if(player->rcSprite.x > RECT_POS_PLAYER_RIGHT_LIMIT_X){
                    player->rcSprite.x = RECT_POS_PLAYER_RIGHT_LIMIT_X;
                }
            }
        }

}

void MoveEnemyRight(fighter *enemy, fighter *player, Time *T){
    enemy->r = RIGHT;
    if(enemy->p != DYING && enemy->p != DEAD){
    	if(enemy->rcSprite.x < player->rcSprite.x - (SPRITE_WIDTH / 2)){
		update_currentTime(T);
		if(T->currentTime - enemy->previousTime > TIME_BTW_ANIMATIONS){
		    AnimatePlayerRight(enemy);
		    enemy->previousTime = T->currentTime;
		}
		enemy->rcSprite.x = enemy->rcSprite.x + 1;
		update_previousTime(T);
	    }
	    else{
	       if(player->f == PLAYER){
	       	EnemyAttackRight(enemy,player,T);
		}
	    }
   }
}

void MoveEnemyLeft(fighter *enemy, fighter * player, Time *T){
    enemy->r = LEFT;
    if(enemy->p != DYING && enemy->p != DEAD){
    	if(enemy->rcSprite.x > player->rcSprite.x + (SPRITE_WIDTH / 2) && enemy->p != KICK){
		update_currentTime(T);
		if(T->currentTime - enemy->previousTime > TIME_BTW_ANIMATIONS){
		    AnimatePlayerLeft(enemy);
		    enemy->previousTime = T->currentTime;
		}
		enemy->rcSprite.x = enemy->rcSprite.x - 1;
		update_previousTime(T);
	    }
	    else{
	       if(player->f == PLAYER){
                EnemyAttackLeft(enemy,player,T);
                enemy->p = KICK;
		}
	    }
   }
}

#include "../headers/moving.h"
#include "../headers/event_manager.h"
#include "../headers/graphics.h"
#include "../headers/animations.h"

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
	printf("collision : %s, en vie  : %s\n",collision(player->rcSprite, enemy->rcSprite) ? "TRUE" : "FALSE", isAlive(*enemy) ? "TRUE" : "FALSE");
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

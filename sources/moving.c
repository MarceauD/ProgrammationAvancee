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
                enemy->acc = 2;
                enemy_r->acc = 1;
            }
            else{
                player->rcSprite.x = player->rcSprite.x - PLAYER_SPEED;
                enemy->acc = 0;
                enemy_r->acc = 0;
            }
            if (bg->source.x < SOURCE_POS_BG_LEFT_LIMIT_X){
                bg->source.x = SOURCE_POS_BG_LEFT_LIMIT_X;
                player->rcSprite.x = player->rcSprite.x - PLAYER_SPEED;
                if(player->rcSprite.x < RECT_POS_PLAYER_LEFT_LIMIT_X){
                    player->rcSprite.x = RECT_POS_PLAYER_LEFT_LIMIT_X;
                }
                enemy->acc = 0;
                enemy_r->acc = 0;
            }

        }
}

void AnimatePlayer(fighter * player, Time *T,background * bg, GameState *gs){
    if(gs->lvl == Level1){
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
    }else if(gs->lvl == Level2){
        if(player->p == ANIMATED){
            player->rcSprite.x += 1;
            player->rcSprite.y -= 1.10;
            update_currentTime(T);
            if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
                AnimatePlayerRight(player);
                player->previousTime = T->currentTime;
            }
            if(player->rcSprite.y <= 45){
                player->p = STANDING;
                ChangeLevel(player,bg,gs);
            }
        }
    }
}

void MovePlayerRight(fighter *player, fighter *enemy,fighter * enemy_r, background *bg, Time *T,GameState *gs){
        if(player->rcSprite.x >= 605 && gs->lvl == Level2){
                player->p = ANIMATED;
        }
        update_currentTime(T);
        if(T->currentTime - player->previousTime > TIME_BTW_ANIMATIONS){
            AnimatePlayerRight(player);
            player->previousTime = T->currentTime;
        }

        if( (!collision(player->rcSprite, enemy->rcSprite) || !isAlive(*enemy)) && (!collision(player->rcSprite,enemy_r->rcSprite) || !isAlive(*enemy_r))){
            if (player->rcSprite.x > SCREEN_WIDTH/2 - SPRITE_WIDTH) {
                if(gs->lvl != Level1 || player->rcSprite.x < 725){
                    bg->source.x = bg->source.x + PLAYER_SPEED;
                    enemy->acc = -1;
                    enemy_r->acc = -2;
                }
            }
            else{
                    player->rcSprite.x = player->rcSprite.x + PLAYER_SPEED;
                    enemy->acc = 0;
                    enemy_r->acc = 0;
                }
            }
            if (bg->source.x > SOURCE_POS_BG_RIGHT_LIMIT_X){
                bg->source.x = SOURCE_POS_BG_RIGHT_LIMIT_X;
                player->rcSprite.x = player->rcSprite.x + PLAYER_SPEED;
                if(player->rcSprite.x > RECT_POS_PLAYER_RIGHT_LIMIT_X){
                    player->rcSprite.x = RECT_POS_PLAYER_RIGHT_LIMIT_X;
                }
                enemy->acc = 0;
                enemy_r->acc = 0;
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
		enemy->rcSprite.x = enemy->rcSprite.x + ENEMY_SPEED + enemy->acc;
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
		enemy->rcSprite.x = enemy->rcSprite.x - ENEMY_SPEED + enemy->acc;
		update_previousTime(T);
	    }
	    else{
	       if(player->f == PLAYER){
                EnemyAttackLeft(enemy,player,T);
            }
	    }
   }
}

#include "../headers/event_manager.h"
#include "../headers/graphics.h"



bool collision(SDL_Rect A, SDL_Rect B){
    bool result;
    if(B.x < A.x){
        result = A.x <= B.x + A.w;
    }
    else{
        result = B.x <= A.x + A.w;
    }
    return result;
}

void PlayerHitEnemy(fighter *player, fighter *enemy){
	if(collision(player->rcSprite,enemy->rcSprite) && ((player->r == LEFT && enemy->r == RIGHT) || (player->r == RIGHT && enemy->r == LEFT))){
		*enemy = write_lifepoints(read_lifepoints(*enemy)-read_damage(*player),*enemy);
	}
}

void EnemyAttackRight(fighter *enemy, fighter *player, Time *T){
	if(isAlive(*enemy)){
	    if(enemy->rcSprite.y != DEFAULT_SPRITE_POSITION_Y + 5){
	    	enemy->rcSprite.y = DEFAULT_SPRITE_POSITION_Y + 5;
	    }
	    enemy->source.x = 232;
	    enemy->source.y = 326;
            update_currentTime(T);
            if(T->currentTime - enemy->previousTime > 1000){
                *player = write_lifepoints(read_lifepoints(*player) - read_damage(*enemy), *player);
                enemy->previousTime = T->currentTime;
            }
        }
}

void EnemyAttackLeft(fighter *enemy, fighter *player, Time *T){
    if(isAlive(*enemy)){
	    if(enemy->rcSprite.y != DEFAULT_SPRITE_POSITION_Y + 5){
	    	enemy->rcSprite.y = DEFAULT_SPRITE_POSITION_Y + 5;
	    }
	    /*enemy->source.x = 232;
	    enemy->source.y = 326;*/
            update_currentTime(T);
            if(T->currentTime - enemy->previousTime > 1000){
                *player = write_lifepoints(read_lifepoints(*player) - read_damage(*enemy), *player);
                enemy->previousTime = T->currentTime;
            }
        }
}


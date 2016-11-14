#include "../headers/event_manager.h"
#include "../headers/graphics.h"


/*collision detect*/
bool collision(SDL_Rect A, SDL_Rect B){
	return (A.x < B.x - A.w || B.x + A.w > A.x);
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
            if(time_gap(*T) > 1000){
                *player = write_lifepoints(read_lifepoints(*player) - read_damage(*enemy), *player);
                update_previousTime(T);
            }
        }
}

#include "../headers/event_manager.h"
#include "../headers/graphics.h"


/*collision detect*/
bool collision(SDL_Rect A, SDL_Rect B){
	return (A.x < B.x - (SPRITE_WIDTH) || B.x + (SPRITE_WIDTH) > A.x);
}

void PlayerHitEnemy(fighter *player, fighter *enemy){
	if(collision(player->rcSprite,enemy->rcSprite) && ((player->r == LEFT && enemy->r == RIGHT) || (player->r == RIGHT && enemy->r == LEFT))){
		*enemy = write_lifepoints(read_lifepoints(*enemy)-read_damage(*player),*enemy);
	}
}

void EnemyAttackRight(fighter *enemy, fighter *player, Time *T){
	if(isAlive(*enemy)){
            update_currentTime(T);
            if(time_gap(*T) > 1000){
                *player = write_lifepoints(read_lifepoints(*player) - read_damage(*enemy) * 5, *player);
                update_previousTime(T);
            }
        }
}
#include <stdio.h>
#include <stdlib.h>
#include "../headers/level.h"

/*RETURNS THE FIRST FIGHTER ALIVE*/
fighter * whichFighter(int N,fighter enemyLeft[N]){
    int i = 0;
    while(!isAlive(enemyLeft[i])){
                    i = i + 1;
                }
        if(i >= N){
                return &enemyLeft[i-2];
        } else {
            return &enemyLeft[i];
        }

}

void MoveEnemies(int N,fighter enemyLeft[N],fighter *player, Time *T, Time *T1,bool launchEnemy[N], int *k, int TimeBetweenEnemies[N]){
    //MoveEnemyRight(&enemyLeft[0],player,T);
    update_currentTime(T1);
    if(time_gap(*T1) > TimeBetweenEnemies[*k]){
        launchEnemy[*k] = true;
        update_previousTime(T1);
        *k = *k + 1;
    }
    int j;
    for(j=0; j < N; j ++){
        if(launchEnemy[j]){
            if(j == 0){
                MoveEnemyRight(&enemyLeft[j],player,T);
            }
            else{
                    bool Alive = isAlive(enemyLeft[j-1]);
                    if(Alive){
                        MoveEnemyRight(&enemyLeft[j],&enemyLeft[j-1],T);
                    }
                    else{
                        MoveEnemyRight(&enemyLeft[j],player,T);
                    }
            }
        }
    }
}

void MoveEnemiesLeft(int N,fighter enemyRight[N], fighter *player, Time *T, Time *T1,bool launchEnemyRight[N], int *cpt, int TimeBetweenEnemiesRight[N]){
    //MoveEnemyLeft(&enemyRight[0],player,T);
    update_currentTime(T1);
    if(time_gap(*T1) > TimeBetweenEnemiesRight[*cpt]){
        launchEnemyRight[*cpt] = true;
        update_previousTime(T1);
        *cpt = *cpt + 1;
    }
    int j;
    for(j=0; j < N; j ++){
        if(launchEnemyRight[j]){
	    bool Alive = isAlive(enemyRight[j-1]);
            if(j == 0){
                MoveEnemyLeft(&enemyRight[j],player,T);
            }
            else{
                if(Alive){
                    MoveEnemyLeft(&enemyRight[j],&enemyRight[j-1],T);
                }
                else{
                    MoveEnemyLeft(&enemyRight[j],player,T);
                }
            }
        }
    }


}

void BlitEnemies(int N,fighter enemyLeft[N], SDL_Surface * screen, bool launchEnemy[N],Time *T){
    int i;
    for(i = 0; i < N; i ++ ){
        if(launchEnemy[i]){
            BlitImagesConditions(&enemyLeft[i],screen,T);
        }
    }
}


void ChangeLevel(fighter * player, background * bg, GameState *gs){
    SDL_Surface * temp;
    temp = bg->surface;
    if(gs->lvl == Level1){
        bg->surface = loadImage(bg->surface,"sprites/floors/floor2.bmp");
        SDL_FreeSurface(temp);
        player->r = RIGHT;
        player->rcSprite.y = DEFAULT_SPRITE_POSITION_Y;
        player->source.x = SOURCE_POS_PLAYER_STANDING_RIGHT_X;
        player->source.y = SOURCE_POS_PLAYER_STANDING_RIGHT_Y;
        gs->lvl = Level2;
    }
    else if(gs->lvl == Level2){
        bg->surface = loadImage(bg->surface,"sprites/floors/floor3.bmp");
        SDL_FreeSurface(temp);
        player->r = LEFT;
        player->rcSprite.y = DEFAULT_SPRITE_POSITION_Y;
        player->source.x = SOURCE_POS_PLAYER_STANDING_LEFT_X;
        player->source.y = SOURCE_POS_PLAYER_STANDING_LEFT_Y;
        gs->lvl = Level3;
    }
}



void resetTabEnemies(int N,fighter enemies[N]){
    int i;
    for (i = 0; i < N ; i ++){
        enemies[i].rcSprite.x = DEFAULT_ENEMY_POSITION_X;
        enemies[i].rcSprite.y = DEFAULT_ENEMY_POSITION_Y;
        enemies[i].source.x = SOURCE_POS_PLAYER_STANDING_RIGHT_X;
        enemies[i].source.y = SOURCE_POS_PLAYER_STANDING_RIGHT_Y;
        enemies[i].source.w = SPRITE_WIDTH;
	if(i == 0){
		enemies[i].lifepoints = DEFAULT_PUNCHING_ENEMY_LIFEPOINTS;
	} else {
        	enemies[i].lifepoints = DEFAULT_GRABBING_ENEMY_LIFEPOINTS;
	}
        enemies[i].p = STANDING;
    }
}

void resetTabLaunch(int N,bool launchEnemy[N]){
    int i;
    for(i = 0; i < N; i ++){
        launchEnemy[i] = false;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include "../headers/level.h"

/*RETURNS THE FIRST FIGHTER ALIVE*/
fighter * whichFighter(fighter enemyLeft[ENEMIES_LVL1]){
    int i = 0;
    while(!isAlive(enemyLeft[i])){
                    i = i + 1;
                }
        if(i >= ENEMIES_LVL1){
                return &enemyLeft[i-2];
        } else {
            return &enemyLeft[i];
        }

}

void MoveEnemies(fighter enemyLeft[ENEMIES_LVL1],fighter *player, Time *T, Time *T1,bool launchEnemy[ENEMIES_LVL1], int *k, int TimeBetweenEnemies[ENEMIES_LVL1]){
    //MoveEnemyRight(&enemyLeft[0],player,T);
    update_currentTime(T1);
    if(time_gap(*T1) > TimeBetweenEnemies[*k]){
        launchEnemy[*k] = true;
        update_previousTime(T1);
        *k = *k + 1;
    }
    int j;
    for(j=0; j < ENEMIES_LVL1; j ++){
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

void MoveEnemiesLeft(fighter enemyRight[ENEMIES_LVL2], fighter *player, Time *T, Time *T1,bool launchEnemyRight[ENEMIES_LVL2], int *cpt, int TimeBetweenEnemiesRight[ENEMIES_LVL2]){
    //MoveEnemyLeft(&enemyRight[0],player,T);
    update_currentTime(T1);
    if(time_gap(*T1) > TimeBetweenEnemiesRight[*cpt]){
        launchEnemyRight[*cpt] = true;
        update_previousTime(T1);
        *cpt = *cpt + 1;
    }
    int j;
    for(j=0; j < ENEMIES_LVL2; j ++){
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

void BlitEnemies(fighter enemyLeft[ENEMIES_LVL1], SDL_Surface * screen, bool launchEnemy[ENEMIES_LVL1],Time *T){
    int i;
    for(i = 0; i < ENEMIES_LVL1; i ++ ){
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



void resetTabEnemies(fighter enemies[ENEMIES_LVL1]){
    int i;
    for (i = 0; i < ENEMIES_LVL1 ; i ++){
        enemies[i].rcSprite.x = DEFAULT_ENEMY_POSITION_X;
        enemies[i].rcSprite.y = DEFAULT_ENEMY_POSITION_Y;
        enemies[i].source.x = SOURCE_POS_PLAYER_STANDING_RIGHT_X;
        enemies[i].source.y = SOURCE_POS_PLAYER_STANDING_RIGHT_Y;
        enemies[i].source.w = SPRITE_WIDTH;
        enemies[i].lifepoints = DEFAULT_GRABBING_ENEMY_LIFEPOINTS;
        enemies[i].p = STANDING;
    }
}

void resetTabLaunch(bool launchEnemy[ENEMIES_LVL1]){
    int i;
    for(i = 0; i < ENEMIES_LVL1; i ++){
        launchEnemy[i] = false;
    }
}

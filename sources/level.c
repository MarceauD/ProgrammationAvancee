#include <stdio.h>
#include <stdlib.h>
#include "../headers/level.h"

/*RETURNS THE FIRST FIGHTER ALIVE*/
fighter * whichFighter(fighter enemyLeft[ENEMYS_LVL1]){
    int i = 0;
    while(!isAlive(enemyLeft[i])){
                    i = i + 1;
                }
        if(i >= ENEMYS_LVL1){
                return &enemyLeft[i-2];
        } else {
            return &enemyLeft[i];
        }

}

void MoveEnemies(fighter enemyLeft[ENEMYS_LVL1],fighter *player, Time *T, Time *T1,bool launchEnemy[ENEMYS_LVL1], int *k){
    MoveEnemyRight(&enemyLeft[0],player,T);
    update_currentTime(T1);
    if(time_gap(*T1) > TIME_BTW_ENEMIES){
        launchEnemy[*k] = true;
        update_previousTime(T1);
        *k = *k + 1;
    }
    int j;
    for(j=1; j < ENEMYS_LVL1; j ++){
        if(launchEnemy[j]){
            if(isAlive(enemyLeft[j-1])){
                MoveEnemyRight(&enemyLeft[j],&enemyLeft[j-1],T);
            }
            else{
                MoveEnemyRight(&enemyLeft[j],player,T);
            }
        }
    }
}

void BlitEnemies(fighter enemyLeft[ENEMYS_LVL1], SDL_Surface * screen, bool launchEnemy[ENEMYS_LVL1],Time *T){
    int i;
    for(i = 0; i < ENEMYS_LVL1; i ++ ){
        printf(" i : %d",i);
        if(launchEnemy[i]){
            BlitImagesConditions(&enemyLeft[i],screen,T);
        }
    }
}


void ChangeLevel(fighter * player, background * bg, GameState *gs){
    SDL_Surface * temp;
    temp = bg->surface;
    bg->surface = loadImage(bg->surface,"sprites/floors/floor2.bmp");
    SDL_FreeSurface(temp);
    player->r = RIGHT;
    player->rcSprite.y = DEFAULT_SPRITE_POSITION_Y;
    player->source.x = SOURCE_POS_PLAYER_STANDING_RIGHT_X;
    player->source.y = SOURCE_POS_PLAYER_STANDING_RIGHT_Y;
    gs->lvl = Level2;
}

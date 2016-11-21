#include <stdio.h>
#include <stdlib.h>
#include "../headers/level.h"

/*RETURNS THE FIRST FIGHTER ALIVE*/
fighter * whichFighter(fighter enemyLeft[ENEMYS_LVL1]){
    int i = 0;
    while(!isAlive(enemyLeft[i])){
                    i = i + 1;
                }

        if(i >= 10){
                return &enemyLeft[i-2];
        } else {
            return &enemyLeft[i];
        }

}

void MoveEnemys(fighter enemyLeft[ENEMYS_LVL1],fighter *player, Time *T, Time *T1,bool launchEnemy[ENEMYS_LVL1], int *k){
    MoveEnemyRight(&enemyLeft[0],player,T);
    update_currentTime(T1);
    if(time_gap(*T1) > 1000){
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

void BlitEnemys(fighter enemyLeft[ENEMYS_LVL1], SDL_Surface * screen, bool launchEnemy[ENEMYS_LVL1],Time *T){
    int i;
    for(i = 0; i < ENEMYS_LVL1; i ++ ){
        if(launchEnemy[i]){
            BlitImagesConditions(&enemyLeft[i],screen,T);
        }
    }
}

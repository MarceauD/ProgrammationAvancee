#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "defines.h"
#include "SDL.h"
#include "graphics.h"
#include "gamestate.h"
#include "stdbool.h"
#include "keyboard.h"
#include "event_manager.h"

/*animate the player moving to the left*/
extern void AnimatePlayerLeft(fighter *player);

/*animate the player moving to the right*/
extern void AnimatePlayerRight(fighter *player);

/*animate the player kneeling left and right*/
extern void AnimatePlayerDown(fighter *player);

/*animate the player jumping left and right*/
extern void AnimatePlayerUp(fighter *player, Time *T);

/*animate the player kicking left and right*/
extern void AnimatePlayerKick(fighter *player,fighter *enemy, Time *T, int delay);

/*animate the player dying left and right*/
extern void AnimatePlayerDeath(fighter *player, Time *T);

/*check if the player is in the middle of an animation, if so, it ends it before anything else*/
extern void CheckAnimations(fighter *player, fighter *enemy, Time *T);


#endif //ANIMATIONS_H

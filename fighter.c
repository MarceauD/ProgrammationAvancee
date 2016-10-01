#include "fighter.h"
#include "defines.h"


fighter init_fighter(){
    fighter F;
    //EN ATTENTE D'UNE VRAIE IMAGE
    F.sprite = SDL_CreateRGBSurface(0,SPRITE_WIDTH,SPRITE_HEIGHT,32,0,0,0,0);

    SDL_FillRect(F.sprite,NULL,SDL_MapRGB(F.sprite->format, 255,0,0));

    F.source = NULL;

    F.rcSprite.x = DEFAULT_SPRITE_POSITION_X;
    F.rcSprite.y = DEFAULT_SPRITE_POSITION_Y;

    F = write_lifepoints(DEFAULT_LIFEPOINTS,F);

    F = write_damage(DEFAULT_HITDAMAGE,F);

    //EN ATTENTE D'UNE MEILLEURE DEFINITION
    F.hitbox = F.rcSprite;

    return F;

}

bool isAlive(fighter F){
    return read_lifepoints(F) == 0;
}

int read_lifepoints(fighter F){
    return F.lifepoints;
}

int read_damage(fighter F){
    return F.damage;
}

fighter write_lifepoints(int lifepoints, fighter F){
    F.lifepoints = lifepoints;;
    return F;
}

fighter write_damage(int damage, fighter F){
    F.damage = damage;
    return F;
}

void FreeFighter(fighter F){
    SDL_FreeSurface(F.sprite);
    SDL_FreeSurface(F.source);
}

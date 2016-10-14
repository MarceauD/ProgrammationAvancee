#include "graphics.h"
/*load BMP sprite*/
SDL_Surface* loadImage(SDL_Surface* sprite,char* file){
    SDL_Surface* temp;
    temp = SDL_LoadBMP(file);

    /*show message error if sprite cant be found*/
    if (!temp){
        printf("Unable to load the BMP image%s\n",SDL_GetError());
        return NULL;
    }

    sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    return sprite;
}


/*fighter structure*/
fighter init_fighter(int fighter_kind){
    fighter F;

    /* load sprite*/
    if(fighter_kind == 0){
      
      F.sprite = loadImage(F.sprite,"sprite_fighter.bmp");
    }
    if(fighter_kind == 1){
      F.sprite = loadImage(F.sprite,"sprite_enemy.bmp");
    }
    /* setup sprite colorkey and turn on RLE */
    SDL_SetColorKey(F.sprite,SDL_SRCCOLORKEY, SDL_MapRGB(F.sprite->format,49,82,49));

    /*sprite's rectangle position*/
    F.source.x = 0;
    F.source.y = 0;
    F.source.h = SPRITE_HEIGHT;
    F.source.w = SPRITE_WIDTH;
    if(fighter_kind == 0){
        /*sprite's position in the game*/
        F.rcSprite.x = DEFAULT_SPRITE_POSITION_X;
        F.rcSprite.y = DEFAULT_SPRITE_POSITION_Y;
        F.rcSprite.h = DEFAULT_SPRITE_HEIGHT;
        F.rcSprite.w = DEFAULT_SPRITE_WIDTH;
	}
	if(fighter_kind == 1){
	  F.rcSprite.x = DEFAULT_ENEMY_POSITION_X;
	  F.rcSprite.y = DEFAULT_ENEMY_POSITION_Y;
	}

    /*lifepoints and damagepoints*/
    F = write_lifepoints(DEFAULT_LIFEPOINTS,F);
    F = write_damage(DEFAULT_HITDAMAGE,F);

    /*position : direction and standing/kneeling*/
    F.r = RIGHT;
    F.p = STANDING;

    //EN ATTENTE D'UNE MEILLEURE DEFINITION
    F.hitbox = F.rcSprite;

    return F;

}

/*Used fonctions in the fighter*/
bool isAlive(fighter F){
    return read_lifepoints(F) > 0;
}

    /*reading fonctions*/
int read_lifepoints(fighter F){
    return F.lifepoints;
}

int read_damage(fighter F){
    return F.damage;
}

    /*writing fonctions*/
fighter write_lifepoints(int lifepoints, fighter F){
    F.lifepoints = lifepoints;;
    return F;
}

 fighter write_damage(int damage, fighter F){
    F.damage = damage;
    return F;
}

    /*clean up fighter*/
void FreeFighter(fighter F){
    SDL_FreeSurface(F.sprite);
}



background init_background(){
    background bg;

    bg.surface = loadImage(bg.surface,"background.bmp");

    bg.rcBG.x = 0;
    bg.rcBG.y = TOP_HEIGHT;

    bg.source.x = BACKGROUND_WIDTH / 2;
    bg.source.y = 0;
    bg.source.w = SCREEN_WIDTH;
    bg.source.h = SCREEN_HEIGHT;

    return bg;

}

void FreeBackground(background bg){
    SDL_FreeSurface(bg.surface);
}



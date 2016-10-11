#include "graphics.h"

SDL_Surface* loadImage(SDL_Surface* sprite,char* file){
        SDL_Surface* temp;
        temp = SDL_LoadBMP(file);
        
        if (!temp){
                printf("Unable to load the BMP image%s\n",SDL_GetError());
                return NULL;
        }
        
        sprite = SDL_DisplayFormat(temp);
        SDL_FreeSurface(temp);

        return sprite;
}



fighter init_fighter(){
        fighter F;

        F.sprite = loadImage(F.sprite,"sprite_fighter.bmp");

        SDL_SetColorKey(F.sprite,SDL_SRCCOLORKEY, SDL_MapRGB(F.sprite->format,49,82,49));

        F.source.x = 0;
        F.source.y = 0;
        F.source.h = SPRITE_HEIGHT;
        F.source.w = SPRITE_WIDTH;

        F.rcSprite.x = DEFAULT_SPRITE_POSITION_X;
        F.rcSprite.y = DEFAULT_SPRITE_POSITION_Y;
        F.rcSprite.h = DEFAULT_SPRITE_HEIGHT;
        F.rcSprite.w = DEFAULT_SPRITE_WIDTH;

        F = write_lifepoints(DEFAULT_LIFEPOINTS,F);

        F = write_damage(DEFAULT_HITDAMAGE,F);

        F.r = RIGHT;

        F.p = STANDING;
        
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



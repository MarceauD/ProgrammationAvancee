#include "../headers/graphics.h"

/*load BMP sprite*/
SDL_Surface* loadImage(SDL_Surface* sprite,char* file){
    SDL_Surface* temp;
    temp = SDL_LoadBMP(file);

    /*show message error if sprite cant be found*/
    if (!temp){
        printf("Unable to load the BMP image %s\n",SDL_GetError());
        return NULL;
    }

    sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    return sprite;
}


/*fighter structure*/
fighter init_fighter(fighter_kind FK){
    fighter F;

    /* load sprite*/
    if(FK == PLAYER){

      F.sprite = loadImage(F.sprite,"sprites/sprite_fighter.bmp");
    }
    if(FK == GRABBING_ENEMY_LEFT){
      F.sprite = loadImage(F.sprite,"sprites/sprite_enemy.bmp");
    }

    /* setup sprite colorkey and turn on RLE */
    SDL_SetColorKey(F.sprite,SDL_SRCCOLORKEY, SDL_MapRGB(F.sprite->format,49,82,49));

    /*sprite's rectangle position*/
    if(FK == PLAYER || FK == GRABBING_ENEMY_LEFT){
      F.source.x = SOURCE_POS_PLAYER_STANDING_LEFT_X;
      F.source.y = SOURCE_POS_PLAYER_STANDING_LEFT_Y;
      F.source.h = SPRITE_HEIGHT;
      F.source.w = SPRITE_WIDTH;
    }

    if(FK == GRABBING_ENEMY_RIGHT){
      F.source.x = SOURCE_POS_PLAYER_STANDING_RIGHT_X;
      F.source.y = SOURCE_POS_PLAYER_STANDING_RIGHT_Y;
      F.source.h = SPRITE_HEIGHT;
      F.source.w = SPRITE_WIDTH;
    }

    if(FK == PLAYER){
      /*sprite's position in the game*/
      F.rcSprite.x = DEFAULT_SPRITE_POSITION_X;
      F.rcSprite.y = DEFAULT_SPRITE_POSITION_Y;
      F.rcSprite.h = DEFAULT_SPRITE_HEIGHT;
      F.rcSprite.w = DEFAULT_SPRITE_WIDTH;
	  }
  	if(FK == GRABBING_ENEMY_LEFT){
  	  F.rcSprite.x = DEFAULT_ENEMY_POSITION_LEFT_X;
  	  F.rcSprite.y = DEFAULT_ENEMY_POSITION_LEFT_Y;
  	}
    if(FK == GRABBING_ENEMY_RIGHT){
      F.rcSprite.x = DEFAULT_ENEMY_POSITION_RIGHT_X;
  	  F.rcSprite.y = DEFAULT_ENEMY_POSITION_RIGHT_Y;
  	}

    /*lifepoints and damage points*/
    if(FK == PLAYER){
        F = write_lifepoints(DEFAULT_PLAYER_LIFEPOINTS,F);
        F = write_damage(DEFAULT_PLAYER_HITDAMAGE,F);
	      F.f = PLAYER;
    }
    if(FK != PLAYER){
        F = write_lifepoints(DEFAULT_GRABBING_ENEMY_LIFEPOINTS,F);
        F = write_damage(DEFAULT_GRABBING_ENEMY_HITDAMAGE,F);
        if (FK == GRABBING_ENEMY_LEFT) F.f = GRABBING_ENEMY_LEFT;
        if (FK == GRABBING_ENEMY_RIGHT) F.f = GRABBING_ENEMY_RIGHT;
    }

    if(FK != GRABBING_ENEMY_RIGHT) F.r = LEFT;
    else F.r = RIGHT;
    F.p = STANDING;

    //EN ATTENTE D'UNE MEILLEURE DEFINITION
    F.hitbox = F.rcSprite;

    F.previousTime = 0;

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
    if(F.sprite != NULL){
        SDL_FreeSurface(F.sprite);
    }
}



background init_background(){
    background bg;

    bg.surface = loadImage(bg.surface,"sprites/floors/floor1.bmp");

    bg.rcBG.x = 0;
    bg.rcBG.y = 0;

    bg.source.x = BACKGROUND_WIDTH / 2;
    bg.source.y = 0;
    bg.source.w = SCREEN_WIDTH;
    bg.source.h = SCREEN_HEIGHT;

    return bg;

}

void FreeBackground(background bg){
    if(bg.surface != NULL){
        SDL_FreeSurface(bg.surface);
    }
}



void BlitImages(background *bg, fighter *player, SDL_Surface *screen, Time *T){
        SDL_BlitSurface(bg->surface,&bg->source,screen,&bg->rcBG);

        BlitImagesConditions(player, screen, T);
}

void BlitImagesConditions(fighter *player, SDL_Surface *screen, Time *T){
	if(!isAlive(*player)){
    		AnimatePlayerDeath(player,T);
		if(player->p == DYING){
			SDL_BlitSurface(player->sprite,&player->source,screen,&player->rcSprite);
		}
	}
	else{
        SDL_BlitSurface(player->sprite,&player->source,screen,&player->rcSprite);
	}
}

#include "../headers/interface.h"

LPV init_LPV(fighter player){

	LPV LifeP_V;
	LifeP_V.sprite = SDL_CreateRGBSurface(0,20 * read_lifepoints(player),20,32,0,0,0,0);
	SDL_FillRect(LifeP_V.sprite,NULL,SDL_MapRGB(LifeP_V.sprite->format,255,0,0));

	LifeP_V.rcSprite.x = SCREEN_WIDTH - 210;
	LifeP_V.rcSprite.y = 20;

	LifeP_V.source.x = 0;
	LifeP_V.source.y = 0;
	LifeP_V.source.w = 20 * read_lifepoints(player);
	LifeP_V.source.h = 20;
	return LifeP_V;

}

void ViewLifepoints(LPV *LifePointsView, fighter player, SDL_Surface *screen){
	LifePointsView->source.w = 20 * read_lifepoints(player);
	SDL_BlitSurface(LifePointsView->sprite,&LifePointsView->source,screen,&LifePointsView->rcSprite);
}

/*
void ViewScore(GameState GS){
	TODO ...

}

void ViewTime(GameState GS){
	TODO...

}*/

void FreeLPV(LPV Lifepoints){
    if(Lifepoints.sprite != NULL){
        SDL_FreeSurface(Lifepoints.sprite);
    }
}


Pause init_Pause(){
    Pause P;
    P.sprite = loadImage(P.sprite, "sprites/pause.bmp");
    SDL_SetAlpha(P.sprite,SDL_SRCALPHA,1);

    P.rcSprite.x = 0;
    P.rcSprite.y = 0;
    P.rcSprite.w = SCREEN_WIDTH;
    P.rcSprite.h = SCREEN_HEIGHT;

    return P;
}

void PauseGame(Pause P, GameState *G, SDL_Surface *screen){
    SDL_Event Event;
    KeyboardManagerPause(Event,G);
    SDL_BlitSurface(P.sprite,NULL,screen,&P.rcSprite);
}


void FreePause(Pause P){
    if(P.sprite != NULL){
        SDL_FreeSurface(P.sprite);
    }
}



void Menu(SDL_Surface * menu, SDL_Surface * Rect, SDL_Rect rcRect, SDL_Rect *source, Time * T, SDL_Event event,GameState *gameState, SDL_Surface * screen, fighter *demo){
    KeyboardManagerMenu(event,gameState);
    SDL_BlitSurface(menu,NULL,screen,NULL);
    SDL_BlitSurface(demo->sprite,&demo->source,screen,&demo->rcSprite);
    update_currentTime(T);
    if(time_gap(*T) > 350){
        if(source->y == 0){
            source->y = 50;
        }
        else{
            source->y = 0;
        }
        update_previousTime(T);
    }
    SDL_BlitSurface(Rect,source,screen,&rcRect);
    AnimatePlayerKick(demo,demo,demo,T,250);
    SDL_UpdateRect(screen,0,0,0,0);
}


void init_Menu(SDL_Rect *rcRect, SDL_Rect *source, fighter *demo){
    rcRect->x = 0;
    rcRect->y = 280;
    source->x = 0;
    source->y = 0;
    source->w = 800;
    source->h = 50;
    demo->rcSprite.x = SCREEN_WIDTH / 2 - SPRITE_WIDTH;
    demo->rcSprite.y = SCREEN_HEIGHT / 2 - SPRITE_HEIGHT / 2 ;
}


void EndMenuVictory(SDL_Surface * screen, GameState *gameState,Time *T){
    SDL_Surface * endmenu;
    fighter beloved;
    SDL_Event event;

    endmenu = loadImage(NULL,"sprites/endMenuVictory.bmp");

    beloved.sprite = loadImage(NULL,"sprites/end_game.bmp");
    SDL_SetColorKey(beloved.sprite,SDL_SRCCOLORKEY, SDL_MapRGB(beloved.sprite->format,39,82,39));
    beloved.previousTime = 0;
    beloved.source.x = 2;
    beloved.source.w = 50   ;
    beloved.source.y = 0;
    beloved.rcSprite.x = (SCREEN_WIDTH / 2 )- SPRITE_WIDTH;
    beloved.rcSprite.y = SCREEN_HEIGHT / 2;
    beloved.rcSprite.w = 50;

    while(gameState->EndMenu){
        KeyboardManagerEndMenu(event,gameState);
        update_currentTime(T);
        if(T->currentTime - beloved.previousTime > 250){
            if(beloved.source.x > 110){
                beloved.source.x = 0;
            }
            else {
                beloved.source.x = beloved.source.x + 50;
            }
            beloved.previousTime = T->currentTime;
        }
        SDL_BlitSurface(endmenu,NULL,screen,NULL);
        SDL_BlitSurface(beloved.sprite,&beloved.source,screen,&beloved.rcSprite);
        SDL_UpdateRect(screen,0,0,0,0);
    }

    SDL_FreeSurface(endmenu);
    FreeFighter(beloved);
}

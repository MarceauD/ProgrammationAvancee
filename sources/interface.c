#include "../headers/interface.h"

LPV init_LPV(fighter player){

	LPV LifeP_V;
	LifeP_V.sprite = SDL_CreateRGBSurface(0,20 * read_lifepoints(player),20,32,0,0,0,0);
	SDL_FillRect(LifeP_V.sprite,NULL,SDL_MapRGB(LifeP_V.sprite->format,200,142,15));

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
	SDL_FreeSurface(Lifepoints.sprite);
}

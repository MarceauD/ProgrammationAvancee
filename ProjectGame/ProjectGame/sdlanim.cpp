#include "SDL.h"
#include "HandleKeyboard.cpp"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE     32

int gameover;

/* source and destination rectangles */
SDL_Rect rcSrc, rcSprite;

int main(int argc, char* argv[])

{

	SDL_Surface *screen, *temp, *sprite, *background, *theme;

	SDL_Rect rcbackground;

	int colorkey;

        

	/* create window */

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);



	/* set keyboard repeat */

	SDL_EnableKeyRepeat(70, 70);



	/* load sprite */

	temp   = SDL_LoadBMP("sprite.bmp");

	sprite = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);



	/* setup sprite colorkey and turn on RLE */                    
 /*sprite background transparency*/
	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);

	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
        SDL_SetColorKey(theme, SDL_SRCCOLORKEY ¡ SDL_RLEACCEL, colorkey);



	/* load background_2 */

	temp  = SDL_LoadBMP("background2.bmp");

	background = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	/* load theme */

	temp  = SDL_LoadBMP("background3.bmp");

	theme = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);
        
        SDL_SetColorKey(theme, SDL_SRCCOLORKEY ¡ SDL_RLEACCEL, colorkey);


	/* set sprite position */

	rcSprite.x = 300;

	rcSprite.y = 300;



	/* set animation frame */

	rcSrc.x = 128;

	rcSrc.y = 0;

	rcSrc.w = SPRITE_SIZE;

	rcSrc.h = SPRITE_SIZE;



	gameover = 0;



	/* message pump */

	while (!gameover)

	{

		SDL_Event event;

		

		/* look for an event */

// 		if (SDL_PollEvent(&event)) {
// 
// 			HandleKeyboard(event);
// 
// 		}



		/* collide with edges of screen */

		if (rcSprite.x <= 0)

			rcSprite.x = 0;

		if (rcSprite.x >= SCREEN_WIDTH - SPRITE_SIZE) 

			rcSprite.x = SCREEN_WIDTH - SPRITE_SIZE;



		if (rcSprite.y <= 0)

			rcSprite.y = 0;

		if (rcSprite.y >= SCREEN_HEIGHT - SPRITE_SIZE) 

			rcSprite.y = SCREEN_HEIGHT - SPRITE_SIZE;



		/* draw the background */
                
                rcbackground.x = 0;

                rcbackground.y = 0;

                SDL_BlitSurface(background, NULL, screen, &rcbackground);
                
		/* draw the theme */

                SDL_BlitSurface(theme, NULL, screen, &rcSprite);



		/* draw the sprite */

		SDL_BlitSurface(sprite, &rcSrc, screen, &rcSprite);



		/* update the screen */

		SDL_UpdateRect(screen, 0, 0, 0, 0);

	}



	/* clean up */

	SDL_FreeSurface(sprite);

	SDL_FreeSurface(background);
        
	SDL_FreeSurface(theme);

	SDL_Quit();



	return 0;

}


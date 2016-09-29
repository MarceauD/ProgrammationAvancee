#include "SDL.h"

extern int gameover;
extern SDL_Rect rcSrc, rcSprite;


void HandleKeyboard(SDL_Event event) {
    switch (event.type) {
            /* close button clicked */
        case SDL_QUIT:
            gameover = 1;
            break;
            
            /* handle the keyboard */
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    gameover = 1;
                    break;
                case SDLK_LEFT:
                    if ( rcSrc.x == 192 )
                        rcSrc.x = 224;
                    else
                        rcSrc.x = 192;
                    rcSprite.x -= 5;
                    break;
                case SDLK_RIGHT:
                    if ( rcSrc.x == 64 )
                        rcSrc.x = 96;
                    else
                        rcSrc.x = 64;
                    rcSprite.x += 5;
                    break;
                case SDLK_UP:
                    if ( rcSrc.x == 0 )
                        rcSrc.x = 32;
                    else
                        rcSrc.x = 0;
                    rcSprite.y -= 5;
                    break;
                case SDLK_DOWN:
                    if ( rcSrc.x == 128 )
                        rcSrc.x = 160;
                    else
                        rcSrc.x = 128;
                    rcSprite.y += 5;
                    break;
            }
            break;
    }
}

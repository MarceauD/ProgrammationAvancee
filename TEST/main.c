#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "SDL/SDL.h"

int main(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        printf("Unable to init SDL :%s",SDL_GetError());
        return 1;
    }

    atexit(SDL_Quit());  //Make sure SDL quits before exiting

    SDL_WM_SetCaption("GAME_TITLE","GAME_TITLE");
    SDL_Surface* screen, bg;
    bool done;
    done = false;

    SDL_Event event;

    screen = SDL_SetVideoMode(640, 480, 0, 0);

    if (!screen){
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    bg = SDL_CreateRGBSurface(0,50,50,32,0,0,0,0);



    if(!bg){
        printf("Unable to load the background %s\n", SDL_GetError());
        return 1;
    }

    while(!done){

        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    done = true;
                    break;
                }
            }
        }

      SDL_FillRect(bg,NULL, SDLMapRGB(bg->format, 255,0,0));
      SDL_BlitSurface(bg,NULL,screen,NULL);

      SDL_UpdateRect(screen, 0, 0, 0, 0);

    }

    SDL_FreeSurface(temp);



    SDL_FreeSurface(bg);
    SDL_FreeSurface(screen);

    SDL_Quit();

    return 0;
}

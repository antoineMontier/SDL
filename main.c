#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void SDL_ExitWithError(const char *string);

int main(int argc, char *argv[]){//compile with     gcc main.c -o main $(sdl2-config --cflags --libs)

    if(0 != SDL_Init(/*flag*/ SDL_INIT_VIDEO))//lots of flags like SDL_INIT_AUDIO ; *_VIDEO ; *_EVERYTHING... To separe with '|'
        SDL_ExitWithError("Initialisation SDL");
    //at this point, the SDL is well initialised, we can afford it because of the if

    SDL_Window *w;//open a window command

    w = SDL_CreateWindow("First SDL2 window",   //name of the window
                        SDL_WINDOWPOS_CENTERED, //x position
                        SDL_WINDOWPOS_CENTERED, //y position
                        800, 600,               //width, length
                        0);                     //window displaying  for example : "SDL_WINDOW_SHOWN"

    if(w == NULL)
        SDL_ExitWithError("window creation");


    SDL_Delay(5000);//waiting delay, in ms


    SDL_DestroyWindow(w);
    SDL_Quit();

    return 0;
}

void SDL_ExitWithError(const char *string){
    SDL_Log("Error : %s > %s\n", string, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

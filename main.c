#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void SDL_ExitWithError(const char *string);

int main(int argc, char *argv[]){//compile with     gcc main.c -o main $(sdl2-config --cflags --libs)

    if(0 != SDL_Init(/*flag*/ SDL_INIT_VIDEO))//lots of flags like SDL_INIT_AUDIO ; *_VIDEO ; *_EVERYTHING... To separe with '|'
        SDL_ExitWithError("Initialisation SDL");
    //at this point, the SDL is well initialised, we can afford it because of the if

    SDL_Window *w;//open a window command
    SDL_Renderer *ren;//render creation


    w = SDL_CreateWindow("First SDL2 window",   //name of the window
                        SDL_WINDOWPOS_CENTERED, //x position
                        SDL_WINDOWPOS_CENTERED, //y position
                        800, 600,               //width, length
                        0);                     //window displaying  for example : "SDL_WINDOW_SHOWN"

    if(w == NULL)
        SDL_ExitWithError("window creation");

    /*--------------------------------------------------------------------------------*/
    ren = SDL_CreateRenderer(w, -1, SDL_RENDERER_SOFTWARE);
                                    /*
                                    SDL_RENDERER_SOFTWARE           asks the software to proceed
                                    SDL_RENDERER_ACCELERATED        asks the graphic card to help proceed
                                    SDL_RENDERER_PRESENTVSYNC       used for vertical display
                                    SDL_RENDERER_TARGETTEXTURE      not useful for me, used to focus on a precise texture
                                    */

    if(ren == NULL)
        SDL_ExitWithError("render creation failed");

    SDL_RenderPresent(ren);//refresh the render


    if(SDL_RenderClear(ren) != 0)
        SDL_ExitWithError("render deletion failed"); //delete the render ; may be usefull if we want to modify


    

    SDL_Delay(5000);//waiting delay, in ms
    /*--------------------------------------------------------------------------------*/

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(w);
    SDL_Quit();

    return 0;
}

void SDL_ExitWithError(const char *string){
    SDL_Log("Error : %s > %s\n", string, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

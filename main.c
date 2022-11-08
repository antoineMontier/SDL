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


    if(SDL_CreateWindowAndRenderer(800, 600, 0, &w, &ren) !=0)
        SDL_ExitWithError("window and render creation failed");

    /*--------------------------------------------------------------------------------*/
    SDL_RenderPresent(ren);//refresh the render
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

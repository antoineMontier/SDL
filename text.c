#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#define HEIGHT 720
#define WIDTH 1080

void SDL_ExitWithError(const char *string);

int main(int argc, char *argv[]){//compile with     gcc text.c -o text -lm -lSDL_ttf $(sdl2-config --cflags --libs) && ./text
    printf("\n\n");
    SDL_Window *w;//open a window command
    printf("window opened ...\n");
    SDL_Renderer *ren;//render creation
    printf("renderer opened ...\n");
    TTF_Font* font;
    printf("font opened...\n");

    if(0 != SDL_Init(/*flag*/ SDL_INIT_VIDEO))//lots of flags like SDL_INIT_AUDIO ; *_VIDEO ; *_EVERYTHING... To separe with '|'
        SDL_ExitWithError("Initialisation SDL failed");
    else
        printf("SDL openned...\n");
    //at this point, the SDL is well initialised, we can afford it because of the if


    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &w, &ren) !=0)
        SDL_ExitWithError("window and render creation failed\n");
    else    
        printf("renderer and window created...\n");

//===================================================================================================================================================
    if(TTF_Init() != 0)
        SDL_ExitWithError("Initialisation TTF failed");
    else
        printf("TTF opened...\n");
















    //////////////////////////////////////////////
    SDL_RenderPresent(ren);
    printf("renderer refreshed...\n");
    SDL_Delay(1000);    
    printf("1000 ms waited...\n");
    //////////////////////////////////////////////




//===================================================================================================================================================

    TTF_Quit();
    printf("quitted TTF...\n");
    TTF_CloseFont(font);
    printf("closed font...\n");
    SDL_DestroyRenderer(ren);
    printf("renderer destroyed...\n");
    SDL_DestroyWindow(w);
    printf("window destroyed...\n");
    SDL_Quit();
    printf("SDL quitted");

    printf("\n\n");
    return 0;
}


void SDL_ExitWithError(const char *string){
    SDL_Log("Error : %s > %s\n", string, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}








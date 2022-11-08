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
    //                        ren, r  , g  , b  , alpha
    if(SDL_SetRenderDrawColor(ren, 112, 168, 237, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("failed to set color");


    if(SDL_RenderDrawPoint(ren, 100, 200) != 0)         //point
        SDL_ExitWithError("failed to draw a point");

    if(SDL_RenderDrawLine(ren, 200, 200, 300, 550) != 0)//line
        SDL_ExitWithError("failed to draw a line");

    if(SDL_SetRenderDrawColor(ren, 255, 168, 20, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("failed to set color");

    SDL_Rect rectangle;
    rectangle.x = 400;
    rectangle.y = 50;
    rectangle.w = 180;
    rectangle.h = 130;

    if(SDL_RenderDrawRect(ren, &rectangle) != 0)
        SDL_ExitWithError("failed to draw an empty rectangle");

    if(SDL_SetRenderDrawColor(ren, 0, 200, 20, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("failed to set color");

    rectangle.x = 50;
    rectangle.y = 450;
    rectangle.w = 180;
    rectangle.h = 130;

    if(SDL_RenderFillRect(ren, &rectangle) != 0)
        SDL_ExitWithError("failed to draw a full rectangle");

        //lets create a red border for the rectangle :
    
    if(SDL_SetRenderDrawColor(ren, 255, 0, 0, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("failed to set color");

    if(SDL_RenderDrawRect(ren, &rectangle) != 0)
        SDL_ExitWithError("failed to draw a full rectangle");

        //lets thick it :

    rectangle.x = 51;
    rectangle.y = 451;
    rectangle.w = 178;
    rectangle.h = 128;

    if(SDL_RenderDrawRect(ren, &rectangle) != 0)
        SDL_ExitWithError("failed to draw a full rectangle");
    


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

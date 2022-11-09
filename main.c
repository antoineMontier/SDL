#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void SDL_ExitWithError(const char *string);
void point(SDL_Renderer* r, int x, int y);
void line(SDL_Renderer* r, int x1, int y1, int x2, int y2);
void color(SDL_Renderer* r, int red, int green, int blue, int alpha);
void rect(SDL_Renderer* r, int x, int y, int width, int height, int filled);
void circle(SDL_Renderer * r, int centreX, int centreY, int radius);
void openSDL(int x, int y, int mode, SDL_Window**w, SDL_Renderer**r);
void closeSDL(SDL_Window**w, SDL_Renderer**r);

int main(int argc, char *argv[]){//compile with     gcc main.c -o main $(sdl2-config --cflags --libs)


    SDL_Window *w;//open a window command
    SDL_Renderer *ren;//render creation

    openSDL(600, 800, 0, &w, &ren);


    /*--------------------------------------------------------------------------------*/
    

    color(ren, 30, 58, 200, 255);

    point(ren, 5, 2);
    point(ren, 5, 3);
    point(ren, 5, 4);
    point(ren, 5, 5);

    line(ren, 20, 30, 80, 90);
    line(ren, 150, 92, 420, 340);

    color(ren, 200, 220, 150, 255);

    rect(ren, 400, 50, 180, 130, 1);

    circle(ren, 50, 100, 200);


    color(ren, 0, 200, 20, SDL_ALPHA_OPAQUE);
    rect(ren, 50, 450, 180, 130, 1);
    //lets create a red border for the rectangle :
    
    color(ren, 255, 0, 0, SDL_ALPHA_OPAQUE);
    rect(ren, 50, 450, 180, 130, 0);
    //lets thick it :
    rect(ren, 51, 451, 178, 128, 0);
    

    SDL_RenderPresent(ren);//refresh the render
    SDL_Delay(5000);//waiting delay, in ms
    /*--------------------------------------------------------------------------------*/

    
    closeSDL(&w, &ren);
    printf("closed successfully !\n");
    return 0;
}

void SDL_ExitWithError(const char *string){
    SDL_Log("Error : %s > %s\n", string, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void point(SDL_Renderer* r, int x, int y){
    if(SDL_RenderDrawPoint(r, x, y) != 0)
        SDL_ExitWithError("failed to draw point");
}

void line(SDL_Renderer* r, int x1, int y1, int x2, int y2){
    if(SDL_RenderDrawLine(r, x1, y1, x2, y2) != 0)//line
        SDL_ExitWithError("failed to draw line");
}

void color(SDL_Renderer* r, int red, int green, int blue, int alpha){
    if(SDL_SetRenderDrawColor(r, red, green, blue, alpha) != 0)
        SDL_ExitWithError("failed to set color");
}

void rect(SDL_Renderer* r, int x, int y, int width, int height, int filled){
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = width;
    rectangle.h = height;

    if(filled){
        if(SDL_RenderFillRect(r, &rectangle) != 0)
            SDL_ExitWithError("failed to draw a full rectangle");
    }
    if(!filled){
        if(SDL_RenderDrawRect(r, &rectangle) != 0)
            SDL_ExitWithError("failed to draw a full rectangle");
    }
}

void circle(SDL_Renderer * r, int cx, int cy, int radius){
   const int diameter = (radius * 2);

   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y){
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(r, cx + x, cy - y);
      SDL_RenderDrawPoint(r, cx + x, cy + y);
      SDL_RenderDrawPoint(r, cx - x, cy - y);
      SDL_RenderDrawPoint(r, cx - x, cy + y);
      SDL_RenderDrawPoint(r, cx + y, cy - x);
      SDL_RenderDrawPoint(r, cx + y, cy + x);
      SDL_RenderDrawPoint(r, cx - y, cy - x);
      SDL_RenderDrawPoint(r, cx - y, cy + x);

      if (error <= 0){
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0){
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void openSDL(int x, int y, int mode, SDL_Window**w, SDL_Renderer**r){

    if(0 != SDL_Init(/*flag*/ SDL_INIT_VIDEO))//lots of flags like SDL_INIT_AUDIO ; *_VIDEO ; *_EVERYTHING... To separe with '|'
        SDL_ExitWithError("Initialisation SDL failed");
    //at this point, the SDL is well initialised, we can afford it because of the if


    if(SDL_CreateWindowAndRenderer(x, y, mode, w, r) !=0)
        SDL_ExitWithError("window and render creation failed");

}

void closeSDL(SDL_Window**w, SDL_Renderer**r){
    SDL_DestroyRenderer(*r);
    SDL_DestroyWindow(*w);
    SDL_Quit();
}



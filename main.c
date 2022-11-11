#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 600
#define HEIGHT 800

void SDL_ExitWithError(const char *string);
void point(SDL_Renderer* r, int x, int y);
void mark(SDL_Renderer* r, int x, int y, int thickness);
void line(SDL_Renderer* r, int x1, int y1, int x2, int y2);
void color(SDL_Renderer* r, int red, int green, int blue, int alpha);
void rect(SDL_Renderer* r, int x, int y, int height, int width, int filled);
void circle(SDL_Renderer * r, int centreX, int centreY, int radius, int filled);
void openSDL(int x, int y, int mode, SDL_Window**w, SDL_Renderer**r);
void closeSDL(SDL_Window**w, SDL_Renderer**r);
void background(SDL_Renderer* r, int red, int green, int blue);
void triangle(SDL_Renderer* r, int x1, int y1, int x2, int y2, int x3, int y3, int filled);
double dist(double x1, double y1, double x2, double y2);
int inTheTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double a, double b);
double min(double a, double b, double c);
double max(double a, double b, double c);
void triangle(SDL_Renderer* r, int x1, int y1, int x2, int y2, int x3, int y3, int filled);







int main(int argc, char *argv[]){//compile with     gcc main.c -o main $(sdl2-config --cflags --libs)


    SDL_Window *w;//open a window command
    SDL_Renderer *ren;//render creation

    openSDL(WIDTH, HEIGHT, 0, &w, &ren);


    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    SDL_bool program_launched = SDL_TRUE; //SDL_FALSE or SDL_TRUE
    SDL_bool circ = SDL_FALSE;
    SDL_bool rectangle = SDL_FALSE;


    while(program_launched){//principal loop
        SDL_Event evt;

            background(ren, 0, 0, 0);

    
            color(ren, 255, 0, 0, 255);

            triangle(ren, 150, 150, 150, 250, 300, 275, 1);

            circle(ren, 300, 300, 50, 1);

    



        SDL_RenderPresent(ren);//refresh the render



        while(SDL_PollEvent(&evt)){//reads all the events (mouse moving, key pressed...)        //possible to wait for an event with SDL_WaitEvent
            switch(evt.type){

                case SDL_QUIT:
                    program_launched = SDL_FALSE;//quit the program if the user closes the window
                    break;

                case SDL_KEYDOWN:                   //SDL_KEYDOWN : hold a key            SDL_KEYUP : release a key
                    switch (evt.key.keysym.sym){//returns the key ('0' ; 'e' ; 'SPACE'...)

                        case SDLK_ESCAPE:
                            program_launched = SDL_FALSE;//escape the program by pressing esc
                            break;



                        default:
                            break;
                    }



                default:
                    break; 

            }
        }

        

    
        


    


    }




    /*SDL_RenderPresent(ren);//refresh the render
    SDL_Delay(5000);//waiting delay, in ms*/
    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

    
    closeSDL(&w, &ren);
    printf("closed successfully !\n");
    return 0;
}

void SDL_ExitWithError(const char *string){
    SDL_Log("Error : %s > %s\n", string, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void mark(SDL_Renderer* r, int x, int y, int thickness){
    for(int a = y - thickness ; a <= y + thickness ; a++){
        for(int b = x - thickness ; b <= x + thickness; b++){
            point(r, b, a);
        }
    }
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

void rect(SDL_Renderer* r, int x, int y, int height, int width, int filled){
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

void circle(SDL_Renderer * r, int cx, int cy, int radius, int filled){
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

    if(filled){
        int s_x = cx - radius;
        int s_y = cy - radius;
        int f_x = cx + radius;
        int f_y = cy + radius;

        for(int a = s_x ; a <= f_x ; a++){
            for(int b = s_y ; b <= f_y ; b++){
                if(dist(cx, cy, a, b) < radius)
                    point(r, a, b);
            }
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

void background(SDL_Renderer* r, int red, int green, int blue){
    color(r, red, green, blue, 255);
    rect(r, 0, 0, HEIGHT, WIDTH, 1);
}

double dist(double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int inTheTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double a, double b){
    int sign1 = -1, sign2 = -1, sign3 = -1;
    if(((x2-x1)*(b-y1) - (y2-y1)*(a-x1)) >= 0)
        sign1 = 1;

    if(((x3-x2)*(b-y2) - (y3-y2)*(a-x2)) >= 0)
        sign2 = 1;

    if(((x1-x3)*(b-y3) - (a-x3)*(y1-y3)) >= 0)
        sign3 = 1;

    if(sign1 == sign2 && sign2 == sign3)
        return 1;
    return 0;
}

double min(double a, double b, double c){
    if(a < b && a < c)
        return a;
    if(b < a && b < c)
        return b;
    if(c < a && c < b)
        return c;
}

double max(double a, double b, double c){
    if(a > b && a > c)
        return a;
    if(b > a && b > c)
        return b;
    if(c > a && c > b)
        return c;
}

void triangle(SDL_Renderer* r, int x1, int y1, int x2, int y2, int x3, int y3, int filled){
    line(r, x1, y1, x2, y2);
    line(r, x2, y2, x3, y3);
    line(r, x3, y3, x1, x1);
    if(filled){

        int s_x = min(x1, x2, x3);
        int s_y = min(y1, y2, y3);
        int f_x = max(x1, x2, x3);
        int f_y = max(y1, y2, y3);

        for(int a = s_x ; a <= f_x ; a++){
            for(int b = s_y ; b <= f_y ; b++){
                if(inTheTriangle(x1, y1, x2, y2, x3, y3, a, b))
                    point(r, a, b);
            }
        }
    }
}

#include "SDL_Basics.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ // compile and execute with     gcc main.c -o main -lm -lSDL2_ttf $(sdl2-config --cflags --libs) && ./main

    SDL_Window *win;   // open a window command
    SDL_Renderer *ren; // render creation
    openSDL(WIDTH, HEIGHT, 0, "SDL-Lab", &win, &ren);
    SDL_SetWindowResizable(win, SDL_TRUE);
    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    SDL_bool program_launched = SDL_TRUE; // SDL_FALSE or SDL_TRUE

    TTF_Font *font;
    setFont(&font, "a.ttf", 50);
    double x = 150, y = 300, w = 150, h = 200, tl = 50, tr = 10, br = 40, bl = 1;

    while (program_launched)
    { // principal loop
        SDL_Event evt;

        //ellipse
        color(ren, 255, 0, 0, 0);
        ellipse(ren, 200, 250, 30, 70, 0);
        ellipse(ren, 200, 450, 30, 70, 1);
        
        //triangle
        color(ren, 0, 255, 0, 0);
        triangle(ren, 800, 800, 900, 950, 850, 700, 1);
        triangle(ren, 900, 750, 920, 770, 980, 600, 0);

        //circle
        color(ren, 0, 0, 255, 0);
        circle(ren, 100, 800, 30, 1);
        circle(ren, 100, 900, 30, 0);

        //roundRect
        color(ren, 255, 0, 255, 0);
        roundRect(ren, 750, 100, 200, 100, 1, 0, 0, 0, 70);
        roundRect(ren, 750, 250, 200, 100, 0, 70, 0, 0, 70);


        SDL_Delay(100);

        SDL_RenderPresent(ren); // refresh the render

        while (SDL_PollEvent(&evt))
        { // reads all the events (mouse moving, key pressed...)        //possible to wait for an event with SDL_WaitEvent
            switch (evt.type)
            {
            case SDL_WINDOWEVENT:
                if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
                    printf("MESSAGE:Resizing window...\n");
                    //resizeWindow(evt.window.data1, evt. window.data2);
                }
                break;
            case SDL_QUIT:
                program_launched = SDL_FALSE; // quit the program if the user closes the window
                break;

            case SDL_KEYDOWN: // SDL_KEYDOWN : hold a key            SDL_KEYUP : release a key
                switch (evt.key.keysym.sym)
                { // returns the key ('0' ; 'e' ; 'SPACE'...)

                case SDLK_ESCAPE:
                    program_launched = SDL_FALSE; // escape the program by pressing esc
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

    closeSDL(&win, &ren);
    printf("closed successfully !\n");
    return 0;
}

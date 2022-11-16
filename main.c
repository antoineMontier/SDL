#include "SDL_Basics.h"
#include <stdio.h>
#include <stdlib.h>









int main(int argc, char *argv[]){//compile and execute with     gcc main.c -o main -lm -lSDL2_ttf $(sdl2-config --cflags --libs) && ./main

    SDL_Window *w;//open a window command
    SDL_Renderer *ren;//render creation

    openSDL(WIDTH, HEIGHT, 0, &w, &ren);


    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    SDL_bool program_launched = SDL_TRUE; //SDL_FALSE or SDL_TRUE


    TTF_Font * font;
    setFont(&font, "a.ttf", 50);


    while(program_launched){//principal loop
        SDL_Event evt;

            background(ren, 128, 64, 0, WIDTH, HEIGHT);

    
            color(ren, 255, 0, 0, 255);//red
            roundRect(ren, 100, 100, 50, 120, 1, 20);

            circle(ren, 200, 600, 80, 1);
            roundRect(ren, 400, 600, 50, 80, 0, 10);

            text(ren, 30, 30, "test", font, 162, 30, 200);

            color(ren, 0, 255, 0, 255);//green
            roundRect(ren, 300, 300, 200, 100, 1, 20);
            roundRect(ren, 100, 300, 80, 40, 0, 10);

            circle(ren, 150, 500, 50, 0);



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

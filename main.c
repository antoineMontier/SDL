#include <SDL.h>
#include <stdio.h>

int main(int argc, char argv){//compile with     gcc main.c -o main $(sdl2-config --cflags --libs)

    SDL_version nb;
    SDL_VERSION(&nb);

    printf("SDL %d.%d.%d !\n", nb.major, nb.minor, nb.patch);
    return 0;


}

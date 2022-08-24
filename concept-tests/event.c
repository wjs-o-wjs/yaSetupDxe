#include <event.h>
#include <SDL2/SDL.h>
#include <main.h>
void main_loop(void)
{
    SDL_Event event;
    while(1) {
        while (SDL_WaitEvent(&event)) {
        // decide what to do with this event.
            if (event.type==SDL_QUIT) {
                fini(EXIT_SUCCESS);
            }
        }
    }
}

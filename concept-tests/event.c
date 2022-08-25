#include <event.h>
#include <SDL2/SDL.h>
#include <main.h>
#include <compositor.h>
void main_loop(void)
{
    SDL_Event event;
    while(1) {
        while (SDL_WaitEvent(&event)) {
        // decide what to do with this event.
            switch(event.type) {
                case SDL_QUIT: {fini(EXIT_SUCCESS);break;}
                case SDL_MOUSEMOTION: {
                    move_mouse(event.motion.x,event.motion.y);
                }
            }
        }
    }
}

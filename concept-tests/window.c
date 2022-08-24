#include <window.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <main.h>
pixel* main_screen;
SDL_Window* window;
SDL_Surface* surface;
void create_window(uint32_t width, uint32_t height)
{
    //GO AWAY GLFW! WE LOVE SDL!
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        fputs("Failed to initialize SDL.\n",stderr);
        fini(EXIT_FAILURE);
    }
    window = SDL_CreateWindow("Emulated Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window==NULL) {
        fputs("Failed to create SDL window.\n",stderr);
        fini(EXIT_FAILURE);
    }
    surface = SDL_GetWindowSurface(window);
    if(surface==NULL) {
        fputs("Failed to get surface from window.\n",stderr);
        fini(EXIT_FAILURE);
    }
    main_screen = surface->pixels;
}
void update_window()
{
    SDL_UpdateWindowSurface(window);
}
void destroy_window()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

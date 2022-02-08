#include <SDL2/SDL.h>
#include "display.h"
#include <stdio.h>

SDL_Window *window;
SDL_Surface *surface;

void display_init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 )
    {
        printf("Failed to initialize SDL!\n");
        return;
    }
    window = SDL_CreateWindow("Simple Emulator",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,640,SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Failed to create window!\n");
        return;
    }
    surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,255,0));
    SDL_Delay(2000);
    display_deinit();
}

void display_deinit()
{
    surface = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("DEBUG: Display deinit: OK!\n");
}

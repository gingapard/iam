#include <SDL2/SDL.h>
#include "constants.h"
#include "globals.h"

void initWindow() {
    window = SDL_CreateWindow(
        "I am", // Title 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0
    );
}

void stop() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void clearScreen() {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
}

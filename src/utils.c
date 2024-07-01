#include <SDL2/SDL.h>

void stop(SDL_Window* window, SDL_Renderer* rend) {
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void clearScreen(SDL_Renderer* rend) {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
}

#include <SDL2/SDL.h>
#include "constants.h"
#include "map.h"

void initMap(Map* map) {
    for (int y = 0; y < GRID_HEIGHT; ++y) { 
        for (int x = 0; x < GRID_WIDTH; ++x) { 
            map->grid[y][x].type = Air;
        }
    }
}

void drawMap(SDL_Renderer* rend, Map* map) {
    for (int y = 0; y < GRID_HEIGHT; ++y) { 
        for (int x = 0; x < GRID_WIDTH; ++x) { 
            if (map->grid[y][x].type == Sand) {
                SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
                SDL_Rect rect = { x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
                SDL_RenderFillRect(rend, &rect);
            }
        }
    }
}

void drawGrid(SDL_Renderer* rend) {
    SDL_SetRenderDrawColor(rend, 100, 100, 100, 255); 

    for (int x = 0; x <= WINDOW_WIDTH; x += GRID_SIZE) {
        SDL_RenderDrawLine(rend, x, 0, x, WINDOW_HEIGHT);
    }

    for (int y = 0; y <= WINDOW_HEIGHT; y += GRID_SIZE) {
        SDL_RenderDrawLine(rend, 0, y, WINDOW_WIDTH, y);
    }
}

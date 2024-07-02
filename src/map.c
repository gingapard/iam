#include <stdlib.h>
#include <SDL2/SDL.h>
#include "constants.h"
#include "map.h"

char* element_cstr[] = {
    "Sand",
    "Water",
    "Rock",
    "Air",
};

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
            switch (map->grid[y][x].type) {
                case Sand:
                    SDL_SetRenderDrawColor(rend, 194, 178, 128, 255);
                    SDL_Rect sand_rect = { x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
                    SDL_RenderFillRect(rend, &sand_rect);
                    break;
                case Water:
                    SDL_SetRenderDrawColor(rend, 64, 164, 223, 128);
                    SDL_Rect water_rect = { x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
                    SDL_RenderFillRect(rend, &water_rect);
                    break;
                case Rock:
                    SDL_SetRenderDrawColor(rend, 120, 120, 120, 255);
                    SDL_Rect rock_rect = { x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE };
                    SDL_RenderFillRect(rend, &rock_rect);
                    break;
                case Air:
                    break;
                default:
                    break;
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

ElementTrait getElementTrait(ElementType element) {
    switch (element) {
        case Sand:
            return Solid;
            break;
        case Water: 
            return Solid;
            break;
        case Rock:
            return Solid;
            break;
        case Air:
            return Empty;
            break;
        default:
            return Empty;
            break;
    }
}

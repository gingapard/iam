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

void moveCell(Cell grid[GRID_WIDTH][GRID_HEIGHT], int x, int y, Direction direc) {

    // is in  bounds
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
        return;
    }

    int new_x = x;
    int new_y= y;
    switch (direc) {
        case Up:
            new_y = y - 1;
            break;
        case Down:
            new_y = y + 1;
            break;
        case Left:
            new_x = x - 1;
            break;
        case Right:
            new_x = x + 1;
            break;
        default:
            return;
    }

    if (new_x < 0 || new_x >= GRID_WIDTH || new_y < 0 || new_y >= GRID_HEIGHT) {
        return;
    }

    grid[new_y][new_x] = grid[y][x];
    grid[y][x].type = Air; 
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

#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include "constants.h"

typedef enum {
    Sand,
    Water,
    Air,
} ElementType;

typedef struct {
    ElementType type;
} Cell;

typedef struct {
    Cell grid[GRID_HEIGHT][GRID_WIDTH]; 
} Map;

void initMap(Map* map);
void drawMap(SDL_Renderer* rend, Map* map);
void drawGrid(SDL_Renderer* rend);

#endif

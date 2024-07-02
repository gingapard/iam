#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include "constants.h"

typedef enum {
    Sand,
    Water,
    Rock,
    Air,
} ElementType;

typedef enum {
    Solid,
    Fluid,
    Empty,
} ElementTrait;

extern char* element_cstr[];

typedef struct {
    ElementType type;
} Cell;

typedef struct {
    Cell grid[GRID_HEIGHT][GRID_WIDTH]; 
} Map;

void initMap(Map* map);
void drawMap(SDL_Renderer* rend, Map* map);
void drawGrid(SDL_Renderer* rend);
ElementTrait getElement(ElementType element);

#endif

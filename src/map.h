#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include "constants.h"

extern char* element_cstr[];

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

typedef struct {
    ElementType type;
} Cell;

typedef struct {
    Cell grid[GRID_HEIGHT][GRID_WIDTH]; 
} Map;

void initMap(Map* map);
void drawMap(SDL_Renderer* rend, Map* map);
void drawGrid(SDL_Renderer* rend);
Uint8 hasTrait(ElementType element, ElementTrait trait);

/* Moving */
void downSwap(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x);
void downRightSwap(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x);
void downLeftSwap(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x);
void rightSwap(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x);
void leftSwap(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x);
void moveDownRandom(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x);

#endif

#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include "constants.h"

typedef enum {
    Sand,
    Air,
} CellType;

typedef struct {
    CellType type;
} Cell;

typedef struct {
    Cell grid[GRID_HEIGHT][GRID_WIDTH]; 
} Map;

typedef enum {
    Up,
    Down,
    Left,
    Right,
} Direction;

void initMap(Map* map);
void moveCell(Cell grid[GRID_WIDTH][GRID_HEIGHT], int x, int y, Direction direc);
void drawMap(SDL_Renderer* rend, Map* map);
void drawGrid(SDL_Renderer* rend);

#endif

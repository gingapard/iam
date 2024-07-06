#include <stdlib.h>
#include "../constants.h"
#include "../map.h"

static void moveRandom(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x) {
    if (rand() % 2)
        downRightSwap(grid, y, x);
    else
        downLeftSwap(grid, y, x);
}

void updateSand(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x) {
    if (!(y < GRID_HEIGHT && x < GRID_WIDTH)) {
        return;
    }

    ElementType* xd = &grid[y + 1][x].type;
    ElementType* xr = &grid[y][x + 1].type;
    ElementType* xl = &grid[y][x - 1].type;
    ElementType* xdr = &grid[y + 1][x + 1].type;
    ElementType* xdl = &grid[y + 1][x - 1].type;

    // moving directly down
    if (y + 1 < GRID_HEIGHT && hasTrait(*xd, Empty) || hasTrait(*xd, Fluid)) {
        downSwap(grid, y, x);
        return;
    }
    
    Uint8 canLeft = (x > 0 && (hasTrait(*xl, Empty) && hasTrait(*xdl, Empty)) || hasTrait(*xl, Fluid) && hasTrait(*xdl, Fluid));
    Uint8 canRight = (x < GRID_WIDTH - 1 && (hasTrait(*xr, Empty) && hasTrait(*xdr, Empty)) || hasTrait(*xl, Fluid) && hasTrait(*xdl, Fluid));

    if (canLeft && canRight)
        moveRandom(grid, y, x);
    else if (canRight) 
        downRightSwap(grid, y, x);
    else if (canLeft)
        downLeftSwap(grid, y, x);
}


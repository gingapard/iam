#include <stdlib.h>
#include "../constants.h"
#include "../map.h"

void moveRandom(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x) {
    if (rand() % 2)
        downRightSwap(grid, y, x);
    else 
        downLeftSwap(grid, y, x);
}

void updateSand(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x) {
    // moving directly down
    if (y + 1 < GRID_HEIGHT && hasTrait(grid[y + 1][x].type, Empty)) {
        downSwap(grid, y, x);
        return;
    }
    
    Uint8 canLeft = (x > 0 && hasTrait(grid[y][x - 1].type, Empty) && hasTrait(grid[y + 1][x - 1].type, Empty));
    Uint8 canRight = (x < GRID_WIDTH - 1 && hasTrait(grid[y][x + 1].type, Empty) && hasTrait(grid[y + 1][x + 1].type, Empty));

    if (canLeft && canRight) {
        moveRandom(grid, y, x);
    } else if (canRight) {
        downRightSwap(grid, y, x);
    } else if (canLeft) {
        downLeftSwap(grid, y, x);
    }
}


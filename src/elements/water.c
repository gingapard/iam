#include "../constants.h"
#include "../map.h"

static void moveRandom(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x) {
    if (rand() % 2)
        rightSwap(grid, y, x);
    else
        leftSwap(grid, y, x);
}

/* for some reason, the water biases towards left side */
void updateWater(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x) {
    if (!(y < GRID_HEIGHT && x < GRID_WIDTH)) {
        return;
    }

    ElementType* xd = &grid[y + 1][x].type;
    ElementType* xl = &grid[y][x - 1].type;
    ElementType* xr = &grid[y][x + 1].type;

    // moving directly down
    if (y + 1 < GRID_HEIGHT && hasTrait(*xd, Empty)) {
        downSwap(grid, y, x);
        return;
    }

    Uint8 canLeft = (x > 0 && hasTrait(*xl, Empty));
    Uint8 canRight = (x < GRID_WIDTH - 1 && hasTrait(*xr, Empty));

    if (canLeft && canRight) {
        moveRandom(grid, y, x);
    } else if (canRight) {
        rightSwap(grid, y, x);
    } else if (canLeft) {
        leftSwap(grid, y, x);
    }
}


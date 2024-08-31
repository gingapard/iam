#include "../constants.h"
#include "../globals.h"
#include "../map.h"

static void moveRandom(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x) {
    int weight = rand() % 2;

    if (weight) {
        rightSwap(grid, y, x);
        right_weight++;
    }
    else {
        leftSwap(grid, y, x);
        left_weight++;
    }

    printf("left: %d\nright: %d", left_weight, right_weight);
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


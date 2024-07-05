#include <stdlib.h>
#include "../constants.h"
#include "../map.h"

void updateSand(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x) {

    // Checking if sand can move one down
    if (y + 1 < GRID_HEIGHT && hasTrait(grid[y + 1][x].type, Empty)) {
        downSwap(grid, y, x);
    } else {

        // If both left and right is free, it will pick a random direction
        if (x > 0
            && hasTrait(grid[y][x - 1].type, Empty) 
            && hasTrait(grid[y + 1][x - 1].type, Empty)
            && x < GRID_WIDTH - 1
            && hasTrait(grid[y][x + 1].type, Empty)
            && hasTrait(grid[y + 1][x + 1].type, Empty)
        ) {
            if (rand() % 2) {
                downRightSwap(grid, y, x);
            }
            else {
                downLeftSwap(grid, y, x);
            }
        }

        // Else if just one direction is free, it will take that
        else if (x > 0 && hasTrait(grid[y][x - 1].type, Empty) && hasTrait(grid[y + 1][x - 1].type, Empty)) {
            grid[y + 1][x - 1] = grid[y][x];
            grid[y][x].type = Air;
        } else if (x < GRID_WIDTH - 1 && hasTrait(grid[y][x + 1].type, Empty) && hasTrait(grid[y + 1][x + 1].type, Empty)) {
            grid[y + 1][x + 1] = grid[y][x];
            grid[y][x].type = Air;
        }
    }
}

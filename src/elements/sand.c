#include <stdlib.h>
#include "../constants.h"
#include "../map.h"

void updateSand(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x) {
    // Checking if sand can move one down
    if (y + 1 < GRID_HEIGHT && grid[y + 1][x].type == Air) {
        grid[y + 1][x] = grid[y][x];
        grid[y][x].type = Air;
    } else if (grid[y][x].type == Sand) {

        // If both left and right is free, it will pick a random direction
        if (x > 0 && grid[y][x - 1].type == Air && grid[y + 1][x - 1].type == Air && x < GRID_WIDTH - 1 && grid[y][x + 1].type == Air && grid[y + 1][x + 1].type == Air) {
            if (rand() % 2) {
                grid[y + 1][x - 1] = grid[y][x];
                grid[y][x].type = Air;
            }
            else {
                grid[y + 1][x + 1] = grid[y][x];
                grid[y][x].type = Air;
            }
        }

        // Else if just one direction is free, it will take that
        else if (x > 0 && grid[y][x - 1].type == Air && grid[y + 1][x - 1].type == Air) {
            grid[y + 1][x - 1] = grid[y][x];
            grid[y][x].type = Air;
        } else if (x < GRID_WIDTH - 1 && grid[y][x + 1].type == Air && grid[y + 1][x + 1].type == Air) {
            grid[y + 1][x + 1] = grid[y][x];
            grid[y][x].type = Air;
        }
    }
}

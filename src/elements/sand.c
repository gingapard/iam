#include <stdlib.h>
#include "../constants.h"
#include "../map.h"

void updateSand(Cell grid[GRID_HEIGHT][GRID_WIDTH], int y, int x) {
    if (y + 1 < GRID_HEIGHT && grid[y + 1][x].type == Air) {
        grid[y + 1][x] = grid[y][x];
        grid[y][x].type = Air;
    } else if (grid[y][x].type == Sand) {
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
        // Check if sand can accumilate
        else if (x > 0 && grid[y][x - 1].type == Air && grid[y + 1][x - 1].type == Air) {
            grid[y + 1][x - 1] = grid[y][x];
            grid[y][x].type = Air;
        } else if (x < GRID_WIDTH - 1 && grid[y][x + 1].type == Air && grid[y + 1][x + 1].type == Air) {
            grid[y + 1][x + 1] = grid[y][x];
            grid[y][x].type = Air;
        }
    }
}

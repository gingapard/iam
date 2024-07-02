#include "../constants.h"
#include "../map.h"

void updateRock(Cell grid[GRID_HEIGHT][GRID_WIDTH], int x, int y) {
    if (y + 1 < GRID_HEIGHT && grid[y + 1][x].type == Air) {
        grid[y + 1][x] = grid[y][x];
        grid[y][x].type = Air;
    }
}

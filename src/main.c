#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>

#include "window.h"
#include "globals.h"
#include "constants.h"
#include "map.h"
#include "hud.h"
#include "elements/sand.h"
#include "elements/water.h"

/* Common Global Variables (globals.h) */
Uint8 should_close = 0; 
Uint8 element_type = Sand;
float current_fps = 0.0;

/* SDL Variables */
SDL_Window* window = NULL;
SDL_Renderer* rend = NULL;
TTF_Font* font = NULL;

void update(Map* map) {
    // for temp
    Cell temp_grid[GRID_HEIGHT][GRID_WIDTH];
    memcpy(temp_grid, map->grid, sizeof(map->grid));

    for (int y = GRID_HEIGHT - 2; y >= 0; --y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            switch (temp_grid[y][x].type) {
                case Sand:
                    update_sand(temp_grid, y, x);
                    break;
                case Water: 
                    update_water(temp_grid, y, x);
                case Air:
                    break;
                default:
                    break;
            }
        }
    }

    // copy back to map->grid
    memcpy(map->grid, temp_grid, sizeof(map->grid));
}

void handleInput(SDL_Event event, Map* map) {
    while (SDL_PollEvent(&event)) {

        /* Handle input */
        switch (event.type) {
            case SDL_QUIT:
                should_close = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int click_x = event.button.x / GRID_SIZE;
                    int click_y = event.button.y / GRID_SIZE;
                    
                    if (click_x >= 0 && click_x < GRID_WIDTH && click_y >= 0 && click_y < GRID_HEIGHT) {
                        map->grid[click_y][click_x].type = element_type;
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    int click_x = event.button.x / GRID_SIZE;
                    int click_y = event.button.y / GRID_SIZE;
                    
                    if (click_x >= 0 && click_x < GRID_WIDTH && click_y >= 0 && click_y < GRID_HEIGHT) {
                        map->grid[click_y][click_x].type = Air;
                    }
                }
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0) {
                    if (element_type != 2)
                        ++element_type;
                    else
                        element_type = 0;
                }
                else if (event.wheel.y < 0) {
                    if (element_type != 0)
                        --element_type;
                    else
                        element_type = 2;
                }
                break;
            default:
                break;
        }
    }
}

int main(void) {

    Uint32 frame_start;
    Uint32 frame_time;
    SDL_Event event;
    Map map;

    SDL_Init(SDL_INIT_VIDEO);
    initWindow();
    TTF_Init();
    initMap(&map);

    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    font = TTF_OpenFont("assets/main.ttf", 12);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 1;
    }

    while (!should_close) {
        frame_start = SDL_GetTicks();
        clearScreen(rend);

        handleInput(event, &map);
        update(&map);
        drawMap(rend, &map);
        renderHud();
        // drawGrid(rend);
        SDL_RenderPresent(rend);

        frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frame_time);
        }

        current_fps = 1000.0 / (frame_time + (FRAME_DELAY - frame_time));
        printf("fps: %f\n", current_fps);
    }

    stop(window, rend, font);
    return 0;
}

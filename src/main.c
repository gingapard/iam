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
#include "elements/rock.h"

/* Common Global Variables (globals.h) */
Uint8 should_close = 0; 
Uint8 element_type = Sand;
float current_fps = 0.0;
Uint8 mouse_left_held = 0;
Uint8 mouse_right_held = 0;

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
                    updateSand(temp_grid, y, x);
                    break;
                case Water: 
                    updateWater(temp_grid, y, x);
                    break;
                case Rock:
                    updateRock(temp_grid, y, x);
                    break;
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
                    mouse_left_held = 1;
                    int click_x = event.button.x / GRID_SIZE;
                   int click_y = event.button.y / GRID_SIZE;
                    
                    if (click_x >= 0 && click_x < GRID_WIDTH && click_y >= 0 && click_y < GRID_HEIGHT) {
                        map->grid[click_y][click_x].type = element_type;
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    mouse_right_held = 1;
                    int click_x = event.button.x / GRID_SIZE;
                    int click_y = event.button.y / GRID_SIZE;
                    
                    if (click_x >= 0 && click_x < GRID_WIDTH && click_y >= 0 && click_y < GRID_HEIGHT) {
                        map->grid[click_y][click_x].type = Air;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    mouse_left_held = 0;
                else mouse_right_held = 0;
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0) {
                    if (element_type != (ELEMENT_N - 2))
                        ++element_type;
                    else
                        element_type = 0;
                }
                else if (event.wheel.y < 0) {
                    if (element_type != 0)
                        --element_type;
                    else
                        element_type = ELEMENT_N - 2;
                }
                break;
            default:
                break;
        }
    }

    int mouse_x;
    int mouse_y;
    (void)SDL_GetMouseState(&mouse_x, &mouse_y);
    int grid_x = mouse_x / GRID_SIZE;
    int grid_y = mouse_y / GRID_SIZE;

    if (mouse_left_held) {
        if (grid_x >= 0 && grid_x < GRID_WIDTH && grid_y >= 0 && grid_y < GRID_HEIGHT) {
            map->grid[grid_y][grid_x].type = element_type;
        }
    }
    if (mouse_right_held) {
        if (grid_x >= 0 && grid_x < GRID_WIDTH && grid_y >= 0 && grid_y < GRID_HEIGHT) {
            map->grid[grid_y][grid_x].type = Air;
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

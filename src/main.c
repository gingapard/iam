#include <stdio.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "constants.h"
#include "map.h"

Uint8 should_close = 0; 

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
                        map->grid[click_y][click_x].type = Sand;
                    }
                }
            default:
                break;
        }
    }
}

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("I am",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;

    Map map;
    initMap(&map);

    Uint32 frame_start;
    Uint32 frame_time;

    while (!should_close) {
        frame_start = SDL_GetTicks();
        clearScreen(rend);

        handleInput(event, &map);
        // TODO: update();
        drawMap(rend, &map);
        // drawGrid(rend);
        SDL_RenderPresent(rend);

        frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frame_time);
        }

        printf("fps: %f\n", 1000.0 / (frame_time + (FRAME_DELAY - frame_time)));

    }

    stop(window, rend);
    return 0;
}


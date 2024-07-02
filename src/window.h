#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void initWindow();
void stop(SDL_Window* window, SDL_Renderer* rend, TTF_Font* font);
void clearScreen(SDL_Renderer* rend);

#endif

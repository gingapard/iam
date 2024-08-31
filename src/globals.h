#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern Uint8 should_close;
extern Uint8 element_type;
extern float current_fps;
extern Uint8 mouse_left_held;
extern Uint8 mouse_right_held;

extern TTF_Font* font;
extern SDL_Renderer* rend;
extern SDL_Window* window;

extern int right_weight;
extern int left_weight;

#endif

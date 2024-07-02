#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "globals.h"
#include "text.h"
#include "map.h"

void renderElementType() {
    SDL_Color textColor = {255, 255, 255};
    renderText(element_cstr[element_type], 10, 25, textColor);
}

void renderFrameRate() {
    SDL_Color textColor = {255, 255, 255};
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%.1f", current_fps);
    renderText(buffer, 10, 10, textColor);
}

void renderHud() {
    renderFrameRate();
    renderElementType();
}

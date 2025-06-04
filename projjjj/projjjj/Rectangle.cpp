
#include "Rectangle.h"

void DrawRect(SDL_Renderer* renderer, int cx, int cy, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { cx - w / 2, cy - h / 2, w, h };
    SDL_RenderDrawRect(renderer, &rect);
}

bool PointInRect(const SDL_Rect& rect, int px, int py) {
    return px >= rect.x && px <= rect.x + rect.w && py >= rect.y && py <= rect.y + rect.h;
}
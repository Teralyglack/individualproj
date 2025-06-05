#include "Ellipse.h"

void DrawEllipse(SDL_Renderer* renderer, int cx, int cy, int rx, int ry, SDL_Color color) {
    color = { 0, 255, 0, 255 };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = -rx; w <= rx; w++) {
        int h = (int)(ry * sqrt(1.0 - (double)(w * w) / (rx * rx)));
        SDL_RenderDrawPoint(renderer, cx + w, cy + h);
        SDL_RenderDrawPoint(renderer, cx + w, cy - h);
    }
}

bool PointInEllipse(int cx, int cy, int rx, int ry, int px, int py) {
    double normX = (double)(px - cx) / rx;
    double normY = (double)(py - cy) / ry;
    return (normX * normX + normY * normY) <= 1.0;
}
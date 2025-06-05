#include "Actor.h"

void DrawCircle(SDL_Renderer* renderer, int cx, int cy, int r, SDL_Color color) {
    color = { 128, 0, 128, 255 };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = -r; w <= r; w++) {
        for (int h = -r; h <= r; h++) {
            if (w * w + h * h <= r * r)
                SDL_RenderDrawPoint(renderer, cx + w, cy + h);
        }
    }
}

void DrawActor(SDL_Renderer* renderer, int cx, int cy) {
    // Рисуем голову
    DrawCircle(renderer, cx, cy - 30, 15, { 0, 0, 0, 255 });
    // Рисуем тело
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, cx, cy - 15, cx, cy + 40); // Тело
    SDL_RenderDrawLine(renderer, cx, cy, cx - 30, cy + 10); // Левая рука
    SDL_RenderDrawLine(renderer, cx, cy, cx + 30, cy + 10); // Правая рука
    SDL_RenderDrawLine(renderer, cx, cy + 40, cx - 25, cy + 70); // Левая нога
    SDL_RenderDrawLine(renderer, cx, cy + 40, cx + 25, cy + 70); // Правая нога
}

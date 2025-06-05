#include "Triangle.h"


void DrawTriangle(SDL_Renderer* renderer, int cx, int cy, int size, SDL_Color color) {
    color = { 0, 0, 255, 255 };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Point points[4] = {
        { cx, cy - size / 2 },
        { cx - size / 2, cy + size / 2 },
        { cx + size / 2, cy + size / 2 },
        { cx, cy - size / 2 }
    };
    SDL_RenderDrawLines(renderer, points, 4);
}

// Определяем точку внутри треугольника по барицентрическим координатам
bool PointInTriangle(SDL_Point pt, SDL_Point v1, SDL_Point v2, SDL_Point v3) {
    double dX = pt.x - v3.x;
    double dY = pt.y - v3.y;
    double dX21 = v3.x - v2.x;
    double dY12 = v2.y - v3.y;
    double D = dY12 * (v1.x - v3.x) + dX21 * (v1.y - v3.y);
    double s = dY12 * dX + dX21 * dY;
    double t = (v3.y - v1.y) * dX + (v1.x - v3.x) * dY;

    if (D < 0) return s <= 0 && t <= 0 && s + t >= D;
    return s >= 0 && t >= 0 && s + t <= D;
}

#include <SDL.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "Actor.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "primitive.h"

struct Primitive {
    enum Type { Actor, Ellipse, Rectangle, Triangle } type;
    int x, y;           // Центр
    int width, height;  // Размеры
    bool selected = false;

    SDL_Rect getRect() const {
        return { x - width / 2, y - height / 2, width, height };
    }

    // Проверка попадания по примитиву
    bool IsPointInside(int px, int py) const;
};

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Кликабельные графические примитивы", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600, SDL_WINDOW_SHOWN);
    if (!win) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(win);
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::vector<Primitive> primitives = {
        { Primitive::Actor, 100, 150, 60, 100 },
        { Primitive::Ellipse, 350, 150, 120, 60 },
        { Primitive::Rectangle, 600, 150, 100, 80 },
        { Primitive::Triangle, 850, 150, 100, 100 },
    };

    bool dragging = false;
    int draggedIndex = -1;
    int dragOffsetX = 0, dragOffsetY = 0;

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN: {
                int mx = e.button.x;
                int my = e.button.y;

                for (int i = 0; i < primitives.size(); ++i) {
                    if (primitives[i].IsPointInside(mx, my)) {
                        dragging = true;
                        draggedIndex = i;
                        dragOffsetX = mx - primitives[i].x;
                        dragOffsetY = my - primitives[i].y;
                        primitives[i].selected = true;
                        break;
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
                dragging = false;
                if (draggedIndex != -1) {
                    primitives[draggedIndex].selected = false;
                    draggedIndex = -1;
                }
                break;
            case SDL_MOUSEMOTION:
                if (dragging && draggedIndex != -1) {
                    primitives[draggedIndex].x = e.motion.x - dragOffsetX;
                    primitives[draggedIndex].y = e.motion.y - dragOffsetY;
                }
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (const auto& prim : primitives) {
            switch (prim.type) {
            case Primitive::Actor:
                DrawActor(renderer, prim.x, prim.y);
                break;
            case Primitive::Ellipse:
                DrawEllipse(renderer, prim.x, prim.y, prim.width / 2, prim.height / 2, { 0, 0, 0, 255 });
                break;
            case Primitive::Rectangle:
                DrawRect(renderer, prim.x, prim.y, prim.width, prim.height, { 0, 0, 0, 255 });
                break;
            case Primitive::Triangle:
                DrawTriangle(renderer, prim.x, prim.y, prim.width, { 0, 0, 0, 255 });
                break;
            }
        }


        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}


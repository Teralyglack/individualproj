#include <SDL.h>
#include <iostream>
#include <cmath>

// Функция для рисования кружка (голова актера)
void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // Расстояние по x от центра
            int dy = radius - h; // Расстояние по y от центра
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

// Рисуем актера (человечка)
void DrawActor(SDL_Renderer* renderer, int x, int y)
{
    SDL_Color black = { 0, 0, 0, 255 };

    // Голова
    DrawCircle(renderer, x, y, 20, black);

    // Туловище
    SDL_RenderDrawLine(renderer, x, y + 20, x, y + 80);

    // Руки
    SDL_RenderDrawLine(renderer, x, y + 40, x - 30, y + 60);
    SDL_RenderDrawLine(renderer, x, y + 40, x + 30, y + 60);

    // Ноги
    SDL_RenderDrawLine(renderer, x, y + 80, x - 20, y + 120);
    SDL_RenderDrawLine(renderer, x, y + 80, x + 20, y + 120);
}

// Рисуем овал (вариант использования)
void DrawEllipse(SDL_Renderer* renderer, int centerX, int centerY, int radiusX, int radiusY, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int w = -radiusX; w <= radiusX; w++)
    {
        int h = (int)(radiusY * sqrt(1 - (double)(w * w) / (radiusX * radiusX)));
        SDL_RenderDrawPoint(renderer, centerX + w, centerY + h);
        SDL_RenderDrawPoint(renderer, centerX + w, centerY - h);
    }
}


void DrawArrowLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Рисуем основную линию
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    // Вычисляем угол линии
    double angle = std::atan2(y2 - y1, x2 - x1);
    const int arrowLen = 10;
    const double arrowAngle = M_PI / 6; // 30 градусов

    // Левая линия стрелки
    int ax1 = x2 - static_cast<int>(arrowLen * std::cos(angle - arrowAngle));
    int ay1 = y2 - static_cast<int>(arrowLen * std::sin(angle - arrowAngle));

    // Правая линия стрелки
    int ax2 = x2 - static_cast<int>(arrowLen * std::cos(angle + arrowAngle));
    int ay2 = y2 - static_cast<int>(arrowLen * std::sin(angle + arrowAngle));

    // Рисуем "ножки" стрелки
    SDL_RenderDrawLine(renderer, x2, y2, ax1, ay1);
    SDL_RenderDrawLine(renderer, x2, y2, ax2, ay2);
}



// Рисуем стрелку на концах лини

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("UML Примитивы", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Ошибка создания окна: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Ошибка создания рендерера: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Очищаем экран белым цветом
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Color black = { 0, 0, 0, 255 };

        // Рисуем актера
        DrawActor(renderer, 100, 100);

        // Рисуем овал (вариант использования)
        DrawEllipse(renderer, 300, 120, 100, 50, black);

        DrawArrowLine(renderer, 100, 300, 400, 300, black);
      

        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // Около 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}


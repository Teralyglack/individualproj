#include "primitive.h"



// Структура для хранения примитива
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


bool Primitive::IsPointInside(int px, int py) const {
    switch (type) {
    case Actor:
        // Проверка по прямоугольнику, который охватывает актера
        return PointInRect(getRect(), px, py);
    case Ellipse:
        return PointInEllipse(x, y, width / 2, height / 2, px, py);
    case Rectangle:
        return PointInRect(getRect(), px, py);
    case Triangle: {
        SDL_Point v1 = { x, y - height / 2 };
        SDL_Point v2 = { x - width / 2, y + height / 2 };
        SDL_Point v3 = { x + width / 2, y + height / 2 };
        return PointInTriangle({ px, py }, v1, v2, v3);
    }
    default:
        return false;
    }
}
#pragma once
#include <SDL.h>
#include <cmath>
#include <vector>
#include <iostream>

void DrawRect(SDL_Renderer* renderer, int cx, int cy, int w, int h, SDL_Color color);

bool PointInRect(const SDL_Rect& rect, int px, int py);
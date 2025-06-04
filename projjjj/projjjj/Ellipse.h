#pragma once
#include <SDL.h>
#include <cmath>
#include <vector>
#include <iostream>

void DrawEllipse(SDL_Renderer* renderer, int cx, int cy, int rx, int ry, SDL_Color color);
bool PointInEllipse(int cx, int cy, int rx, int ry, int px, int py);
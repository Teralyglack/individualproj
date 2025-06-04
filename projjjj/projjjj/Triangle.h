#pragma once
#include <SDL.h>
#include <cmath>
#include <vector>
#include <iostream>

void DrawTriangle(SDL_Renderer* renderer, int cx, int cy, int size, SDL_Color color);

bool PointInTriangle(SDL_Point pt, SDL_Point v1, SDL_Point v2, SDL_Point v3);

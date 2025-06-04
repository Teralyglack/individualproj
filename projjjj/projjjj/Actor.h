#pragma once
#include <SDL.h>
#include <cmath>
#include <vector>
#include <iostream>

void DrawCircle(SDL_Renderer* renderer, int cx, int cy, int r, SDL_Color color);

void DrawActor(SDL_Renderer* renderer, int cx, int cy);
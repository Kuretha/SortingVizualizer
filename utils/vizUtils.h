 //
// Created by tf_no on 2/24/2024.
//
#include "SDL.h"
#include <vector>

#ifndef UNTITLED_VIZUTILS_H
#define UNTITLED_VIZUTILS_H


bool init(SDL_Window*& window, SDL_Renderer*& renderer);
void renderBars(SDL_Renderer* renderer, const std::vector<int>& array);
void renderBarsTimSort(SDL_Renderer* renderer, const std::vector<int>& array, int left, int right, int mergedIndex);
void swapAndRender(std::vector<int>& array, int i, int j, SDL_Renderer* renderer);


#endif //UNTITLED_VIZUTILS_H

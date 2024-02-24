//
// Created by tf_no on 2/24/2024.
//

#include "vizUtils.h"
#include <SDL.h>
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>

// Constants for screen dimensions and array size
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int ARRAY_SIZE = 800;
const int BAR_WIDTH = SCREEN_WIDTH / ARRAY_SIZE;


//// Init SDL and create window
//bool init(SDL_Window*& window, SDL_Renderer*& renderer);
//
//// Draw bars for the array representation
//void renderBars(SDL_Renderer* renderer, const std::vector<int>& array);
//
//// Function to swap two elements in the array and update the visualization
//void swapAndRender(std::vector<int>& array, int i, int j, SDL_Renderer* renderer);

bool init(SDL_Window*& window, SDL_Renderer*& renderer) {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed. SDL Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create window
    window = SDL_CreateWindow("Sorting Algorithm Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window creation failed. SDL Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Renderer creation failed. SDL Error: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
}

// render bar function for general sort function
void renderBars(SDL_Renderer* renderer, const std::vector<int>& array, int currentIndex, int comparingIndex) {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw bars for each element in the array
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        SDL_Rect bar = {i * BAR_WIDTH, SCREEN_HEIGHT - array[i], BAR_WIDTH, array[i]};

        // differentiator between currently processed bar and no
        if (i == currentIndex) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        } else if (i == comparingIndex) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green for comparing
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        SDL_RenderFillRect(renderer, &bar);
    }
    // render the bar
    SDL_RenderPresent(renderer);
}

// render bar function for TimSort, because it TimSort works a bit different
void renderBarsTimSort(SDL_Renderer* renderer, const std::vector<int>& array, int left, int right, int mergedIndex) {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw bars for each element in the array
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        SDL_Rect bar = {i * BAR_WIDTH, SCREEN_HEIGHT - array[i], BAR_WIDTH, array[i]};

        // Highlight the elements in the current segment that are  being merged
        if (i >= left && i <= right) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red for the current segment
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        // Highlight the merged element
        if (i == mergedIndex) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green for the merged element
        }

        SDL_RenderFillRect(renderer, &bar);
    }

    SDL_RenderPresent(renderer);
}

void swapAndRender(std::vector<int>& array, int i, int j, SDL_Renderer* renderer) {
    // Swap elements in the array
    std::swap(array[i], array[j]);
    // Render the updated array
    renderBars(renderer, array, i, j);
    // Delay for a short time to visualize the sorting step
    SDL_Delay(5);
}

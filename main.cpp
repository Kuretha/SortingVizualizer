#include <SDL.h>
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include "utils/vizUtils.h"
#include "algos/timSort.h"


const int ARRAY_SIZE = 800;

// Sorting algorithms for testing
void bubbleSort(std::vector<int>& array, SDL_Renderer* renderer);
void selectionSort(std::vector<int>& array, SDL_Renderer* renderer);


int main(int argc, char* argv[]) {
    // SDL components
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!init(window, renderer)) {
        std::cerr << "SDL initialization failed.\n";
        return 1;
    }

    // initialization to generate random vector ~prolly this can be changed or deleted, this is only for testing~
    std::random_device rd;
    std::uniform_int_distribution<> d(1, ARRAY_SIZE);
    std::vector<int> v;
    // Generate random numbers vector
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
      v.push_back(d(rd));
    }

    // Uncomment the sorting algorithm you want to visualize, add new sorting in here
//    bubbleSort(v, renderer);
    selectionSort(v, renderer);
//    timSort(v, renderer);

    SDL_Delay(3000);  // Pause for a moment before closing the window

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void bubbleSort(std::vector<int>& array, SDL_Renderer* renderer) {
    int n = ARRAY_SIZE;
    bool swapped;
    do {
        swapped = false;
        for (int i = 1; i < n; ++i) {
            if (array[i - 1] > array[i]) {
                swapAndRender(array, i - 1, i, renderer);
                swapped = true;
            }
        }
        --n;
    } while (swapped);
}

void selectionSort(std::vector<int>& array, SDL_Renderer* renderer) {
    int n = ARRAY_SIZE;
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        swapAndRender(array, i, minIndex, renderer);
    }
}

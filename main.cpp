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


// Init SDL and create window
bool init(SDL_Window*& window, SDL_Renderer*& renderer);

// Draw bars for the array representation
void renderBars(SDL_Renderer* renderer, const std::vector<int>& array);

// Function to swap two elements in the array and update the visualization
void swapAndRender(std::vector<int>& array, int i, int j, SDL_Renderer* renderer);

// Sorting algorithms for testing
void bubbleSort(std::vector<int>& array, SDL_Renderer* renderer);
void selectionSort(std::vector<int>& array, SDL_Renderer* renderer);
void timSort(std::vector<int>& array, SDL_Renderer* renderer);


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
//    selectionSort(v, renderer);
    timSort(v, renderer);

    SDL_Delay(3000);  // Pause for a moment before closing the window

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

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

// part of timsort
void merge(std::vector<int>& array, int left, int middle, int right, SDL_Renderer* renderer) {
    // Sizes of two subarrays to be merged
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    // Copy data to temporary arrays leftArray[] and rightArray[]
    for (int i = 0; i < n1; ++i) {
        leftArray[i] = array[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        rightArray[j] = array[middle + 1 + j];
    }

    // Merge the temporary arrays back into array[left...right]
    int i = 0;  // 1st subarray
    int j = 0;  // 2nd subarray
    int k = left;  // merged subarray

    while (i < n1 && j < n2) {
        // Highlight the elements being compared during merging
        renderBarsTimSort(renderer, array, left, right, k);
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            ++i;
        } else {
            array[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements of leftArray[], if there are any
    while (i < n1) {
        array[k] = leftArray[i];
        ++i;
        ++k;
        // Highlight the remaining elements
        renderBarsTimSort(renderer, array, left, right, k - 1);
    }

    // Copy the remaining elements of rightArray[], if there are any
    while (j < n2) {
        array[k] = rightArray[j];
        ++j;
        ++k;
        // Highlight the remaining elements
        renderBarsTimSort(renderer, array, left, right, k - 1);
    }
    // Render the final state after merging
    renderBarsTimSort(renderer, array, left, right, k - 1);
    SDL_Delay(10);  // Adjust delay for visualization
}

// part of timsort also
void mergeSort(std::vector<int>& array, int left, int right, SDL_Renderer* renderer) {
    if (left < right) {
        // Same logic as before for dividing the array and recursively sorting
        int middle = left + (right - left) / 2;

        mergeSort(array, left, middle, renderer);
        mergeSort(array, middle + 1, right, renderer);

        // Merge the sorted subarrays
        merge(array, left, middle, right, renderer);

    }
}

// TimSort
void timSort(std::vector<int>& array, SDL_Renderer* renderer) {
    mergeSort(array, 0, array.size() - 1, renderer);
}



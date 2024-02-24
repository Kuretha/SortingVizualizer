//
// Created by tf_no on 2/24/2024.
//

#include "timSort.h"
#include <vector>
#include "utils/vizUtils.h" // call the viz here


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
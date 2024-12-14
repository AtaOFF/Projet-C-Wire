#include <stdio.h>
#include <stdlib.h>
#include "common.h"


void quick_sort_by_capacity(StationResult **results, int low, int high) {
    if (low < high) {
        long long pivot = results[high]->capacity;  // Pivot is the element at index `high`
        int i = low - 1;  // Tracks the boundary for elements smaller than the pivot

        // Partition the array
        for (int j = low; j < high; j++) {
            if (results[j]->capacity < pivot) {
                i++;  
                // Swap the elements
                StationResult *temp = results[i];
                results[i] = results[j];
                results[j] = temp;
            }
        }

        // Swap the pivot into its correct position
        StationResult *temp = results[i + 1];
        results[i + 1] = results[high];
        results[high] = temp;

        int pi = i + 1;  // New pivot position

        // Recursively sort the subarrays to the left and right of the pivot
        quick_sort_by_capacity(results, low, pi - 1);  // Sort left of the pivot
        quick_sort_by_capacity(results, pi + 1, high); // Sort right of the pivot
    }
}


// Sorts an array of StationResult structures by capacity in a separate thread using quicksort.
void* sort_by_capacity_thread(void* arg) {
    StationResult **results = (StationResult**)arg;
    int count = sizeof(results) / sizeof(results[0]);  // Calculate the number of elements
    quick_sort_by_capacity(results, 0, count - 1);
    return NULL;
}
 
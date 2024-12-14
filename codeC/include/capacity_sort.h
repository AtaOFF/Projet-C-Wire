#ifndef CAPACITY_SORT_H
#define CAPACITY_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/**
 * @brief Sorts an array of StationResult structures by their capacity using the quicksort algorithm.
 *
 * This function performs a quicksort on an array of StationResult pointers, partitioning
 * the array based on the capacity of each StationResult. It recursively sorts the subarrays
 * to the left and right of the pivot element.
 *
 * @param results The array of StationResult pointers to be sorted.
 * @param low The starting index of the array to be sorted.
 * @param high The ending index of the array to be sorted.
 */
void quick_sort_by_capacity(StationResult **results, int low, int high);

/**
 * @brief Sorts an array of StationResult structures by capacity in a separate thread using quicksort.
 *
 * This function is executed in a thread to sort the array of StationResult structures
 * by their capacity. It receives the array of results, calculates the number of elements,
 * and then calls quick_sort_by_capacity to perform the sorting.
 *
 * @param arg The array of StationResult pointers to be sorted (passed as void pointer).
 * @return NULL This is required for thread functions in C.
 */
void* sort_by_capacity_thread(void* arg);

#endif // CAPACITY_SORT_H


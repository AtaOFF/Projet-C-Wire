#ifndef AVL_TO_CSV_H
#define AVL_TO_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"
#include "tree.h"

// Constants for maximum and minimum LV stations to write
#define FIRST_MAX 10
#define LAST_MIN 10

// Structure for AVL Station Result
typedef struct StationResult {
    int id;                  // Station ID
    long long capacity;      // Station capacity
    long long load;          // Station load
} StationResult;

// Structure for passing AVL tree data to threads
typedef struct AVLData {
    Station *root;           // Root of the AVL tree
    StationResult **results; // Array to store results
    int *count;              // Count of results
} AVLData;

// Function declarations
void collectAVLData(Station *a, StationResult **results, int *index);
void writeCSV(const char *filename, const char *header, StationResult **results, int count);
void* collectAndSortData(void* arg);
void transferToCSV(Station *a, const char *filename, const char *header);
long long calculate_diff(StationResult *station);
int compare_by_diff(const void *a, const void *b);
void output_min_max_LV(char *filename, StationResult **results, int count);

#endif // AVL_TO_CSV_H

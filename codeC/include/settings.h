#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// Constants for maximum and minimum LV stations to write
#define FIRST_MAX 10
#define LAST_MIN 10

typedef struct Station {
    struct Station* leftSon;    
    struct Station* rightSon;  
    int balance;   
    int id;      
    long load;          
    long capacity;           
} Station;

int min(int a, int b);
int min3(int a, int b, int c);
int max(int a, int b);
int max3(int a, int b, int c);
Station * createNode();
Station * createStation(long capacity, int id);


int getHeight(Station* a);
int getBalance(Station* a);
Station* rotateLeft(Station* a);
Station* rotateRight(Station* a);
Station* doublerotationLeft(Station* a);
Station* doublerotationRight(Station* a);
Station* balance(Station* a, int id);
Station* insertStation(Station* a, int id, long capacity,  int* h);
Station* updateStation(Station * a, int id, long load);

// Structure to store station results
typedef struct {
    int id;          
    long capacity;   
    long load;      
} StationResult;

// Function to collect AVL data into an array (in avl_to_csv.c)
void collectAVLData(Station *a, StationResult **results, int *index);

// Declaration of the sorting function (in capacity_sort.c)
void qsort_by_capacity(StationResult **results, int count);

// Constants for handling the min/max stations
#define FIRST_MAX 10
#define LAST_MIN 10

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

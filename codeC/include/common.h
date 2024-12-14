#ifndef COMMON_H
#define COMMON_H


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

#endif

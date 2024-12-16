#include "settings.h"


// Function to collect AVL data into an array (in-order traversal)
void collectAVLData(Station *a, StationResult **results, int *index) {
    if (a != NULL) {
        collectAVLData(a->leftSon, results, index); 
        results[*index] = malloc(sizeof(StationResult)); 
        results[*index]->id = a->id;
        results[*index]->capacity = a->capacity;
        results[*index]->load = a->load;
        (*index)++;  
        collectAVLData(a->rightSon, results, index); 
    }
}

// Function to write data to CSV file
void writeCSV(const char *filename, const char *header, StationResult **results, int count) {
    FILE *file = fopen(filename, "w+");
    if (file == NULL) {
        printf("Unable to open file\n");
        exit(4);
    }

    // Write header to the CSV file
    fprintf(file, "%s\n", header);

    // Write each result to the file
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d:%ld:%ld\n", results[i]->id, results[i]->capacity, results[i]->load);
    }

    fclose(file);
}

// Function to collect data and then sort it using a separate thread
void* collectAndSortData(void* arg) {
    AVLData *data = (AVLData*)arg;

    // Collect data from the AVL tree into the results array
    collectAVLData(data->root, data->results, data->count);
    
    // Sort the data by capacity using the quicksort function
    quick_sort_by_capacity(data->results, 0, *data->count - 1);
    
    return NULL;
}

// Function to transfer the data from AVL tree to a CSV file
void transferToCSV(Station *a, const char *filename, const char *header) {
    // Step 1: Dynamically allocate memory to store the results
    int count = 0;
    int max_size = 1000; // Initial array size, can be adjusted
    StationResult **results = malloc(max_size * sizeof(StationResult*)); // Dynamic array allocation

    // Step 2: Prepare the data structure to pass to the thread
    AVLData data = {a, results, &count};
    
    // Step 3: Create a thread to collect and sort the data
    pthread_t thread;
    pthread_create(&thread, NULL, collectAndSortData, (void*)&data);
    
    // Step 4: Wait for the thread to finish (synchronization)
    pthread_join(thread, NULL);
    
    // Step 5: Write the sorted data to the CSV file
    writeCSV(filename, header, results, count);
    
    
    free(results);
}





// Function to calculate the absolute difference between capacity and load
long long calculate_diff(StationResult *station) {
    return abs(station->capacity - station->load);
}

// Comparator for sorting stations by absolute difference (ascending order)
int compare_by_diff(const void *a, const void *b) {
    StationResult *stationA = *(StationResult **)a;
    StationResult *stationB = *(StationResult **)b;

    long long diffA = calculate_diff(stationA);
    long long diffB = calculate_diff(stationB);

    return (diffA > diffB) - (diffA < diffB); // Ascending order
}

// Function to write the 10 most and least loaded LV stations to a CSV file
void output_min_max_LV(char *filename, StationResult **results, int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    fprintf(file, "station_id,capacity,load,absolute_diff\n");

    // Write the 10 most loaded stations
    for (int i = 0; i < FIRST_MAX && i < count; i++) {
        fprintf(file, "%d,%lld,%lld,%lld\n",
                results[i]->id,
                results[i]->capacity,
                results[i]->load,
                calculate_diff(results[i]));
    }

    fprintf(file, "...\n");

    // Write the 10 least loaded stations
    for (int i = count - LAST_MIN; i < count; i++) {
        fprintf(file, "%d,%lld,%lld,%lld\n",
                results[i]->id,
                results[i]->capacity,
                results[i]->load,
                calculate_diff(results[i]));
    }

    fclose(file);
    printf("File %s written successfully.\n", filename);
}

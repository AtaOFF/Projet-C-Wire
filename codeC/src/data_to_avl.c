#include "settings.h"

void processInputToAVL(FILE *inputFile, const char *outputFilename) {
    /* Variables */
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Error creating the output file.\n");
        return;
    }
    fprintf(outputFile, "StationID;Capacity;TotalLoad\n");

    Station *avlTree = NULL; // Root of the AVL tree
    Station *currentNode = NULL; // Node used to search in the AVL tree
    int inputStatus = 0; // Status returned by fscanf
    long stationID, consumerID, capacity, load; // Input data fields
    int heightChange; // Flag for AVL balancing operations

    /* Process input data */
    while ((inputStatus = fscanf(inputFile, "%ld;%ld;%ld;%ld", 
                                 &stationID, &consumerID, &capacity, &load)) == 4) {
        /* If the station does not exist in the tree, insert it */
        if (search(avlTree, stationID, &currentNode) == 0) {
            avlTree = insertStation(avlTree, stationID, capacity, load, &heightChange);
        } 
        /* If the station exists and capacity is provided, update the capacity */
        else if (capacity != 0) {
            currentNode->capacity = capacity;
        } 
        /* If the station exists and load is provided, add to total load */
        else if (load != 0) {
            currentNode->load += load;
        }
    }

    /* Write aggregated data to CSV file */
    Infix(avlTree, outputFile);

    /* Clean up */
    fclose(outputFile);
    deleteTree(avlTree);
}


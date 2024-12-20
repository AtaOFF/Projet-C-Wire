#include "settings.h"

Station* insertStation(Station* a, int id, long capacity, long load, int* h) {
    if (a == NULL) {  /* Create a new station if not found */
        *h = 1;
        a = createStation(id, capacity);
        if (a == NULL) {
            printf("New station creation failed.\n");
            exit(3);
        }
        a->load = load;  /* Initialize load */
    } 
    else if (id < a->id) {  /* Insert into the left subtree */
        a->leftSon = insertStation(a->leftSon, id, capacity, load, h);
        *h = -(*h); 
    } 
    else if (id > a->id) {  /* Insert into the right subtree */
        a->rightSon = insertStation(a->rightSon, id, capacity, load, h);
    } 
    else {  /* If the station already exists, update its load */
        *h = 0;
        a->load += load;  /* Add load to the existing load */
        if (capacity != 0) {
            a->capacity = capacity;  /* Update capacity if provided */
        }
        return a;
    }

    /* Update the balance factor and rebalance */
    if (*h != 0) {
        a->balance += *h;
        a = balance(a, id);
        *h = (a->balance == 0) ? 0 : 1;
    }
    return a;
}



#include <stdio.h>
#include <stdlib.h>

typedef struct Station {
    int id;                // Unique station identifier
    int capacity;          // Station capacity 
    int sum_consumption;   // Sum of consumer consumption
    struct Station* fg;    // Pointer to the left sub tree
    struct Station* fd;    // Pointer to the right sub tree
    int eq;                // balance tree
    int height;            // Tree height
} Station;

int min(int a, int b){
    return(a<b) ? a : b;
}

int min3(int a, int b, int c){
    return min(a, min(b,c));
}

int max(int a, int b){
    return(a>b) ? a : b;
}

int max3(int a, int b, int c){
    return max(a, max(b,c));
}

int getHeight(Station* a) {
    if (a == NULL){
        return 0;
    }
    return 1 + max(getHeight(a->fg), getHeight(a->fd));
}

int getBalance(Station* a){
    if (a == NULL){
        return 0;
    }
    return getHeight(a->fd) - getHeight(a->fg);
}

Station* rotateLeft(Station* a){
    Station* shaft = a->fd; 
    int eq_a = a->eq;
    int eq_p = shaft->eq;
    a->fd = shaft->fg; 
    shaft->fg = a; 
    a->eq = eq_a - max(eq_p, 0) - 1;
    shaft->eq = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return shaft; 
}

Station* rotateRight(Station* a){
    Station* shaft = a->fg; 
    int eq_a = a->eq;
    int eq_p = shaft->eq;
    a->fg = shaft->fd; 
    shaft->fg = a; 
    a->eq = eq_a - max(eq_p, 0) - 1;
    shaft->eq = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return shaft; 
}

Station* doublerotationLeft(Station* a){
    a->fd = rotateRight(a->fd);
    return rotateLeft(a);
}

Station* doublerotationRight(Station* a){
    a->fg = rotateLeft(a->fg);
    return rotateRight(a);
}

Station* createStation(int id, int capacity, int sum_consumption){
    Station* newStation = malloc(sizeof(Station));
    if(newStation == NULL){
        exit(1);
    }
    newStation->id = id;                            // Unique station identifier
    newStation->capacity = capacity;                // Station capacity in kWh
    newStation->sum_consumption = sum_consumption;  // Sum of consumer consumption
    newStation->fg = newStation->fd = NULL;         // Initialization of sub tree left and right
    newStation->height = 1;                         // Knot height (always 1 for a new node)
    newStation->eq = 0;                             // Initial balance tree (always 0 at the beginning)
    return newStation;                              // return the pointer to the new node 
}

Station* balance(Station* a, int id){
    if(a == NULL){
        exit(2);
    }
    if(a->eq >= 2){                                 // Case when tree is unbalanced on the right side
        if(a->fd == NULL){
            exit(3);
        }
        if(a->fd->eq >= 0){
            a = rotateLeft(a);
        }
        else{
            a = doublerotationLeft(a);
        }
    }
    else if(a->fg <= -2){                           // Case when tree is unbalanced on the left side
        if(a->fg == NULL){
            exit(4);
        }
        if(a->fg->eq <= 0){
            a = rotateRight(a);
        }
        else{
            a = doublerotationRight(a);
        }
    }
    return a;                                       // No balance traitement required
}

Station* insertStation(Station* a, int id, int capacity, int sum_consumption, int* h){
    if(a == NULL){
        *h = 1;                                     // Node has a height of 1
        a = createStation(id, capacity, sum_consumption);
    }
    else if(id < a->id){                            // If the element is shorter, insert on left
        a->fg = insererAVL(a->fg, id, capacity, sum_consumption, h);
        *h = -*h; 
    }
    else if(id > a->id){                            // If the element is taller, insert on right
        a->fd = insererAVL(a->fd, id, capacity, sum_consumption, h);
    }
    else{                                           // Element is already here
        *h = 0;                                     // The height doesn't change
        return a;
    }
    if(*h != 0){                                    // Update of balance if it's necessary
        a->eq += *h;
        a = balance(a, id);
        *h = (a->eq == 0) ? 0 : 1;                  // Update height
    }
    return a;
}
#include "tree.h"
#include "balance.h"
#include "tratment.h"
#include "avl_to_csv.h"


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

Station * createNode(){
    Station * new = malloc(sizeof(Station *));
    if (new==NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    new->leftSon = NULL;
    new->rightSon = NULL;
    new->balance = 0;
    new->id = 0;
    new->load = 0;
    new->capacity = 0;
    return new;
}

Station * createStation(long capacity, int id){
    Station *new = createNode();
    new->capacity = capacity;
    new->id = id;
    return new;
}

int search(Station* a, int id, Station* *searched) {
    if (a == NULL) { 
        *searched = a;
        return 0;
    }
    if (a->id == id) { 
        *searched = a;
        return 1;
    }
    if (id < a->id) {
        return search(a->leftSon, id, searched);
    } else {
        return search(a->rightSon, id, searched);
    }
} 
#include <stdio.h>
#include <stdlib.h>

typedef struct Station {
    struct Station* leftSon;    
    struct Station* rightSoon;  
    int balance;   
    int id;      
    long load;          
    long capacity;           
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
    pAvl new = createNode();
    new->capacity = capacity;
    new->id = id;
    return new;
}

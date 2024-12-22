#include "settings.h"


//Function that returns the minimum between two values
int min(int a, int b){
    return(a<b) ? a : b;
}


//Function that returns the minimum between three values
int min3(int a, int b, int c){
    return min(a, min(b,c));
}


//Function that returns the maximum between two values
int max(int a, int b){
    return(a>b) ? a : b;
}


//Function that returns the maximum between three values
int max3(int a, int b, int c){
    return max(a, max(b,c));
}


//Function that creates a new station 
Station *createStation(int Id,long Capacity,long Load){
    Station * new = malloc(sizeof(Station));
    if (new == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new -> leftSon = NULL;
    new -> rightSon = NULL;
    new -> balance = 0;
    new -> id = Id;
    new -> load = Load;
    new -> capacity = Capacity;
    return new;
}


//Function that looks for an identifier int the tree and returns 1 if found and 0 otherwise
//The pointer **searched stores the address of the found station
int search(Station* a, int id, Station** searched) {
    if (a == NULL) {
        return 0;
    }
    if (a -> id == id) { 
        *searched = a;
        return 1;
    }
    if (id < a -> id) {
        return search(a -> leftSon, id, searched);
    } else {
        return search(a -> rightSon, id, searched);
    }
} 


//Procedure for the infix path of the tree
void Infix (Station *p){ 
    if(p != NULL){
        Infix(p -> leftSon);
        printf("%d;%ld;%ld\n",p -> id, p -> capacity, p -> load);
        Infix(p -> rightSon);
    }
}


//Procedure to remove all nodes from the tree recursively
void deleteTree(Station* root) {
    if (root == NULL) {
        return;
    }
    deleteTree(root -> leftSon);
    deleteTree(root -> rightSon);
    free(root);
}


//Function to rotate left
Station* rotateLeft(Station* a){
    Station* pivot = a -> rightSon; 
    int eq_a = a -> balance;
    int eq_p = pivot -> balance;
    a -> rightSon = pivot -> leftSon; 
    pivot -> leftSon = a; 
    a -> balance = eq_a - max(eq_p, 0) - 1;
    pivot -> balance = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return pivot; 
}


//Function to rotate right
Station* rotateRight(Station* a){
    Station* pivot = a -> leftSon; 
    int eq_a = a -> balance;
    int eq_p = pivot -> balance;
    a -> leftSon = pivot -> rightSon; 
    pivot -> leftSon = a; 
    a -> balance = eq_a - max(eq_p, 0) - 1;
    pivot -> balance = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return pivot; 
}


//Function to perform a double left rotation
Station* doublerotationLeft(Station* a){
    a -> rightSon = rotateRight(a -> rightSon);
    return rotateLeft(a);
}


//Function to perform a double right rotation
Station* doublerotationRight(Station* a){
    a -> leftSon = rotateLeft(a -> leftSon);
    return rotateRight(a);
}


//Function that balances the tree
Station* balance(Station* a){
    if(a == NULL){
        exit(2);
    }
    if(a -> balance >= 2){                                
        if(a -> rightSon == NULL){
            exit(3);
        }
        if(a -> rightSon -> balance >= 0){
            a = rotateLeft(a);
        }
        else{
            a = doublerotationLeft(a);
        }
    }
    else if(a -> balance <= -2){                         
        if(a -> leftSon == NULL){
            exit(4);
        }
        if(a -> leftSon -> balance <= 0){
            a = rotateRight(a);
        }
        else{
            a = doublerotationRight(a);
        }
    }
    return a;
}


//Function to insert a node in the tree
Station* insertStation(Station* a, int id, long capacity, long load, int* h) {
    if (a == NULL) { 
        *h = 1;
        return createStation(id,capacity,load);
    } 
    else if (id < a->id){ 
        a->leftSon = insertStation(a->leftSon, id, capacity, load, h);
        *h = -*h; 
    } 
    else if (id > a->id){ 
        a->rightSon = insertStation(a->rightSon, id, capacity, load, h);
    } 
    else{
        *h = 0;
        return a;
    }

    if (*h != 0) {
        a->balance += *h;
        a = balance(a);
        *h = (a->balance == 0) ? 0 : 1;
    }
    return a;
}
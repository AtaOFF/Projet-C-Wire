#include "settings.h"


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

int search(Station* a, int id, Station** searched) {
    if (a == NULL) {
        return 0;
    }
    if (a -> id == id) { 
        *searched = a;
        return 1;
    }
    if (id < a -> id) {
        return search(a->leftSon, id, searched);
    } else {
        return search(a->rightSon, id, searched);
    }
} 

void Infix(Station *p){ 
    if(p!=NULL){
        Infix(p->leftSon);
        printf("%d;%ld;%ld\n",p->id,p->capacity,p->load);
        Infix(p->rightSon);
    }
}

void deleteTree(Station* root) {
    if (root == NULL) {
        return;
    }

    /* Appel récursif pour supprimer les sous-arbres gauche et droit */
    deleteTree(root->leftSon);
    deleteTree(root->rightSon);

    /* Libération du nœud actuel */
 free(root);
}

Station* rotateLeft(Station* a){
    Station* pivot = a->rightSon; 
    int eq_a = a->balance;
    int eq_p = pivot->balance;
    a->rightSon = pivot->leftSon; 
    pivot->leftSon = a; 
    a->balance = eq_a - max(eq_p, 0) - 1;
    pivot->balance = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return pivot; 
}

Station* rotateRight(Station* a){
    Station* pivot = a->leftSon; 
    int eq_a = a->balance;
    int eq_p = pivot->balance;
    a->leftSon = pivot->rightSon; 
    pivot->leftSon = a; 
    a->balance = eq_a - max(eq_p, 0) - 1;
    pivot->balance = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return pivot; 
}

int getHeight(Station* a) {
    if (a == NULL){
        return 0;
    }
    return 1 + max(getHeight(a->leftSon), getHeight(a->rightSon));
}

int getBalance(Station* a){
    if (a == NULL){
        return 0;
    }
    return getHeight(a->rightSon) - getHeight(a->leftSon);
}

Station* doublerotationLeft(Station* a){
    a->rightSon = rotateRight(a->rightSon);
    return rotateLeft(a);
}

Station* doublerotationRight(Station* a){
    a->leftSon = rotateLeft(a->leftSon);
    return rotateRight(a);
}


Station* balance(Station* a){
    if(a == NULL){
        exit(2);
    }
    if(a->balance >= 2){                                
        if(a->rightSon == NULL){
            exit(3);
        }
        if(a->rightSon->balance >= 0){
            a = rotateLeft(a);
        }
        else{
            a = doublerotationLeft(a);
        }
    }
    else if(a->balance <= -2){                         
        if(a->leftSon == NULL){
            exit(4);
        }
        if(a->leftSon->balance <= 0){
            a = rotateRight(a);
        }
        else{
            a = doublerotationRight(a);
        }
    }
    return a;
}

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
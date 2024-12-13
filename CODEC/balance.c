#include "tree.h"
#include "balance.h"
#include "tratment.h"
#include "transfer.h" 


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

Station* doublerotationLeft(Station* a){
    a->rightSon = rotateRight(a->rightSon);
    return rotateLeft(a);
}

Station* doublerotationRight(Station* a){
    a->leftSon = rotateLeft(a->leftSon);
    return rotateRight(a);
}


Station* balance(Station* a, int id){
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
    else if(a->leftSon <= -2){                         
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


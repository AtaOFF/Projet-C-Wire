#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



typedef struct Station {
    struct Station* leftSon;    
    struct Station* rightSon;  
    int balance;   
    int id;      
    long load;          
    long capacity;           
} Station;



int min(int a, int b);
int min3(int a, int b, int c);
int max(int a, int b);
int max3(int a, int b, int c);

Station * createStation(long capacity, int id);
int search(Station *a, int id, Station **searched);
void Infix(Station *p);
void deleteTree(Station *root);
Station* rotateLeft(Station* a);
Station* rotateRight(Station* a);
int getHeight(Station *a);
int getBalance(Station *a);
Station* doublerotationLeft(Station* a);
Station* doublerotationRight(Station* a);
Station* balance(Station* a);
Station* insertStation(Station* a, int id, long capacity, long load, int* h);
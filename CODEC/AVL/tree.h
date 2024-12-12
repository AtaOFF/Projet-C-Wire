#include <stdio.h>
#include <stdlib.h>


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
Station * createNode();
Station * createStation(long capacity, int id);
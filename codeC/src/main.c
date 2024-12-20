#include "settings.h"


int main() {
    Station* tree = NULL;
    Station* node = NULL;
    int return = 0;
    int arg1;
    long arg2,arg3; 
    int h;
    printf("Identifier;Capacity;Load\n");
    do{
        return = scanf("%d;%ld;%ld\n", &arg1, &arg2, &arg3);
        if(return == 3 && search(tree, arg1, &node) == 0){
            tree = insertStation(tree, arg1, arg2, arg3, &h); 
        }
       
        else if(return == 3 && search(tree, arg1, &node) == 1 && arg2 != 0){
            node -> capacity = arg2;
        }
        else if(return == 3 && search(tree, arg1, &node) == 1 && v3 != 0){
            node -> load += arg3;
        }    

    } while(return == 3);
    Infix(tree);
    return 0;
}
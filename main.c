#include "settings.h"


int main() {

//Declaration and initialization a tree into NULL
    Station* tree = NULL;
//Declaration and initialization a node into NULL
    Station* node = NULL;
//Declaration of a variable to check the return of the scanf
    int tmp=0;
//Declaration of 3 variables to retrieve the arguments from the shell
    int arg1;
    long arg2,arg3; 
//Declaration of a varibale to manage the height of the tree
    int h;


    printf("Identifier;Capacity;Load\n");
    do{
        tmp = scanf("%d;%ld;%ld\n", &arg1, &arg2, &arg3);
//Retrieval of the 3 arguments from the shell in variables
//The tmp variable takes the return value of the scanf

        if(tmp == 3 && search(tree, arg1, &node) == 0){
//If the scanf worked well and and the first argument (identifiant of the station) 
//is not already part of the tree
            tree = insertStation(tree, arg1, arg2, arg3, &h); 
//Insert the first argument in the tree and update the tree
        }

//Else if the scanf worked well and and the first argument is already part of the tree,
//and if the second argument (capacity of the station) is valid
        else if(tmp == 3 && search(tree, arg1, &node) == 1 && arg2 != 0){
//Fill the capacity field of the station node with the value contained in arg2
            node -> capacity = arg2;
        }

//Else if the scanf worked well and and the first argument is already part of the tree,
//and if the third argument (load of the station) is valid
        else if(tmp == 3 && search(tree, arg1, &node) == 1 && arg3 != 0){
//Update load by adding the value of arg3
            node -> load += arg3;
        }    

    } while(tmp == 3);
//Repeat condition as long as the scanf is working properly

    Infix(tree);
//Do an infix path of the tree so that the data is sorted in ascending order of identifier
    return 0;
}
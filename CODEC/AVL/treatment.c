#include "treatment.h"
#include "tree.h"
#include "balance.h"



Station* insertStation(Station* a, int id, long capacity,  int* h){
    if(a == NULL){
        *h = 1;                                    
        a = createStation(id, capacity);
    }
    else if(id < a->id){                           
        a->leftSon = insertStation(a->leftSon, id, capacity,h);
        *h = -*h; 
    }
    else if(id > a->id){                            
        a->fd = insertStation(a->fd, id, capacity,h);
    }
    else{                                           
        *h = 0;                                    
        return a;
    }
    if(*h != 0){                                   
        a->eq += *h;
        a = balance(a, id);
        *h = (a->eq == 0) ? 0 : 1;                 
    }
    return a;
}


void ProcessFile (const char *filename, Station * a, int *h){
    File *file=fopen(filename, "r");
    if(file==NULL){
        printf("Unable to open file %s.\n");
        exit(1);
    }

    char * buffer= malloc(SIZE * sizeof(char)); // buffer=tampon
    if(buffer==NULL){
        
    }
    while (fgets(buffer, SIZE, file)) {
    ...
}

}
 
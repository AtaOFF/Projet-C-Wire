#include "treatment.h"
#include "transfer.h"
#include "balance.h"
#include "tree.h"


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
        a->rightSon = insertStation(a->rightSon, id, capacity,h);
    }
    else{                                           
        *h = 0;                                    
        return a;
    }
    if(*h != 0){                                   
        a->balance += *h;
        a = balance(a, id);
        *h = (a->balance == 0) ? 0 : 1;                 
    }
    return a;
}


Station * updateStation(Station * a, int id, long load) {
    Station * station;
    int h = 0;
    int result = search(a, id, &station);
    if (!result) {
        a = insertStation(a, id, 0, &h);
    } else {
        station->load += load;
    }

    return a;
}


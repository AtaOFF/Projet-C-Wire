#include "settings.h"


int main() {
    Station* tree=NULL;
    Station* node=NULL;
    int ret=0;
    int v1;
    long v2,v3; 
    int h;
    printf("Identifier;Capacity;Load\n");
    do{
        ret=scanf("%d;%ld;%ld\n",&v1,&v2,&v3);
        if(ret==3 && search(tree,v1,&node)==0){
            tree=insertStation(tree,v1,v2,v3,&h); 
        }
       
        else if(ret==3 && search(tree,v1,&node)==1 && v2!=0){
            node->capacity=v2;
        }
        else if(ret==3 && search(tree,v1,&node)==1 && v3!=0){
            node->load+=v3;
        }    

    } while(ret==3);
    Infix(tree);
    return 0;
}
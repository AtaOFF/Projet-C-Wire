#include "treatment.h"
#include "a.h"
#include "balance.h"
#include "transfer.h"


void fprintAVL(Station *a, FILE *file) {
    if (a != NULL){
        fprintAVL(a->leftSon, file);
        fprintf(file,"%d:%ld:%ld\n", a->id, a->capacity, a->load);
        fprintAVL(a->rightSon, file);
    }
}

//transfer the contents of an AVL a to a CSV file.

void transferToFile(Station *a, const char *filename, const char *header) {
    FILE *file = fopen(filename, "w+");
    if (file == NULL) {
        printf("unable to open file\n");
        exit(4);
    }
    fprintf(file, "%s\n", header);
    fprintAVL(a, file);
    fclose(file);
}

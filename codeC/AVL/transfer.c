

#include "treatment.h"
#include "tree.h"
#include "balance.h"

void fprintAVL(pAvl node, FILE *file) {
    if (node != NULL){
        fprintAVL(node->leftSon, file);
        fprintf(file,"%d:%ld:%ld\n", node->id, node->capacity, node->load);
        fprintAVL(node->rightSon, file);
    }
}

//transfer the contents of an AVL tree to a CSV file.

void transferToFile(pAvl tree, const char *filename, const char *header) {
    FILE *file = fopen(filename, "w+");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(4);
    }
    fprintf(file, "%s\n", header);
    fprintAVL(tree, file);
    fclose(file);
}

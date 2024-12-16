#include "data_to_avl.h"

Station * updateAVL(Station * tree, int id, long load){
   Station * station;
    int h = 0;
    int result = search(tree, id, &station);
    if (!result) {
        tree = insertAVL(tree, 0, &h, id);
    } else {
        station->load += load;
    }

    return tree;
}


Station* buildAvl(Station* tree, int isLv, int isHva, int isHvb, char *chvb, char *chva, char *clv, char *ccomp, char *cindiv, char *ccapa, char *cload) {
    int h = 0;
    if (isLv) {
        if (strcmp("-", chva)) { // This is an lv station

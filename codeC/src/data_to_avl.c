#include "settings.h"


Station* buildAvl(Station* tree, int isLv, int isHva, int isHvb, char *chvb, char *chva, char *clv, char *ccomp, char *cindiv, char *ccapa, char *cload) {
    int h = 0;
    if (isLv) {
        if (strcmp("-", chva)) { // This is an lv station

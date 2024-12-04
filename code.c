#include <stdio.h>
#include <stdlib.h>

typedef struct _avl{
    int value;
    int eq;
    struct _avl* fd;
    struct _avl* fg;
} AVL;

int min(int a, int b){
    return(a<b) ? a : b;
}

int min3(int a, int b, int c){
    return min(a, min(b,c));
}

int max(int a, int b){
    return(a>b) ? a : b;
}

int max3(int a, int b, int c){
    return max(a, max(b,c));
}

AVL* creerAVL(int v){
    AVL* new = malloc(sizeof(AVL));
    if(new == NULL){
        exit(1);
    }
    new->value = v;
    new->fd = new->fg = NULL;
    new->eq = 0; // Facteur d'équilibre initialisé à 0
    return new;
}

// Fonction rotation Gauche
AVL* rotationLeft(AVL* a){
    AVL* pivot = a->fd; // Le fd devient le pivot
    // Save des facteur d'eq de a et du pivot
    int eq_a = a->eq;
    int eq_p = pivot->eq;
    a->fd = pivot->fg; // Le sous-arbre gauche du pivot devient le fd de a
    pivot->fg = a; // a devient le fg du pivot
    // MAJ des facteurs d'eq
    a->eq = eq_a - max(eq_p, 0) - 1;
    pivot->eq = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return pivot; // Le pivot devient la nouvelle racine de ce sous-arbre
}

// Fonction rotation Droite
AVL* rotationRight(AVL* a){
    AVL* pivot = a->fg; // Le fg devient le pivot
    // Save des facteur d'eq de a et du pivot
    int eq_a = a->eq;
    int eq_p = pivot->eq;
    a->fg = pivot->fd; // Le sous-arbre gauche du pivot devient le fd de a
    pivot->fd = a; // a devient le fg du pivot
    // MAJ des facteurs d'eq
    a->eq = eq_a - max(eq_p, 0) + 1;
    pivot->eq = min3(eq_a + 2, eq_a + eq_p + 2, eq_p + 1);
    return pivot; // Le pivot devient la nouvelle racine de ce sous-arbre
}

// Double rotation gauche
AVL* doublerotationLeft(AVL* a){
    a->fd = rotationRight(a->fd);
    return rotationLeft(a);
}

// Double rotation droite
AVL* doublerotationRight(AVL* a){
    a->fg = rotationLeft(a->fg);
    return rotationRight(a);
}
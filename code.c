#include <stdio.h>
#include <stdlib.h>

typedef struct _avl{
    int value;
    int eq;
    struct _avl* fd;
    struct _avl* fg;
} AVL;

// Result minimum for 2 variables
int min(int a, int b){
    return(a<b) ? a : b;
}

// Result minimum for 3 variables
int min3(int a, int b, int c){
    return min(a, min(b,c));
}

// Result maximum for 2 variables
int max(int a, int b){
    return(a>b) ? a : b;
}

// Result maximum for 3 variables
int max3(int a, int b, int c){
    return max(a, max(b,c));
}

// Function to create an AVL
AVL* createAVL(int v){
    AVL* new = malloc(sizeof(AVL));
    if(new == NULL){
        exit(1);
    }
    new->value = v;
    new->fd = new->fg = NULL;
    new->eq = 0; // Balance factor initialited to 0
    return new;
}

// Function rotation left
AVL* rotationLeft(AVL* a){
    AVL* pivot = a->fd; // Right son become the pivot
    // Save balance factor of a and pivot
    int eq_a = a->eq;
    int eq_p = pivot->eq;
    a->fd = pivot->fg; //  The left subtree of the pivot becomes the right son
    pivot->fg = a; // a becomes the left son of the pivot
    // update balance factor
    a->eq = eq_a - max(eq_p, 0) - 1;
    pivot->eq = min3(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    return pivot; //  pivot becomes the new root of this subtree

// Function rotation right
AVL* rotationRight(AVL* a){
    AVL* pivot = a->fg; // left son become the pivot
    // Save balance factor of a and pivot   
    int eq_a = a->eq;
    int eq_p = pivot->eq;
    a->fg = pivot->fd; //The right subtree of the pivot becomes the left son
    pivot->fd = a; // a becomes the right son of the pivot
    // update balance factor
    a->eq = eq_a - max(eq_p, 0) + 1;
    pivot->eq = min3(eq_a + 2, eq_a + eq_p + 2, eq_p + 1);
    return pivot; //  pivot becomes the new root of this subtree
}

// Double left rotation 
AVL* doublerotationLeft(AVL* a){
    a->fd = rotationRight(a->fd);
    return rotationLeft(a);
}

// Double right rotation 
AVL* doublerotationRight(AVL* a){
    a->fg = rotationLeft(a->fg);
    return rotationRight(a);
}

// balance 
AVL* equilibreAVL(AVL* a){
    if(a == NULL){
        exit(2);
    }
    // Cas où l'arbre est déséquilibré à droite
    if(a->eq >= 2){
        if(a->fd == NULL){
            exit(3);
        }
        if(a->fd->eq >= 0){
            a = rotationLeft(a);
        }
        else{
            a = doublerotationLeft(a);
        }
    }
    // Cas où l'arbre est déséquilibré à gauche
    else if(a->fg <= -2){
        if(a->fg == NULL){
            exit(4);
        }
        if(a->fg->eq <= 0){
            a = rotationRight(a);
        }
        else{
            a = doublerotationRight(a);
        }
    }
    // Aucun rééquilibrage nécessaire
    return a;
}

// Insertion 
AVL* insererAVL(AVL* a, int e, int* h){
    if(a == NULL){
        *h = 1; // un noeud seul a une hauteur de 1
        a = creerAVL(e);
    }
    else if(e < a->value){
        // Si l'élément est plus petit, insérer à gauche
        a->fg = insererAVL(a->fg, e, h);
        *h = -*h; // inverse l'impact de la hauteur
    }
    else if(e > a->value){
        // Si l'élément est plus grand, insérer à droite
        a->fd = insererAVL(a->fd, e, h);
    }
    else{
        // Elément est déjà présent
        *h = 0; // la hauteur ne change pas
        return a;
    }
    // MAJ du facteur d'eq et rééquilibrage si nécessaire
    if(*h != 0){ // si l'insertion a modifié la hauteur
        a->eq += *h;
        a = equilibreAVL(a);
        *h = (a->eq == 0) ? 0 : 1; // Maj de la hauteru
    }
    return a;
}



// Main function
int main() {
    AVL* arbre = NULL;  // Root of the AVL tree
    int h = 0;    // Height adjustment flag
    int value;         // To hold values during insertion/removal

    // Step 1: Load data from a file or standard input
    printf("Loading data from 'filtered_data.dat'...\n");
    FILE* fichier = fopen("filtered_data.dat", "r");
    if (fichier == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Insert data into AVL tree
    char line[256];
    while (fgets(line, sizeof(line), fichier)) {
        // Parse each line (format: ID,Name,Score)
        int id, score;
        char name[50];
        if (sscanf(line, "%d,%49[^,],%d", &id, name, &score) == 3) {
            printf("Inserting ID %d (Name: %s, Score: %d) into AVL...\n", id, name, score);
            arbre = insererAVL(arbre, id, &h);
        } else {
            fprintf(stderr, "Invalid line format: %s", line);
        }
    }
    fclose(fichier);

    // Step 2: Display the tree (In-Order Traversal)
    printf("\nAVL Tree (In-Order Traversal):\n");
    parcoursInOrder(arbre);
    printf("\n");

    // Step 3: Remove an element from the AVL tree
    printf("Removing an element from the AVL tree...\n");
    printf("Enter the ID to remove: ");
    scanf("%d", &value);
    arbre = suppressionAVL(arbre, value, &h);
    printf("Updated AVL Tree (In-Order Traversal):\n");
    parcoursInOrder(arbre);
    printf("\n");

    // Step 4: Free the tree memory
    printf("Freeing the AVL tree memory...\n");
    libererArbre(arbre);

    return EXIT_SUCCESS;
}
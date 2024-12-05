#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int *id_station;
    int *capacity;
    int *cons;
} Station;

typedef struct tree {
    Station elt;
    struct tree *fg;
    struct tree *fd;
    int balance;
} AVL;

typedef AVL* PAVL;

//Prototypes

PAVL makeAVL(Station elt);
PAVL AVLinsertion(PAVL a, Station elt, int* h);

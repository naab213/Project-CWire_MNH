#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *id_station;
    int *capacity;
    long *cons;
} Station;

typedef struct AVL {
    Station elt;
    struct AVL *fg;
    struct AVL *fd;
    int balance;
} AVL;

typedef AVL* PAVL;

PAVL makeAVL(Station elt);
PAVL AVLinsertion(PAVL a, Station elt, int* h);

#endif // TREE_H

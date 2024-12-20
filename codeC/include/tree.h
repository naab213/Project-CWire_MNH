#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long *id_station;
    long *capacity;
    long *cons;
} Station;

typedef struct AVL {
    Station elt;
    struct AVL *fg;
    struct AVL *fd;
    int balance;
} AVL;

typedef AVL* PAVL;

PAVL makeAVL(Station* elt);
Station* createStation(long id, long capacity, long cons);
PAVL AVLinsertion(PAVL a, Station elt, int* h);


#endif // TREE_H

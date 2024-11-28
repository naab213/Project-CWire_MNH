#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
int max(int a, int b);
int min(int a, int b, int c);
PAVL leftRotation(PAVL a);
PAVL rightRotation(PAVL a);
PAVL leftDoubleRotation(PAVL a);
PAVL rightDoubleRotation(PAVL a);
PAVL balanceAVL(PAVL a);
PAVL AVLinsertion(PAVL a, Station elt, int* h);

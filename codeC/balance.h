#include <stdio.h>
#include <stdlib.h>

//Prototypes

int max(int a, int b);
int min(int a, int b, int c);
PAVL leftRotation(PAVL a);
PAVL rightRotation(PAVL a);
PAVL leftDoubleRotation(PAVL a);
PAVL rightDoubleRotation(PAVL a);
PAVL balanceAVL(PAVL a);
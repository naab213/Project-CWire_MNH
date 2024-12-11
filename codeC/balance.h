#ifndef BALANCE_H
#define BALANCE_H

#include "tree.h"


int max(int a, int b);
int min(int a, int b, int c);
int min2(int a, int b);
int max2(int a, int b, int c);
PAVL leftRotation(PAVL a);
PAVL rightRotation(PAVL a);
PAVL leftDoubleRotation(PAVL a);
PAVL rightDoubleRotation(PAVL a);
PAVL balanceAVL(PAVL a);

#endif // BALANCE_H

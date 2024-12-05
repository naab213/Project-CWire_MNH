#include "balance.h"
#include "tree.h"


int max(int a, int b){
    if(a >= b){
        return a;
    }
    else{
        return b;
    }
}

int min(int a, int b, int c){
    int min = a;

    if(b < min){
        min = b;
    }
    if(c < min){
        min = c;#include "track.h"
#include "tree.h"
#include "balance.h"
    }
    return min;
}


PAVL leftRotation(PAVL a){
    PAVL pivot;
    int ba_a, ba_p;
    pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;

    ba_a = a->balance;
    ba_p = pivot->balance;

    a->balance = ba_a - max(ba_p, 0) -1;
    pivot->balance = min(ba_a-2, ba_a + ba_p-2, ba_p-1);

    a = pivot;
    return a;

}

PAVL rightRotation(PAVL a){
    PAVL pivot;
    int ba_a, ba_p;
    pivot = a->fg; //on inverse fg et fd
    a->fg = pivot->fd;
    pivot->fd = a;

    ba_a = a->balance;
    ba_p = pivot->balance;

    a->balance = ba_a - max(ba_p, 0) +1; //on remplace les - par des +
    pivot->balance = min(ba_a+2, ba_a + ba_p+2, ba_p+1);

    a = pivot;
    return a;

}


PAVL leftDoubleRotation(PAVL a){
    a->fd = rightRotation(a->fd);
    return leftRotation(a);
}

PAVL rightDoubleRotation(PAVL a){
    a->fg = leftRotation(a->fg);
    return rightRotation(a);
}


PAVL balanceAVL(PAVL a){
    if(a->balance >= 2){
        if(a->fd->balance >= 0){
            return leftRotation(a);
        }
        else{
            return leftDoubleRotation(a);
        }
    }
    else if(a->balance <= -2){
        if(a->fg->balance <= 0){
            return rightRotation(a);
        }
        else{
            return rightDoubleRotation(a);
        }
    }
    return a;
}

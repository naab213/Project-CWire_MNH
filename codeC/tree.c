#include "tree.h"

PAVL makeAVL(Station elt){
    PAVL a;
    a = malloc(sizeof(PAVL));
    a->elt.id_station = NULL;
    a->elt.capacity = NULL;
    a->elt.cons = NULL;
    a->fg = NULL;
    a->fd = NULL;
    a->balance = 0;
    return a;
}


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
        min = c;
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

PAVL AVLinsertion(PAVL a, Station elt, int* h){
    if(a == NULL){
        *h = 1;
        return makeAVL(elt);
    }
    else if(elt.cons < a->elt.cons){
        a->fg = AVLinsertion(a->fg, elt, h);
        *h = -*h;
    }
    else if(elt.cons > a->elt.cons){
        a->fd = AVLinsertion(a->fd, elt, h);
    }
    else{
        *h = 0;
        return a;
    }

    if(*h != 0){
        a->balance += *h;
        a = balanceAVL(a);
        if(a->balance == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }
    return a;
}

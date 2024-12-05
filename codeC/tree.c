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

PAVL AVLinsertion(PAVL a, Station elt, int* h){
    if(a == NULL){
        *h = 0;
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


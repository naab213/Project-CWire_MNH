#include "tree.h"
#include "balance.h"


PAVL makeAVL(Station elt){
    PAVL a;
    a = malloc(sizeof(PAVL));
    a->elt.id_station = NULL;
    //a->elt.capacity = NULL;
    a->elt.cons = NULL;
    a->fg = NULL;
    a->fd = NULL;
    a->balance = 0;

    return a;
}

Station* createStation(int id, int capacity, int cons){
    Station* newStation = malloc(sizeof(Station));
    if(newStation == NULL){
        printf("The allocation for the station failed.");
        exit(1);
    }

    newStation->id_station = id;
    //newStation->capacity = malloc(sizeof(int));
    newStation->cons = cons;

    return newStation;
}

PAVL makeAVL(Station* elt){
    if(elt == NULL){
        printf("The doesn't exist.");
        exit(3);
    }
    PAVL a = malloc(sizeof(PAVL));
    if(a == NULL){
        printf("The allocation for the node failed.");
        exit(4);
    }

    a->elt = *elt;
    a->fg = NULL;
    a->fd = NULL;
    a->balance = 0;

    return a;
}

PAVL AVLinsertion(PAVL a, Station elt, int* h){
    if(a == NULL){
        *h = 1;
        return makeAVL(elt);
    }

    if(elt.cons < a->elt.cons){
        a->fg = AVLinsertion(a->fg, elt, h);
    } 
    else if(elt.cons > a->elt.cons){
        a->fd = AVLinsertion(a->fd, elt, h);
    } 
    else {
        *h = 0;
        return a;
    }

    if (*h != 0) {
        a->balance += *h;
        a = balanceAVL(a);

        if (a->balance == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }

    return a;
}



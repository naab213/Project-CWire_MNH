#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "balance.h"

PAVL makeAVL(Station* elt){
    if(elt == NULL){
        printf("The station doesn't exist.");
        exit(3);
    }
    PAVL a = malloc(sizeof(AVL));
    if(a == NULL){
        printf("Error: Memory allocation for AVL node failed.\n");
        exit(4);
    }

    a->elt.id_station = malloc(sizeof(long));
    a->elt.capacity = malloc(sizeof(long));
    a->elt.cons = malloc(sizeof(long));

    if (a->elt.id_station == NULL || a->elt.capacity == NULL || a->elt.cons == NULL) {
        printf("Error: Memory allocation for station data failed.\n");
        exit(5);
    }

    *(a->elt.id_station) = *(elt->id_station);
    *(a->elt.capacity) = *(elt->capacity);
    *(a->elt.cons) = *(elt->cons);

    a->fg = NULL;
    a->fd = NULL;
    a->balance = 0;

    return a;
}

Station* createStation(long id, long capacity, long cons){
    Station* newStation = malloc(sizeof(Station));
    if(newStation == NULL){
        printf("Error: Memory allocation for station failed.\n");
        exit(1);
    }

        newStation->id_station = malloc(sizeof(long));
    newStation->capacity = malloc(sizeof(long));
    newStation->cons = malloc(sizeof(long));

    if (newStation->id_station == NULL || newStation->capacity == NULL || newStation->cons == NULL) {
        printf("Error: Memory allocation for station fields failed.\n");
        exit(2);
    }

    *(newStation->id_station) = id;
    *(newStation->capacity) = capacity;
    *(newStation->cons) = cons;

    return newStation;
}

PAVL AVLinsertion(PAVL a, Station elt, int* h){
    if(a == NULL){
        *h = 1;
        return makeAVL(&elt);
    }

    if(*(elt.id_station) < *(a->elt.id_station)){
        a->fg = AVLinsertion(a->fg, elt, h);
    } 
    else if(*(elt.id_station) > *(a->elt.id_station)){
        a->fd = AVLinsertion(a->fd, elt, h);
    } 
    else {
        *h = 0;
        return a;
    }

    if (*h != 0) {
        a->balance += (*h);
        a = balanceAVL(a);

        if (a->balance == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }

    return a;
}
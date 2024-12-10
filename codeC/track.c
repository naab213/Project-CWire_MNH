#include "track.h"
#include "tree.h"


void traiter(PAVL a){
    printf("%d ", a->elt);
}

void parcoursInfixe(PAVL a){
    if(a != NULL){
        parcoursInfixe(a->fg);
        traiter(a);
        parcoursInfixe(a->fd);
    }
}
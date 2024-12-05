#include "track.h"
#include "tree.h"
#include "balance.h"

void traiter(Arbre* a){
    printf("%d ", a->elt);
}

void parcoursInfixe(Arbre* a){
    if(a != NULL){
        parcoursInfixe(a->fg);
        traiter(a);
        parcoursInfixe(a->fd);
    }
}
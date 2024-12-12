#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "track.h"
#include "tree.h"


void traiter(PAVL a, FILE *file){
    fprintf(file, "%d; %d; %ld\n", a->elt.id_station, a->elt.capacity, a->elt.cons);
}


void parcoursInfixe(PAVL a, FILE *file){
    if(a != NULL){
        parcoursInfixe(a->fg, file);
        traiter(a, file);
        parcoursInfixe(a->fd, file);
    }
}

void fillCSV(PAVL a, FILE *file){
    parcoursInfixe(a, file);
}

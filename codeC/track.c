#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "track.h"
#include "tree.h"


void traiter(PAVL a, FILE *file){
    if (a->elt.id_station == NULL || a->elt.capacity == NULL || a->elt.cons == NULL) {
        printf("Error: Null pointer in station data.\n");
        exit(46);
    }
    fprintf(file, "%ld; %ld; %ld\n", *(a->elt.id_station), *(a->elt.capacity), *(a->elt.cons));
}


void parcoursInfixe(PAVL a, FILE *file){
    if(a != NULL){
        parcoursInfixe(a->fg, file);
        traiter(a, file);
        parcoursInfixe(a->fd, file);
    }
}

void fillCSV(PAVL a, FILE *file){
    if (file == NULL) {
    printf("Error: File is not open.\n");
    exit(47);
    }
    fprintf(file, "Station ; Capacity ; Consumption\n");
    parcoursInfixe(a, file);
}

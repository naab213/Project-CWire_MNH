#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treatment.h"
#include "tree.h"
#include "balance.h"
#include "track.h"


int search(PAVL a, long id){
    if(a == NULL){
        return 0;
    } 
    else if( *(a->elt.id_station) == id){
        return 1;
    } 
    else if(id < *(a->elt.id_station) ){
        return search(a->fg, id);
    } 
    else{
        return search(a->fd, id);
    }
}

int updateCapacity(PAVL* a, long id, long new_capacity){
    PAVL node = *a;
    if(search(node, id)){ 
        node->elt.capacity = malloc(sizeof(long)); // Allouer de la mémoire
        if(node->elt.capacity != NULL) {
            *(node->elt.capacity) = new_capacity;
            return 1;
        }
    }
    return 0;
}


int addConsumption(PAVL* a, long id, long new_cons) {
    PAVL node = *a;
    if(search(node, id)){
        node->elt.cons += new_cons;
        return 1;
    }
    return 0;
}


void ProcessFile(const char *filename, PAVL *tree, int *h) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Couldn't open the file");
        exit(2);
    }

    char *buffer = malloc(SIZE * sizeof(char));
    if (buffer == NULL) {
        perror("Memory allocation for buffer failed");
        fclose(file);
        exit(3);
    }

    long id, capacity, cons;

    fgets(buffer, SIZE, file); // Skip the first line

    while (fgets(buffer, SIZE, file) != NULL) {
        id = 0;
        capacity = -1;
        cons = 0;

        int nbtokens = sscanf(buffer, "%ld;%ld;%ld", &id, &capacity, &cons);
        if (nbtokens == 3) {
            printf("Processing id: %ld, capacity: %ld, consumption: %ld\n", id, capacity, cons);
            if (!updateCapacity(tree, id, capacity)) {
                Station *newStation = createStation(id, capacity, cons);
                *tree = AVLinsertion(*tree, *newStation, h);
            }
            if (!addConsumption(tree, id, cons)) {
                Station *newStation = createStation(id, capacity, cons);
                *tree = AVLinsertion(*tree, *newStation, h);
            }
        } else {
            fprintf(stderr, "Invalid line format in file: %s\n", buffer);
        }
    }

    free(buffer);
    fclose(file);
}


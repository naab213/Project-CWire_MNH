#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treatment.h"
#include "tree.h"
#include "balance.h"
#include "track.h"


int search(PAVL a, int id){
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

int updateCapacity(PAVL* a, int id, int new_capacity){
    PAVL node = *a;
    if(search(node, id)){ 
        node->elt.capacity = malloc(sizeof(int));
        if(node->elt.capacity != NULL) {
            *(node->elt.capacity) = new_capacity;
            return 1;
        }
    return 0;
    }
}


int addConsumption(PAVL* a, int id, long new_cons) {
    PAVL node = *a;
    if(search(node, id)){
        node->elt.cons += new_cons;
        return 1;
    }
    return 0;
}


void ProcessFile(const char *filename, PAVL *tree, int *h){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Couldn't open the file %s.\n", filename);
        exit(2);
    }

    char *buffer = malloc(SIZE * sizeof(char));
    if (buffer == NULL) {
        printf("Memory allocation for buffer failed.\n");
        exit(3);
    }

    int id, capacity;
    long cons;

    while(fgets(buffer, SIZE, file)){
        //buffer[strcspn(buffer, "\n")] = 0;

        char *token = strtok(buffer, ";");
        id = 0;
        cons = 0;
        capacity = -1;

        int nbColumn = 0; 
        while(token != NULL){
            if(nbColumn == 0){
                id = atoi(token);  // Le premier token est l'ID
            }
            else if(nbColumn == 1){
                if(strcmp(token, "-") != 0){
                    capacity = atoi(token);
                }
            }
            else{
                if(strcmp(token, "-") != 0){
                    cons += atol(token);  // Ajouter les autres tokens à la consommation
                }
            }
            nbColumn++;
            token = strtok(NULL, ";");
        }


        if(nbColumn >= 3){
            if(capacity != -1){
                if(!updateCapacity(tree, id, capacity)){
                    Station* newStation = createStation(id, capacity, cons);
                    *tree = AVLinsertion(*tree, *newStation, h);
                }
            }
            if(!addConsumption(tree, id, cons)){
                Station* newStation = createStation(id, capacity, cons);
                *tree = AVLinsertion(*tree, *newStation, h);
            }
        }
        else{
            printf("Invalid line format in file.\n");
        }
    }

    free(buffer);
    fclose(file);
}

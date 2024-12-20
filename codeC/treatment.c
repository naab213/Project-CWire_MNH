#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treatment.h"
#include "tree.h"
#include "balance.h"
#include "track.h"


PAVL search(PAVL a, long id) {
    while (a != NULL) {
        if (*(a->elt.id_station) == id) {
            return a; // Retourne le nœud correspondant
        } else if (id < *(a->elt.id_station)) {
            a = a->fg; // Aller à gauche
        } else {
            a = a->fd; // Aller à droite
        }
    }
    return NULL; // Retourne NULL si l'ID n'est pas trouvé
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
    PAVL node = search(*a, id); // Recherche du nœud correspondant

    if (node != NULL) {
        // Mise à jour de la consommation
        *(node->elt.cons) += new_cons;
        return 1; // Succès
    }

    return 0; // Échec : nœud non trouvé
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
            if (!updateCapacity(tree, id, capacity) || !addConsumption(tree, id, cons)) {
                Station *newStation = createStation(id, capacity, cons);
                *tree = AVLinsertion(*tree, *newStation, h);
            }
            
        } else {
            printf("Invalid line format in file: %s\n", buffer);
        }
    }

    free(buffer);
    fclose(file);
}

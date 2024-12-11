#ifndef TREATMENT_H
#define TREATMENT_H

#include "tree.h"
#include "balance.h"
#include "track.h"

#define SIZE 256

int search(PAVL a, int id);
int updateCapacity(PAVL* a, int id, int new_capacity);
int addConsumption(PAVL *a, int id, long new_cons);
void ProcessFile(const char *filename, PAVL *tree, int *h);

#endif // TREATMENT_H

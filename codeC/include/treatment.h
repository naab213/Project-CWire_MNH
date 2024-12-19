#ifndef TREATMENT_H
#define TREATMENT_H

#include <stdio.h>
#include "tree.h"
#include "balance.h"
#include "track.h"

#define SIZE 100000
#define TOK 64

int search(PAVL a, long id);
int updateCapacity(PAVL* a, long id, long new_capacity);
int addConsumption(PAVL *a, long id, long new_cons);
void ProcessFile(const char *filename, PAVL *tree, int *h);

#endif // TREATMENT_H

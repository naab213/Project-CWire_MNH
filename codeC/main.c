#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treatment.h"
#include "track.h"


int main(int argc, char *argv[]){
    /*if(argc != 4){
        printf("Too many/few arguments! There must be 3 !!\n");
        exit(1);
    }*/

    const char *filename = argv[1];
    printf("%s", argv[1]);
    const char *final = argv[2];
    PAVL tree = NULL;
    int h = 0;

    ProcessFile(filename, &tree, &h);


    FILE *file = fopen(final, "w");
    if (file == NULL) {
        printf("Failed to open file %s for writing.\n", final);
        exit(1);
    }

    fillCSV(tree, file);

    fclose(file);
    return 0;
}
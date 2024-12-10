#include "treatment.h"
#include "track.h"


int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Too many/few arguments! There must be 2 !!\n");
        exit(1);
    }

    const char *filename = argv[1];
    PAVL tree = NULL;
    int h = 0;

    ProcessFile(filename, &tree, &h);

    return 0;
}

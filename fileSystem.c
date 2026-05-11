#include <string.h>
#include <stdlib.h>
#include "fileSystem.h"

// creates a new file identifier struct
File *createFile(char *name, int score){
    File *newFile = malloc(sizeof(struct File));
    newFile->score = score;
    newFile->id = malloc(strlen(name) + 1);
    strcpy(newFile->id, name);
    return newFile;
}
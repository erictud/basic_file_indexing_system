#ifndef FILE
#define FILE

typedef struct File {
    int score;
    char *id;
} File;

// creates a new file identifier struct
File *createFile(char *name, int score);

#endif
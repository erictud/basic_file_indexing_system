/* Tudorica Eric Emanuel - 313CCa */

#include "lists.h"
#include "trie.h"
#include <stdio.h>

#ifndef FILE_FUNC
#define FILE_FUNC

typedef struct File {
    int score;
    char *id;
} File;

// creates a new file identifier struct
File *createFile(char *name, int score);
// sorts a list of file stored as pointer nodes by names
void sortFilesByName(List *list);
// displays all the keywords (returns 1 if printed something)
int showKeyWords(TrieNode *root, char *keyword, int pos, FILE *outputFilePtr);
// cmp two file structs based on name
int cmpFiles(void *content, void *refContent);
// cmp two nodes based on the file content that they are holding
int cmpNodes(void *node1, void *node2);
// compares two files based on relevance score; if the score is equal, the compares lexicographically
int cmpFilesByPriority(File f1, File f2);
// frees the contents of a file
void freeFile(void *f);

#endif
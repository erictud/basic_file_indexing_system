/* Tudorica Eric Emanuel - 313CCa */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fileSystem.h"
#include "lists.h"
#include "trie.h"


// creates a new file identifier struct
File *createFile(char *name, int score){
    File *newFile = malloc(sizeof(struct File));
    newFile->score = score;
    newFile->id = malloc(strlen(name) + 1);
    strcpy(newFile->id, name);
    return newFile;
}

// sorts a list of files stored as nodes by names
void sortFilesByName(List *list){
    // a list with < 2 elem shouldnt be sorted
    if(!list->head || !list->head->next) 
        return;

    // bubble sort
    Node *p, *q;
    for(p = list->head; p->next != NULL; p = p->next){
        for(q = p->next; q != NULL; q = q->next){
            File *file1 = ((File *)((Node *)p->content)->content);
            File *file2 = ((File *)((Node *)q->content)->content);

            // file name is the criteria of cmp
            if(strcmp(file1->id, file2->id) > 0){ 
                void *temp = p->content;
                p->content = q->content;
                q->content = temp;
            }
        }
    }
}

// compares to files by names
int cmpFiles(void *content, void *refContent){
    char *id = ((File *)content)->id;
    char *idRef = ((File *)refContent)->id;
    return strcmp(id, idRef) == 0;
}

// compares two nodes who contains a 
int cmpNodes(void *node1, void *node2){
    File *f1 = (File *)(((Node *)node1)->content);
    File *f2 = (File *)(((Node *)node2)->content);
    char *id1 = f1->id;
    char *id2 = f2->id;
    return strcmp(id1, id2) == 0;
}

// compares two files based on relevance score
// the score is equal, the compares lexicographically
int cmpFilesByPriority(File f1, File f2){
    if(f1.score > f2.score)
        return 1;
    else if(f1.score == f2.score && strcmp(f1.id, f2.id) < 0) // relevance is eq
        return 1;
    return 0;
}

// prints all keywords in aphabetical order followed by details
int showKeyWords(TrieNode *root, char *keyword, int pos, FILE *outputFilePtr){
    int printed = 0;
    // end of keyword
    if (root->numOfWords != 0) {
        printed = 1;
        keyword[pos] = '\0';
        fprintf(outputFilePtr, "%s %d ", keyword, root->numOfWords); 
        // printing every file name that has the current keyword
        Node *p = root->listOfNodes->head;
        while(p != NULL){
            char *name = ((File *)(((Node *)p->content))->content)->id;
            fprintf(outputFilePtr, "%s ", name);
            p = p->next;
        }
        fprintf(outputFilePtr, "\n");
    }
    
    // iterating through every letter
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            // adding letter
            keyword[pos] = i + 'a';
            
            if(showKeyWords(root->children[i], keyword, pos + 1, outputFilePtr))
                printed = 1; // remember that something is printed
        }
    }
    return printed;
}
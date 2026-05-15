/* Tudorica Eric Emanuel - 313CCa */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// custom headers
#include "lists.h"
#include "trie.h"
#include "fileSystem.h"
#include "heap.h"

int main(){
    // Input files
    FILE *inputFile = fopen("indexare.in", "r");
    FILE *outputFile = fopen("indexare.out", "w");

    // Initializing data structures
    List *fileSystemList = createList();
    TrieNode *keywordTrieRoot = createTrieNode();

    // Getting input - reading every operations
    int numOfOperations;
    char operation[21];
    fscanf(inputFile, "%d", &numOfOperations);
    for(int i = 0; i < numOfOperations; i++){
        fscanf(inputFile, "%s", operation);

        // add - create a new node in fileSystemList
        //     - put all the keywords in the trie (keywordTrieRoot)
        if(strcmp(operation, "ADD") == 0){
            // creating new file
            char fileName[101], keyword[101];
            int score, numOfKeywords;
            fscanf(inputFile, "%s %d %d", fileName, &score,  &numOfKeywords);
            File *newFile = createFile(fileName, score);

            // checking if exists
            if(existsNode(fileSystemList, cmpFiles, newFile)){
                // already exists -> freeing up mem and continuing
                fprintf(outputFile, "EXISTS\n");
                free(newFile->id);
                free(newFile);
                // reading buffer
                for(int j = 0; j < numOfKeywords; j++)
                    fscanf(inputFile, "%s", keyword);
                continue;
            }

            // adding to the list
            Node *referenceNode = addNode(fileSystemList, (void *)newFile);

            // adding keywords to trie
            for(int j = 0; j < numOfKeywords; j++){
                fscanf(inputFile, "%s", keyword);
                TrieNode *terminalLetter = addWord(keywordTrieRoot, keyword, referenceNode);

                // refernces to files with a keyword need to be ordered => sort them after 
                // every keyword insert
                sortFilesByName(terminalLetter->listOfNodes);
            }

            // printing succes message
            fprintf(outputFile, "OK\n");
        } else if(strcmp(operation, "DEL") == 0){
            char fileName[101];
            fscanf(inputFile, "%s", fileName);

            // finding the file that needs to be deleted
            File *newFile = createFile(fileName, -1); // creating file struct in order to compare
            Node *nodeToBeDeleted = existsNode(fileSystemList, cmpFiles, newFile);
            free(newFile);
            if(!nodeToBeDeleted){ // doesn't exist, we move on
                fprintf(outputFile, "NOT FOUND\n");
                continue;
            }

            // deleting references of the file from the keyword trie 
            removeRefrenceWord(keywordTrieRoot, cmpNodes, nodeToBeDeleted);

            // cleaning keyword trie
            cleanupTrie(keywordTrieRoot);

            // deleting file from the list
            removeNode(fileSystemList, cmpFiles, nodeToBeDeleted->content);

            // printing succes message
            fprintf(outputFile, "OK\n");
        } else if(strcmp(operation, "ADDKW") == 0){
            char fileName[101], keywordToBeAdded[101];
            fscanf(inputFile, "%s %s", fileName, keywordToBeAdded);

            // finding the file with the id given
            File *newFile = createFile(fileName, -1); // creating file struct in order to compare
            Node *refNode = existsNode(fileSystemList, cmpFiles, newFile);
            free(newFile);
            if(!refNode){ // doesn't exist, we move on
                fprintf(outputFile, "NOT FOUND\n");
                continue;
            }

            // adding the keyword
            TrieNode *terminalLetter = addWord(keywordTrieRoot, keywordToBeAdded, refNode);
            sortFilesByName(terminalLetter->listOfNodes); // sorting list of keywords

            // printing succes message
            fprintf(outputFile, "OK\n");           
        } else if(strcmp(operation, "DELKW") == 0){
            char fileName[101], keywordToBeDeleted[101];
            fscanf(inputFile, "%s %s", fileName, keywordToBeDeleted);

            // finding the file with the id given
            File *newFile = createFile(fileName, -1); // creating file struct in order to compare
            Node *refNode = existsNode(fileSystemList, cmpFiles, newFile);
            free(newFile);
            if(!refNode){ // doesn't exist, we move on
                fprintf(outputFile, "NOT FOUND\n");
                continue;
            }

            // removing the keyword reference
            removeKeyword(keywordTrieRoot, cmpNodes, refNode, keywordToBeDeleted, 0);

            // removing all the nodes from the trie that dont point to anything
            cleanupTrie(keywordTrieRoot);

            // printing succes message
            fprintf(outputFile, "OK\n");
        } else if(strcmp(operation, "FIND") == 0){
            char keyword[101];
            fscanf(inputFile, "%s", keyword);
            // iterating throught the trie and printing the ref nodes
            int res = printReferencedFiles(keywordTrieRoot, keyword, 0, outputFile);

            // err msg if there s nothing to print
            if(res == -1){
                fprintf(outputFile, "EMPTY\n");
            }
        }else if(strcmp(operation, "TOPK") == 0){
            // getting input
            char keyword[101];
            int k;
            fscanf(inputFile, "%s %d", keyword, &k);

            // gets the terminal letter node of the keyword
            TrieNode *lastLetter = findLastLetterNode(keywordTrieRoot, keyword, 0);

            // check if the keyword exists
            if(!lastLetter || lastLetter->numOfWords == 0){
                fprintf(outputFile, "EMPTY\n");
                continue;
            }

            // init the max-heap of elements from the lastLetter
            Heap *keywordHeap = initHeap(lastLetter->numOfWords);

            // constructs the heap that is formed by the files that are referenced
            Node *p = lastLetter->listOfNodes->head;
            while(p != NULL){
                File *f = (File *)((Node *)p->content)->content;
                insertHeap(keywordHeap, *f, cmpFilesByPriority);
                p = p->next;
            }

            // extracts the k elements (if there are less than k elem, we show all the elem)
            int ind = k > lastLetter->numOfWords ? lastLetter->numOfWords : k; 
            fprintf(outputFile, "%d ", ind); // prints the num 
            for(int i = 0; i < ind; i++){
                File f = extractMax(keywordHeap, cmpFilesByPriority);
                fprintf(outputFile, "%s ", f.id);
            }
            fprintf(outputFile, "\n");

            // free mem
            freeHeap(&keywordHeap);

        } else if(strcmp(operation, "PREFIX") == 0){
            char prefix[101];
            fscanf(inputFile, "%s", prefix);

            // getting the root node in the trie of the last prefix letter
            TrieNode *root = findLastLetterNode(keywordTrieRoot, prefix, 0);

            if(!root){ // the prefix doesnt exist
                fprintf(outputFile, "EMPTY\n");
                continue;
            }
            
            // creating a list that contains all the files with a keyword with the prefix
            List *filesWithPrefix = createList();
            getAllRefrencedNodes(root, filesWithPrefix);

            // iterating through the list and printing files
            fprintf(outputFile, "%d ", filesWithPrefix->len);
            Node *p = filesWithPrefix->head;
            while(p != NULL){
                File *f1 = (File *)(((Node *)p->content)->content);
                fprintf(outputFile, "%s ", f1->id);
                p = p->next;
            }
            fprintf(outputFile, "\n");
        } else if(strcmp(operation, "PRINT") == 0){
            char keyword[101];
            int showsSomething = showKeyWords(keywordTrieRoot, keyword, 0, outputFile);
            // prints empty if the trie doesnt have keywords
            if(showsSomething == 0){
                fprintf(outputFile, "EMPTY\n");
            }
        }
    }

    // FREE memory
    freeList(&fileSystemList, freeFile);
    freeTrie(keywordTrieRoot);
}
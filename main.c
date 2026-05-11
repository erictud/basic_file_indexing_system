#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// custom headers
#include "lists.h"
#include "trie.h"
#include "fileSystem.h"

int main(){
    // Initializing data structures
    List *fileSystemList = createList();
    TrieNode *keywordTrieRoot = createTrieNode();

    // Getting input - reading every operations
    int numOfOperations;
    char operation[21];
    scanf("%d", &numOfOperations);

    for(int i = 0; i < numOfOperations; i++){
        scanf("%s", operation);

        // add - create a new node in fileSystemList
        //     - put all the keywords in the trie (keywordTrieRoot)
        if(strcmp(operation, "ADD") == 0){
            char fileName[21], keyword[41];
            int score, numOfKeywords;

            scanf("%s %d", fileName, &score);
            File *newFile = createFile(fileName, score);
            // adding to the list
            Node *referenceNode = addNode(fileSystemList, (void *)newFile);

            // reading keywords and adding to trie
            scanf("%d", &numOfKeywords);
            for(int j = 0; j < numOfKeywords; j++){
                scanf("%s", keyword);
                addWord(keywordTrieRoot, keyword, referenceNode);
            }

            // printing succes message
            printf("OK\n");
        }
    }
}
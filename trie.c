#include <stdlib.h>
#include <string.h>
#include "trie.h"

// creates an initially empty node 
TrieNode *createTrieNode(){
    TrieNode *node = malloc(sizeof(struct TrieNode));
    for(int i = 0; i < 25; i++)
        node->children[i] = NULL;
    node->listOfNodes = NULL;
    node->numOfWords = 0;
    return node;
}

// adds a node to the trie and links the last letter to a node from a linked list
void addWord(TrieNode *root, char *word, Node *referenceNode){
    TrieNode *p = root;
    // iterating every letter & creating node if neccesary
    for(int i = 0; i < strlen(word); i++){
        int letterIndex = word[i] - 'a';
        if(p->children[letterIndex] == NULL){
            p->children[letterIndex] = createTrieNode();
        }
        p = p->children[letterIndex];
        // linking last letter node to the reference node from the list
        if(i == strlen(word) - 1){
            p->numOfWords++;
            p->listOfNodes = realloc(p->listOfNodes, p->numOfWords * sizeof(struct Node *));
            p->listOfNodes[p->numOfWords-1] = referenceNode;

        }
    }
}
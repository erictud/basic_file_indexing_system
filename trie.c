#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "lists.h"
#include "fileSystem.h"

// creates an initially empty node 
TrieNode *createTrieNode(){
    TrieNode *node = malloc(sizeof(struct TrieNode));
    for(int i = 0; i < 26; i++)
        node->children[i] = NULL;
    node->listOfNodes = createList();
    node->numOfWords = 0;
    return node;
}

// adds a node to the trie and links the last letter to a node from a linked list
TrieNode *addWord(TrieNode *root, char *word, Node *referenceNode){
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
            addNode(p->listOfNodes, referenceNode);
        }
    }
    return p;
}

// Removes the refrence of a file node from the tree
void removeRefrenceFromWord(TrieNode *root, int (*cmp)(void *, void *), Node *nodeToBeDeleted){
    // checking if the terminal node containts a ref to the file
    if(root->numOfWords != 0 && existsNode(root->listOfNodes, cmp, nodeToBeDeleted)){
        // deleting the reffrence
        removeNode(root->listOfNodes, cmp, nodeToBeDeleted);
        root->numOfWords--;
    }

    // iterating through every child
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            removeRefrenceFromWord(root->children[i], cmp, nodeToBeDeleted);
        }
    }
}

// removes all the nodes in the trie that dont serve a meaning
int cleanupTrie(TrieNode *root) {
    if (!root) return 1;
    if (root->numOfWords != 0) {
        return 0; // node is stil useful bc it contains a ref
    }

    // check children 
    int has_children = 0;
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            if (cleanupTrie(root->children[i])) {
                free(root->children[i]);
                root->children[i] = NULL; 
            } else {
                has_children = 1; // means is a prefix
            }
        }
    }

    // if it has no active children it can be deleted
    if (!has_children) {
        return 1; 
    }
    return 0; 
}
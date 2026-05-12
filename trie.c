#include <stdlib.h>
#include <stdio.h>
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
        if(i == strlen(word) - 1 && !existsNode(p->listOfNodes, cmpNodes, referenceNode)){
            p->numOfWords++;
            addNode(p->listOfNodes, referenceNode);
        }
    }
    return p;
}

// Based on a keyword, it prints the names of all files referenced in the last node
int printReferencedFiles(TrieNode *root, char *keyword, int lvl, FILE *outputFile){
    // arrived to the last node
    if(lvl == strlen(keyword) - 1) {
        root = root->children[keyword[lvl] - 'a']; 
        if(!root || root->numOfWords == 0) // keyword doesnt exist
            return -1;
        Node *p = root->listOfNodes->head;
        fprintf(outputFile, "%d ", root->numOfWords);
        while(p != NULL){
            File *f = (File *)((Node *)p->content)->content;
            fprintf(outputFile, "%s ", f->id);
            p = p->next;
        }
        fprintf(outputFile, "\n");
        return 1;
    } else {
        int ind = keyword[lvl] - 'a';
        if(root->children[ind] == NULL){ // keyword doesnt exist
            return -1;
        }
        else
            return printReferencedFiles(root->children[ind], keyword, lvl+1, outputFile);
    }
    return -1;
}

// Removes the refrence of a file node from the tree
void removeRefrenceWord(TrieNode *root, int (*cmp)(void *, void *), Node *nodeToBeDeleted){
    // checking if the terminal node containts a ref to the file
    if(root->numOfWords != 0 && existsNode(root->listOfNodes, cmp, nodeToBeDeleted)){
        // deleting the reffrence
        removeNode(root->listOfNodes, cmp, nodeToBeDeleted);
        root->numOfWords--;
    }

    // iterating through every child
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            removeRefrenceWord(root->children[i], cmp, nodeToBeDeleted);
        }
    }
}

// Removes the refrence of a file node from one keyword
void removeKeyword(TrieNode *root, int (*cmp)(void *, void *), Node *nodeToBeDeleted, char *keyword, int lvl){
    // checking if the terminal node containts a ref to the file
    if(lvl == strlen(keyword)-1){
        int ind = keyword[lvl] - 'a';
        root = root->children[ind];
        if(root->numOfWords != 0 && existsNode(root->listOfNodes, cmp, nodeToBeDeleted)){
            // deleting the reference
            removeNode(root->listOfNodes, cmp, nodeToBeDeleted);
            root->numOfWords--;
        }
    }else{ // navigating the keyword
        int ind = keyword[lvl] - 'a';
        if(root->children[ind] == NULL){
            return;
        }
        else
            removeKeyword(root->children[ind], cmp, nodeToBeDeleted, keyword, lvl+1);
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
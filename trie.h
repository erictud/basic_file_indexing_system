#include "lists.h"

#ifndef TRIE
#define TRIE

typedef struct TrieNode {
    struct TrieNode *children[26];
    int numOfWords;
    Node **listOfNodes;
} TrieNode;

TrieNode *createTrieNode();
void addWord(TrieNode *root, char *word, Node *referenceNode);

#endif
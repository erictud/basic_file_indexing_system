#include "lists.h"

#ifndef TRIE
#define TRIE

typedef struct TrieNode {
    struct TrieNode *children[26];
    int numOfWords;
    List *listOfNodes;
} TrieNode;

// creates a trie node
TrieNode *createTrieNode();
// adds an word to the trie and a reffrence in the terminal node
TrieNode *addWord(TrieNode *root, char *word, Node *referenceNode);
// removes all the refrences to a file from the trie
void removeRefrenceFromWord(TrieNode *root, int (*cmp)(void *, void *), Node *nodeToBeDeleted);
// deletes the nodes in the trie that have no file to point to
int cleanupTrie(TrieNode *root);

#endif
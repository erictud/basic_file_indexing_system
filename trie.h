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
void removeRefrenceWord(TrieNode *root, int (*cmp)(void *, void *), Node *nodeToBeDeleted);
// deletes the nodes in the trie that have no file to point to
int cleanupTrie(TrieNode *root);
//
void removeKeyword(TrieNode *root, int (*cmp)(void *, void *), Node *nodeToBeDeleted, char *keyword, int lvl);
//
int printReferencedFiles(TrieNode *root, char *keyword, int lvl, FILE *outputFile);
// based on a word, it finds the last letter node
TrieNode *findLastLetterNode(TrieNode *root, char *keyword, int lvl);
// gets all the unique referenced nodes from a trie
void getAllRefrencedNodes(TrieNode *root, List *nodesList);
#endif
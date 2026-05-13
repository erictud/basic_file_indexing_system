/* Tudorica Eric Emanuel - 313CCa */

#ifndef LIST
#define LIST

typedef struct Node {
    struct Node *next, *prev;
    void *content;
} Node;

typedef struct List {
    int len;
    struct Node *head, *tail;
} List;

// creates empty list
List *createList(); 
// adds node to list
Node *addNode(List *list, void *content);
// checks if a nodes exists based on a function 
Node *existsNode(List *list, int (*cmp)(void *, void *), void *contentRef);
// removes node from list based on a comparing function
void removeNode(List *list, int (*cmp)(void *, void *), void *cmpContent);
// frees memory from a list
void freeList(List **list, void (*freeContent)(void *));

#endif
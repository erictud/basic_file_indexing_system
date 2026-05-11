#ifndef LIST
#define LIST

typedef struct Node {
    struct Node *next;
    void *content;
} Node;

typedef struct List {
    int len;
    struct Node *head;
} List;

//creates empty list
List *createList(); 
// adds node to list
void addNode(List *list, void *content);
// removes node from list based on a comparing function
void removeNode(List *list, int (*cmp)(void *, void *), void *cmpContent);
// frees memory from a list
void freeList(List **list, void (*freeContent)(void *));

#endif
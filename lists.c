#include <stdlib.h>
#include "lists.h"

// creates an empty list
List *createList(){
    List *newList = malloc(sizeof(struct List));
    newList->len = 0;
    newList->head = NULL;
    return newList;
}

// creates a new Node
Node *createNode(void *content){
    Node *newNode = malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->content = content;
    return newNode;
}

// adds new node
Node *addNode(List *list, void *content){
    Node *newNode = createNode(content);
    if(!list->head) // adds first node
        list->head = newNode;
    else{ // adds another node
        list->head->next = newNode;
        list->head = newNode;
    }
    list->len++;
    return newNode;
}
 
// removes an element based on a comparison function passed as param
void removeNode(List *list, int (*cmp)(void *, void *), void *cmpContent){
    Node *p = list->head, *prev = NULL;
    while(p != NULL){
        if(cmp(p->content, cmpContent) == 1){ 
            // found element that needs to be deleted
            if(prev == NULL)
            list->head = list->head->next;
            else
            prev->next = p->next;

            free(p);
            list->len--;
        }
        prev = p;
        p = p->next;
    }

}

// frees list, including the node's contents using an aux function
void freeList(List **list, void (*freeContent)(void *)){
    Node *p = (*list)->head, *prev;
    while(p != NULL){
        prev = p;
        p = p->next;
        // freeing mem
        freeContent(prev->content);
        free(prev->content);
        free(prev);
    }
    free(*list);
    *list = NULL;
}
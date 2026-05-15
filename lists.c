/* Tudorica Eric Emanuel - 313CCa */

#include <stdlib.h>
#include "lists.h"

// creates an empty list
List *createList(){
    List *newList = malloc(sizeof(struct List));
    newList->len = 0;
    newList->head = newList->tail = NULL;
    return newList;
}

// creates a new Node
Node *createNode(void *content){
    Node *newNode = malloc(sizeof(struct Node));
    newNode->next = newNode->prev = NULL;
    newNode->content = content;
    return newNode;
}

// adds new node
Node *addNode(List *list, void *content){
    Node *newNode = createNode(content);
    if(!list->head) // list is empty
        list->head = list->tail = newNode;
    else{ // adds to end
        newNode->prev = list->tail;
        newNode->next = NULL;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->len++;
    return newNode;
}
 
// checks if a node exists based on a comparing function
Node *existsNode(List *list, int (*cmp)(void *, void *), void *contentRef){
    Node *p = list->head;
    while(p){
        if(cmp(p->content, contentRef) == 1)
            return p;
        p = p->next;
    }
    return NULL;
}

// removes an element based on a comparison function passed as param
void removeNode(List *list, int (*cmp)(void *, void *), void *cmpContent){
    Node *p = list->head;
    while(p != NULL){
        if(cmp(p->content, cmpContent) == 1){ 
            // found element that needs to be deleted
            if(p->next == NULL){ // del last node
                if(list->head == list->tail) // del the only one node
                    list->head = list->tail = NULL;
                else{
                    list->tail = list->tail->prev;
                    list->tail->next = NULL;
                }
            }else if(p->prev == NULL){ // del first node
                list->head = list->head->next;
                list->head->prev = NULL;
            }else{
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }
            free(p);
            return;
        }
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
        if(freeContent){
            freeContent(prev->content);
        }
        free(prev);
    }
    free(*list);
    *list = NULL;
}
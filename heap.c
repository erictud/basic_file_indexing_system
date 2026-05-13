/* Tudorica Eric Emanuel - 313CCa */

#include <stdlib.h>
#include "heap.h"

// initializes an empty heap
Heap *initHeap(int maxHeapSize){
    Heap *h = malloc(sizeof(Heap));
    h->maxHeapSize = maxHeapSize;
    h->size = 0;
    h->elem = malloc((maxHeapSize+1) * sizeof(File)); // heap si 1 indexed
    return h;
}

// gets the parent of a node in the heap
int getParent(int i){
    return i/2;
}

// gets the left child in the heap
int getLeftChild(int i){
    return 2 * i;
}

// gets the right child in the heap
int getRightChild(int i){
    return 2 * i + 1;
}

// moves the node up in the heap until its a parent of a lesser priority node
void SiftUp(Heap *h, int pos, int (*cmp)(File elem1, File elem2)){
    if(pos == 1)
        return;
    int parentInd = getParent(pos);
    // interchanging based on cmp func
    if(cmp(h->elem[pos], h->elem[parentInd])){
        File aux = h->elem[pos];
        h->elem[pos] = h->elem[parentInd];
        h->elem[parentInd] = aux;
    }
    SiftUp(h, parentInd, cmp);
}

// inserts an element into a max-heap
void insertHeap(Heap *h, File elem, int (*cmp)(File elem1, File elem2)){
    if(h->size == h->maxHeapSize)
        return; // no more space to add elements
    
    h->size++;
    h->elem[h->size] = elem;
    SiftUp(h, h->size, cmp);
}



// moves a node in the heap in order to still have the max heap priority
void SiftDown(Heap *h, int pos, int (*cmp)(File elem1, File elem2)) {
    int maxInd = pos;
    int left = getLeftChild(pos); // 2 * pos
    if(left <= h->size && cmp(h->elem[left], h->elem[maxInd]))
        maxInd = left;
    int right = getRightChild(pos); // 2 * pos + 1
    if(right <= h-> size && cmp(h->elem[right], h->elem[maxInd]))
        maxInd = right;
    if(pos != maxInd) {
        File aux = h->elem[maxInd];
        h->elem[maxInd] = h->elem[pos];
        h->elem[pos] = aux;
        SiftDown(h, maxInd, cmp);
    }
}

// extracts the maximum element, whose priority is determined by the cmp func
File extractMax(Heap *h, int (*cmp)(File elem1, File elem2)){
    File res = h->elem[1];
    h->elem[1] = h->elem[h->size];
    h->size--;
    SiftDown(h, 1, cmp);
    return res;
}


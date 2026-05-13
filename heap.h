/* Tudorica Eric Emanuel - 313CCa */

#include "fileSystem.h"

#ifndef HEAP
#define HEAP

typedef struct Heap {
    int size, maxHeapSize;
    File *elem;
} Heap;

// initializes an empty heap
Heap *initHeap(int maxHeapSize);
// inserts an element into a max-heap
void insertHeap(Heap *h, File elem, int (*cmp)(File elem1, File elem2));
// extracts the maximum element, whose priority is determined by the cmp func
File extractMax(Heap *h, int (*cmp)(File elem1, File elem2));

#endif
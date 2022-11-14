#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize){
	//TODO:
	PriQueue *heap = malloc(sizeof(PriQueue));
	heap->elem = (ItemType *)malloc(sizeof(ItemType));
	heap->size = 0;
	heap->maxHeapSize = maxHeapSize;
	return heap;
}

int getLeftChild(int i){
	//TODO:
	return 2 * i + 1;
}

int getRightChild(int i) {
	//TODO:
	return 2 * i + 2;
}

int getParent(int i) {
	//TODO:
	return (i - 1) / 2;
}

ItemType getMax(APriQueue h) {
	//TODO:
	return h->elem[0];
}

void siftUp(APriQueue h, int idx) {
	//TODO:
	ItemType aux;
	int Parent = getParent(idx);
	while(idx >= 0 && h->elem[idx].prior > h->elem[Parent].prior){
		aux = h->elem[Parent];
		h->elem[Parent] = h->elem[idx];
		h->elem[idx] = aux;
		idx = Parent;
		Parent = getParent(idx);
	}
}


void insert(PriQueue *h, ItemType x) {
	//TODO:
	if(h->size <= h->maxHeapSize){
		h->maxHeapSize = h->maxHeapSize * 2;
		h->elem = (ItemType*)realloc(h->elem, h->maxHeapSize * sizeof(ItemType));
	}
	h->elem[h->size] = x;
	siftUp(h, h->size);
	h->size++;
}

void siftDown(APriQueue h, int idx){
	//TODO:
	int maxIndex = idx;
	int l = getLeftChild(idx);
	if(l < h->size && h->elem[maxIndex].prior < h->elem[l].prior){ 
		maxIndex = l;
	}
	int r = getRightChild(idx);
	if(r < h->size && h->elem[maxIndex].prior < h->elem[r].prior){
		if(h->elem[l].prior < h->elem[r].prior){
			maxIndex = r;
		}
	}
	if(idx != maxIndex){
		ItemType aux = h->elem[idx];
		h->elem[idx] = h->elem[maxIndex];
		h->elem[maxIndex] = aux;
		siftDown(h, maxIndex);
	}
}

void removeMax(APriQueue h) {
	//TODO:
	ItemType last = h->elem[h->size - 1];
	h->elem[0] = last;
	h->size--;
	siftDown(h, 0);
}

void freeQueue(APriQueue h){
	// TODO:
	if(h == NULL) return;
	if(h->elem != NULL){
		free(h->elem);
		h->elem = NULL;
	}
    free(h);
}

#endif


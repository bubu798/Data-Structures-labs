#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

typedef Queue TCoada;
typedef Queue *AQ;


Queue* createQueue(void){
	// TODO: Cerinta 2
	Queue *coada = malloc(sizeof(Queue));
	coada->front = NULL;
	coada->rear = NULL;
	coada->size = 0;
	return coada;
} 

int isQueueEmpty(Queue *q){
	// TODO: Cerinta 2
	if(q->front == NULL) return 1;
	return 0;
}

void enqueue(Queue *q, Item elem){
	// TODO: Cerinta 2
	QueueNode *p = malloc(sizeof(Queue));
	p->elem = elem;
	p->next = NULL;
	if(q->front == NULL){
		q->front= q->rear = p;
		q->size++;
	}
	else{
		q->rear->next = p;
		q->rear = p;
		q->size++;
	}
}

Item front(Queue* q){
	// TODO: Cerinta 2
	if(q->front == NULL) return 0;
	else return q->front->elem;
}

void dequeue(Queue* q){
	// TODO: Cerinta 2
	if(q->front == q->rear) {
		free(q->front);
		q->front = q->rear = NULL;
		q->size = 0;
	}
	else {
		QueueNode *aux = q->front;
		q->front = q->front->next;
		q->size--;
		free(aux);
	}
}

void destroyQueue(Queue *q){
	// TODO: Cerinta 2
	free(q->front);
	free(q->rear);
	q->front = q->rear = NULL;
	q->size = 0;
}

#endif

#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



typedef struct StackNode{
	Item elem;
	struct StackNode *next;
}StackNode;

typedef StackNode TCelSt; // Redenumirea unui nod la notatiile din curs 
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
}Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;//  // Redenumirea unui pointer la stiva la notatiile din curs

Stack* createStack(void){
	// TODO: Cerinta 1
	Stack *stiva = malloc(sizeof(Stack));
	stiva->head = NULL;
	stiva->size = 0;
	return stiva;
}

int isStackEmpty(Stack* stack){
	// TODO: Cerinta 1
	if(stack->head == NULL) return 1;
	return 0;
}

void push(Stack *stack, Item elem){
	// TODO: Cerinta 1
	StackNode *new_elem = malloc(sizeof(Stack));
	new_elem->elem = elem;
	new_elem->next = stack->head;
	stack->head = new_elem;
	stack->size++;
}

Item top(Stack *stack){	
	// TODO: Cerinta 1
	if(stack->head == NULL) return 0;
	else return stack->head->elem;
} 

void pop(Stack *stack){
	// TODO: Cerinta 1
	StackNode *aux = stack->head;
	stack->head = stack->head->next;
	stack->size--;
	free(aux);
}

void destroyStack(Stack *stack){
	// TODO: Cerinta 1
	StackNode *aux;
	while(stack->head != NULL) {
		aux = stack->head;
		stack->head = stack->head->next;
		free(aux);
	}
	stack->head = NULL;
	stack->size = 0;
}

#endif 

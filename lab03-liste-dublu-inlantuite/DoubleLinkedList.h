#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new node
 *  [input]: Item
 *  [output]: List*
 */
ListNode *createNode(Item elem) {
	// TODO: Cerinta 1a
	ListNode *node = malloc(sizeof(List));
	node -> elem = elem;
	node -> prev = NULL;
	node -> next = NULL;
	return node;
}

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	// TODO: Cerinta 1a
	List *lista = malloc(sizeof(List));
	lista -> first = NULL;
	lista -> last = NULL;
	return lista;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	// TODO: Cerinta 1b
	if(list -> first == NULL && list -> last == NULL) return 1;
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	// TDOO: Cerinta 1c
	ListNode *curr = list -> first;
	while(curr != NULL) {
		if(curr -> elem == elem) return 1;
		curr = curr -> next;
	}

	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAt(List* list, Item elem, int pos){

	// Guard against young player errors
	if(list == NULL) return;
	ListNode *new_node = createNode(elem);
	if(pos < 0 || pos > length(list)) return;
	if(isEmpty(list)) {
		list -> first = new_node;
		list -> last = new_node;
	}
	else if(pos == 0) {
		new_node -> next = list -> first;
		list -> first -> prev = new_node;
		new_node -> prev = NULL;
		list -> first = new_node;
	}
	else if(pos == length(list)) {
		list -> last -> next = new_node;
		new_node -> prev = list -> last;
		new_node -> next = NULL;
		list -> last = new_node;
	}
	else {
		ListNode *curr = list -> first;
		for(int i = 0; i < pos; ++i) {
			curr = curr -> next;
		}
		new_node -> prev = curr -> prev;
		new_node -> next = curr;
		curr -> prev -> next = new_node;
		curr -> prev = new_node;
	}
}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	// Guard against young player errors
	if(list == NULL) return;
	ListNode *curr = list->first;
	if (isEmpty(list)) return; 
	if (!contains(list, elem)) return;
	if (curr->next == NULL && curr->prev == NULL) {
		list->first = NULL;
		list->last = NULL;
		free(curr);
		return;
	}
	for (int i = 0; i < length(list); i++) {
		if (curr->elem == elem) {
			if (i == 0) {
				list->first = curr->next;
				if (list->first != NULL) 
					list->first->prev = NULL;
				else
					list->last = NULL;
				free(curr);
				return;
			} else if (i == length(list) - 1) {
				list->last = curr->prev;
				list->last->next = NULL;
				free(curr);
				return;
			} else {
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next; 
				free(curr);
				return;
			}
		
		}
		curr = curr->next;
	}
}	//TODO: Cerinta 1e
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list){
	// Guard against young player errors
	if(list == NULL) return 0;
	int len = 0;
	ListNode *curr = list -> first;
	while(curr != NULL) {
		++len;
		curr = curr -> next;
	}
	// TODO: Cerinta 1f
	return len;
}
// -----------------------------------------------------------------------------



/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
List* destroyList(List* list){
	// Guard against young player errors
	if(list == NULL) return NULL;

	//TODO: Cerinta 1g
	return NULL;
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_

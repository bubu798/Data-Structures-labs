#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
    IMPORTANT!

    As we stick to pure C, we cannot use templates. We will just asume
    some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct node {
    T value;
    struct node* next;
} TNode, *TSortedList;

// TODO : Cerința 1 & Cerința 2

TSortedList create(T value) {
    // TODO (se va completa la Cerința 2)
    TSortedList list = malloc(sizeof(TNode));
    list->value = value;
    list->next = NULL;
    return list;
}

int isEmpty(TSortedList list) {
    if(list==NULL)return 1;
    else return 0;
}

int contains(TSortedList list, T element) {
    TSortedList curr = list;
    while(curr != NULL) {
        if(curr -> value == element) return 1;
        curr = curr -> next;
    }
    return 0;
}

TSortedList insert (TSortedList list, T element) {
    if (isEmpty(list)) {
        TSortedList new_node = malloc(sizeof(TNode));
        new_node->value = element;
        new_node->next = NULL;
        return new_node;
    }
    if (element < list->value) {
        TSortedList new_node = malloc(sizeof(TNode));
        new_node->value = element;
        new_node->next = list;
        return new_node;
    }
    TSortedList prev = list;
    TSortedList curr = list;
    while (curr != NULL && element > curr -> value) {
        prev = curr;
        curr = curr -> next;
    }
    TSortedList new_node = malloc(sizeof(TNode));
    prev -> next = new_node;
    new_node -> next = curr;
    new_node -> value = element;
    return list;
}

TSortedList deleteOnce (TSortedList list, T element) {
    if(isEmpty(list)) return list;
    if(element < list -> value) {
        list = list -> next;
        return list;
    }
    TSortedList curr = list;
    TSortedList prev = list;
    while(curr != NULL) {
        prev = curr;
        curr = curr -> next;
        if(curr -> value == element) {
            prev -> next = curr -> next;
            free(curr);
            return list;
        }
    }
    return list;
}

long length (TSortedList list) {
    TSortedList current = list;
    long len = 0;
    while (current != NULL) {
        len++;
        current = current -> next;
    }
    return len;
}

T getNth(TSortedList list, int N) {
   TSortedList current = list;
   int count = 0;
   while(current != NULL) {
       if(count = N) return current -> value;
       ++ count;
       current = current -> next;
   }
}

TSortedList freeTSortedList(TSortedList list) {
    TSortedList tmp = list;
    while(list != NULL) {
        tmp = list;
        list = list -> next;
        free(tmp);
    }
}


#endif

#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

/*
  OrderedSet represents a set with elements of type T stored in memory
  in an ordered fashion.
*/

typedef struct OrderedSet {
  T* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

// -----------------------------------------------------------------------------

/*
  Function that creates an OrderedSet with elements of type T with a given
  initial capacity.
*/

OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet->size = 0;                        // initially, the set is empty
  newSet->capacity = initialCapacity;
  newSet->elements = (T*) malloc(initialCapacity * sizeof(T));

  return newSet;
}

// -----------------------------------------------------------------------------

/*
  Function that checks if an element exists in a given set. As the
  elements of the set are ordered in memory, this function uses binary
  search.

  Function returns 1 if the given element exists in the set, and 0
  otherwise.
*/

int contains(OrderedSet* set, const T element) {
  for(int i=0; i < set->size; i++) {
    if(set->elements[i] == element) return 1;
  }
  return 0;
}

// -----------------------------------------------------------------------------

/*
  Function that adds a new element to a set. If the element was
  already in the set, nothing changes. Otherwise, the element is added
  to the set. In the end, the elements must be in ascending order.
*/


void add(OrderedSet *set, const T newElement)
{
  // TODO : Cerința 2
	int ok = 0;
	if (set->size == 0)
		set->elements[set->size++] = newElement;
	else if (!contains(set, newElement))
	{
    if (set->size + 1 > set->capacity) {
      set->elements = realloc(set->elements, 2 * set->capacity * sizeof (T));
    }
		for (long idx = 0; idx < set->size && ok == 0; idx++)
		{
			if (set->elements[idx] > newElement)
			{
				for (long it = set->size; it > idx; it--)
				{
					set->elements[it] = set->elements[it - 1];
				}
				set->elements[idx] = newElement;
				ok = 1;
				set->size++;
			}
		}
		if (ok == 0)
			set->elements[set->size++] = newElement;
	}
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the union of
  the two
*/

OrderedSet* unionOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  // TODO : Cerința 3

  int ok = 0;
  for(int i=0; i<s1->size;++i) {
    for(int j=0; j<s2->size;j++){
      if(s1->elements[i]==s2->elements[j]){
        
      }
    }

  }
  return createOrderedSet(1);
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the
  intersection of the two
*/

OrderedSet* intersectOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  // TODO : Cerința 3
  return createOrderedSet(1);
}


// -----------------------------------------------------------------------------

#endif

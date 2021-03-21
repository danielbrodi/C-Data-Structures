/***********************************************
* File: list.h						 		  *
* Author: Rostik Angelevich					   *
* Date: 21/03/2021							   *
* Version: 1.0  							   *
* Reviewer: Daniel							   *
* Description: Single Linked List API		   * 
************************************************/
#ifndef	__LIST_H__
#define	__LIST_H__

#include <stddef.h>	/* size_t */

#include "utils.h"

/*typedef struct list list_ty;*/

typedef struct list_iter list_iter_ty


/* Creates an empty single-linked list and returns iterator to the head */
/* returns NULL on failure*/
/* Complexity: O(1) */
list_iter_ty *ListCreate();

/* Deletes entire List */
/* Complexity: O(n) */
void ListDestroy(list_iter_ty *iterator);

/* Returns iterator to beginning of the list */
/* Returns NULL if list is empty */
/* Complexity: O(1) */
list_iter_ty *ListIteratorBegin(list_iter_ty *iterator);

/* Returns iterator to end of the list */
/* Returns NULL if list is empty */
/* Complexity: O(1) */
list_iter_ty *ListIteratorEnd(list_iter_ty *iterator);

/* Returns iterator to next elemet in the list */
/* Returns NULL if on the last element in the list */
/* Complexity: O(1) */
list_iter_ty *ListIteratorNext(list_iter_ty *iterator);

/* Returns SUCCESS if both iterators are of the same item,
/* or FAILURE otherwise */
/* Complexity: O(1) */
status_ty ListIteratorIsEqual(const list_iter_ty *iterator_a, 
												const list_iter_ty *iterator_b);

/* Returns the element of the the iterator */
/* Returns NULL if list is empty */
/* Complexity: O(1) */
void *ListGetData(const list_iter_ty *iterator);

/* Sets the data at the iterator */
/* Undefined behaviour if list is empty */
/* Complexity: O(1) */
void ListSetData(const list_iter_ty *iterator, void *element);

/* Insters the element after the iterator */
/* Undefined behaviour if list is empty */
/* Complexity: O(1) */
void ListInsert(list_iter_ty *iterator, void *element);

/* Removes the current element from the list, */
/* the iterator will point to the next element in the list */
/* Undefined behaviour if list is empty */
/* Complexity: O(1) */
void ListRemove(list_iter_ty *iterator);

/* Returns SUCCESS if list is empty or FAILURE otherwise */
/* Complexity: O(1) */
status_ty ListIsEmpty(const list_iter_ty *iterator);

/* Returns number of elements in the list */
/* Complexity: O(1) ? */
size_t ListSize(const list_iter_ty *iterator);

/* Returns iterator to the found element, or NULL if not found */
/* Undefined behaviour if list is empty */
/* Complexity: O(n) */
list_iter_ty *ListFind(list_iter_ty *iterator, void *element);

/* Perform the function Apply on each element from iterator 'start' */
/* to iterator 'end' */
/* Returns SUCCESS if no errors, FAILURE otherwise
/* Undefined behaviour if list is empty */
/* Complexity: O(n) * O(Apply) */
status_ty ListForEach(const list_iter_ty *iterator, 
											status_ty (*Apply)(void *element), 
							const list_iter_ty *start, const list_iter_ty *end);
							 
#endif	/* __LIST_H__ */

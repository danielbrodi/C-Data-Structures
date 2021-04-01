/***********************************************
* File: dlist.h						 		   *
* Date: 01/04/2021							   *
* Version: 1.2								   *
* Description: Double Linked List API		   * 
************************************************/
#ifndef	__DLIST_H__
#define	__DLIST_H__

#include <stddef.h>	/* size_t */

#include "utils.h" /* status_ty, bolean_ty*/

typedef struct dlist dlist_ty;

typedef struct dlist_node dlist_node_ty;

typedef dlist_node_ty *dlist_iter_ty;

typedef boolean_ty (*IsMatch_Func_ty)(const void *data, void *param);

typedef status_ty (*Action_Func_ty)(void *data, void *param);

/* Creates an empty doubly-linked list and returns pointer to handler struct */
/* returns NULL on failure*/
/* Complexity: O(1) */
dlist_ty *DlistCreate(void);

/* Frees entire List */
/* Immitates Free() if dlist is NULL */
/* Complexity: O(n) */
void DlistDestroy(dlist_ty *dlist);

/* Returns iterator to first element of the list */
/* If dlist is empty returns dlist_END */
/* Complexity: O(1) */
dlist_iter_ty DlistIteratorBegin(const dlist_ty *dlist);

/* Returns iterator to the dummy end of the list */
/* Complexity: O(1) */
dlist_iter_ty DlistIteratorEnd(const dlist_ty *dlist);

/* Returns iterator to the next element in the list */
/* Returns dlist_END on the last element in the list */
/* Undefined if iter is dlist_END */
/* Complexity: O(1) */
dlist_iter_ty DlistIteratorNext(const dlist_iter_ty iter);

/* Returns iterator to the previous element in the list */
/* Undefined if iter is dlist_BEGIN */
/* Complexity: O(1) */
dlist_iter_ty DlistIteratorPrevious(const dlist_iter_ty iter);

/* Returns TRUE if both are iterators of the same item */
/* or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty DlistIteratorIsEqual(const dlist_iter_ty iter_a, 
													const dlist_iter_ty iter_b);

/* Returns the data of the iterator */
/* Undefined behaviour if iter is dlist_END */
/* Complexity: O(1) */
void *DlistGetData(const dlist_iter_ty iter);

/* Sets the data at the iterator */
/* Undefined behaviour if iter is dlist_END */
/* Complexity: O(1) */
void DlistSetData(dlist_iter_ty iter, void *data);

/* Inserts the element before the iterator, */
/* returns iterator to the new element */
/* On failure returns the same iterator */
/* Complexity: O(1) */
dlist_iter_ty DlistInsertBefore(dlist_iter_ty iter, void *data);

/* Removes the element from the list, */
/* returns iterator to the next element in the list */
/* Complexity: O(1) */
dlist_iter_ty DlistRemove(dlist_iter_ty iter);

/* Inserts a new element to the beginning of the list */
/* returns iterator to the new element on success or dlist_END on failure */
/* Complexity: O(1) */
dlist_iter_ty DlistPushFront(dlist_ty *dlist, void *data);

/* Inserts a new element to the end of the list */
/* returns iterator to the new nod on success or dlist_END on failure */
/* Complexity: O(1) */
dlist_iter_ty DlistPushBack(dlist_ty *dlist, void *data);

/* Removes an element from the beginning of the list */
/* Returns the popped element */
/* Undefined if dlist is empty */
/* Complexity: O(1) */
void *DlistPopFront(dlist_ty *dlist);

/* Removes an element from the end of the list */
/* Returns the popped element */
/* Undefined if dlist is empty */
/* Complexity: O(1) */
void *DlistPopBack(dlist_ty *dlist);

/* Returns TRUE if list is empty or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty DlistIsEmpty(const dlist_ty *dlist);

/* Returns number of elements in the list */
/* Complexity: O(n) */
size_t DlistSize(const dlist_ty *dlist);

/* Returns the first iterator to the found element */
/* in range of [from_iter, to_iter) */
/* returns to_iter if data not found */
/* Complexity: O(n) */
dlist_iter_ty DlistFind(const dlist_iter_ty from_iter, 
								const dlist_iter_ty to_iter, 
										IsMatch_Func_ty match_func,
												void *param);
						
/* Stores each matching data in an element in dlist_output, */
/* in range of [from_iter, to_iter) */
/* Returns the number of matches */
/* returns 0 if data not found */
/* Complexity: O(n) */
size_t DlistMultiFind(const dlist_iter_ty from_iter, 
								const dlist_iter_ty to_iter, 
									IsMatch_Func_ty match_func, void *param,
														dlist_ty *dlist_output);
			
/* Perform the function Action_Func on each element in range, */
/* [from_iter, to_item) until failure */
/* Returns SUCCESS if no errors, FAILURE otherwise */
/* Complexity: O(n) */
status_ty DlistForEach(dlist_iter_ty from_iter,
			const dlist_iter_ty to_iter, Action_Func_ty action_func,
													 void *param);

/* Inserts sublist in range [src_from, src_to) before dest_iter */
/* Returns src_from  */
/* Complexity: O(1) */
dlist_iter_ty Splice(dlist_iter_ty dest_iter, 
								dlist_iter_ty src_from, dlist_iter_ty src_to);
							 
#endif	/* __DLIST_H__ */

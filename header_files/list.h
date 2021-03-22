/**********************************FILE-HEADER*********************************\
* File: list.h						 		   
* Author: Rostik Angelevich					   
* Date: 21/03/2021							   
* Version: 1.0  							   
* Reviewer: Daniel							   
* Description: Single Linked List API		    
\******************************************************************************/
#ifndef	__LIST_H__
#define	__LIST_H__

#include <stddef.h>	/* size_t */

#include "utils.h" /* status_ty, bolean_ty*/

typedef struct slist slist_ty;

typedef struct slist_node slist_node_ty;

typedef slist_node_ty *slist_iter_ty;

typedef boolean_ty (*IsMatch_Func)(void *data, void *param);

typedef status_ty (*Action_Func)(void *data, void *param);

/* Creates an empty single-linked list and returns pointer to the head */
/* returns NULL on failure*/
/* Complexity: O(1) */
slist_ty *SlistCreate(void);

/* Deletes entire List */
/* Complexity: O(n) */
void SlistDestroy(slist_ty *slist);

/* Returns iterator to beginning of the list */
/* Returns NULL if list is empty */
/* Complexity: O(1) */
slist_iter_ty SlistIteratorBegin(const slist_ty *slist);

/* Returns iterator to end of the list */
/* Complexity: O(1) */
slist_iter_ty SlistIteratorEnd(const slist_ty *slist);

/* Returns iterator to next elemet in the list */
/* Returns slist_END on the last element in the list */
/* Complexity: O(1) */
slist_iter_ty SlistIteratorNext(const slist_iter_ty iter);

/* Returns TRUE if both iterators are of the same item, */
/* or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty SlistIteratorIsEqual(const slist_iter_ty iter_a, 
											const slist_iter_ty iter_b);

/* Returns the data of the iterator */
/* Undefined behaviour if iter is slist_END */
/* Complexity: O(1) */
void *SlistGetData(const slist_iter_ty iter);

/* Sets the data at the iterator */
/* Undefined behaviour if iter is slist_END */
/* Complexity: O(1) */
void SlistSetData(slist_iter_ty iter, void *data);

/* Insters the element after the iterator, returns iterator to the new node */
/* TODO Undefined behaviour if iter is slist_END */
/* Complexity: O(1) */
slist_iter_ty SlistInsert(slist_iter_ty iter, void *data);

/* Removes the current element from the list, */
/* returns iterator to the next element in the list */
/* TODO Undefined behaviour if iter is slist_END */
/* Complexity: O(1) */
slist_iter_ty SlistRemove(slist_iter_ty iter);

/* Returns TRUE if list is empty or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty SlistIsEmpty(const slist_ty *slist);

/* Returns number of elements in the list */
/* Complexity: O(n) */
size_t SlistSize(const slist_ty *slist);

/* Returns the first iterator to the found element */
/* in range of [from_iter, to_iter) */
/* returns to_iter if data not found */
/* Complexity: O(n) */
slist_iter_ty SlistFind(const slist_iter_ty from_iter, 
	const slist_iter_ty to_iter, IsMatch_Func,
	void *param);

/* Perform the function Action_Func on each element in range */
/* [from_iter, to_item) until failure */
/* Returns SUCCESS if no errors, FAILURE otherwise */
/* Complexity: O(n) */
status_ty SlistForEach(const slist_iter_ty from_iter,
const slist_iter_ty to_iter, Action_Func, void *param);
							 
#endif	/* __LIST_H__ */

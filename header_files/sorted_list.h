/***********************************************
* File: sorted_list.h						 	*
* Date: 05/04/2021							    *
* Version: 2.4								    *
* Description: Sorted List API  		        * 
************************************************/
#ifndef	__SORTEDLIST_H__
#define	__SORTEDLIST_H__

#include <stddef.h>	/* size_t	*/

#include "utils.h"	/* status_ty, bolean_ty	*/
#include "dlist.h"

typedef struct sorted_list sorted_list_ty;

typedef dlist_iter_ty sorted_list_iter_ty;

typedef boolean_ty (*Is_Match_Func_ty)(const void *data, const void *param);

typedef status_ty (*Action_Function_ty)(void *data, const void *param);

/* Compare Func returns positive if data2 belongs somewhere after */
/* data1 in the list */
/* Returns 0 if the data are equal */
/* Returns negative otherwise */
typedef int (*Compare_Func_ty)(const void *data1, const void *data2);

/* Creates an empty sorted list and returns a pointer to handler struct */
/* List will be sorted based on the compare_func */
/* Returns NULL on failure */
/* Complexity: O(1) */
sorted_list_ty *SortedListCreate(Compare_Func_ty compare_func);

/* Frees entire List */
/* No operations will be performed if pointer is NULL */
/* Complexity: O(n) */
void SortedListDestroy(sorted_list_ty *sorted_list);

/* Returns iterator to first element of the list */
/* If sorted list is empty returns SortedList_END */
/* Complexity: O(1) */
sorted_list_iter_ty SortedListIteratorBegin(const sorted_list_ty *sorted_list);

/* Returns iterator to the SortedList_End dummy of the list */
/* Complexity: O(1) */
sorted_list_iter_ty SortedListIteratorEnd(const sorted_list_ty *sorted_list);

/* Returns iterator to the next element in the list */
/* Returns SortedList_END on the last element in the list */
/* Undefined if iter is SortedList_End */
/* Complexity: O(1) */
sorted_list_iter_ty SortedListIteratorNext(const sorted_list_iter_ty iter);

/* Returns iterator to the previous element in the list */
/* Undefined if iter is at the first element */
/* Complexity: O(1) */
sorted_list_iter_ty SortedListIteratorPrevious(const sorted_list_iter_ty iter);

/* Returns TRUE if both are iterators of the same element */
/* Or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty SortedListIteratorIsEqual(const sorted_list_iter_ty iter_a, 
													const sorted_list_iter_ty iter_b);

/* Returns the data of the iterator */
/* Undefined behaviour if iter is SortedList_END */
/* Complexity: O(1) */
void *SortedListGetData(const sorted_list_iter_ty iter);

/* Inserts the data in the appropriate place in the list */
/* Returns iterator to the new element */
/* On failure returns the SortedList_End */
/* Complexity: O(n) */
sorted_list_iter_ty SortedListInsert(sorted_list_ty *list, void *data);

/* Removes the element from the list */
/* Returns iterator to the next element in the list */
/* Undefined behavior if iter is SortedList_End */
/* Complexity: O(1) */
sorted_list_iter_ty SortedListRemove(sorted_list_iter_ty iter);

/* Removes a node from the beginning of the list */
/* Returns the popped element */
/* Undefined if sorted list is empty */
/* Complexity: O(1) */
void *SortedListPopFront(sorted_list_ty *sorted_list);

/* Removes a node from the end of the list, before the SortedList_End */
/* Returns the popped element */
/* Undefined if SortedList is empty */
/* Complexity: O(1) */
void *SortedListPopBack(sorted_list_ty *sorted_list);

/* Returns TRUE if list is empty or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty SortedListIsEmpty(const sorted_list_ty *sorted_list);

/* Returns number of elements in the list */
/* Complexity: O(n) */
size_t SortedListSize(const sorted_list_ty *sorted_list);

/* Returns the first iterator to the found element based on sort criteria */
/* In range of [from_iter, to_iter) */
/* Returns to_iter if data not found */
/* Complexity: O(n) */
sorted_list_iter_ty SortedListFind(const sorted_list_ty *list, 
                            const sorted_list_iter_ty from_iter, 
								const sorted_list_iter_ty to_iter,
												void *param);

/* Returns the first iterator to the found element based on given criteria */
/* In range of [from_iter, to_iter) */
/* Returns to_iter if data not found */
/* Complexity: O(n) */
sorted_list_iter_ty SortedListFindIf(const sorted_list_iter_ty from_iter, 
								const sorted_list_iter_ty to_iter, 
										Is_Match_Func_ty match_func,
												void *param);
			
/* Perform the function Action_Func on each element in range, */
/* [from_iter, to_item) until failure */
/* Returns SUCCESS if no errors, FAILURE otherwise */
/* Note: the action function may ruin the sorted nature of the list */
/* Complexity: O(n) */
status_ty SortedListForEach(sorted_list_iter_ty from_iter,
			const sorted_list_iter_ty to_iter, Action_Function_ty action_func,
													 void *param);

/* Merges two sorted lists */
/* Leaves the other list empty */
/* The two lists must be sorted via the same criteria */
/* Complexity: O(n) */
void SortedListMerge(sorted_list_ty *dest_list, 
						sorted_list_ty *src_list);
							 
#endif	/* __SORTEDLIST_H__ */

/***********************************************
* File: heap_queue.h							 	*
* Date: 08/04/2021							    *
* Version: 1.1 								    *
* Description: Priority Queue API  		        * 
************************************************/
#ifndef	__HEAP_QUEUE_H__
#define	__HEAP_QUEUE_H__

#include <stddef.h>	/*	size_t	*/

#include "utils.h"	/*	status_ty, bolean_ty	*/

typedef struct heap_queue heap_queue_ty;                                                  
                                                          
typedef boolean_ty (*Match_Function_ty)(const void *data, const void *param);

/* Compare Func returns positive if data2 has a lower priority than/
/ data1 in the list /
/ Returns 0 if the data are equal /
/ Returns negative otherwise */
typedef int (*Cmp_Func_ty)(const void *data1, const void *data2);

/* Creates an empty heap_queue and returns pointer to handler struct */
/* returns NULL on failure */
/* Complexity: O(1) */
heap_queue_ty *HeapQueueCreate(Cmp_Func_ty cmp_func);

/* Frees entire heap_queue */
/* No operations will be performed if pointer is NULL */
/* Complexity: O(n) */
void HeapQueueDestroy(heap_queue_ty *heap_queue);

/* Inserts the data in the appropriate place in the heap_queue */
/* Return value: On success - SUCCESS                       */
/* 				 On failure - FAILURE                       */
/* Complexity: O(n) */
status_ty HeapQueueEnqueue(heap_queue_ty *heap_queue, void *data);

/* Removes the first element from the heap_queue */
/* undefined - if the heap_queue is empty        */
/* Returns dequeued data                      */
/* Complexity: O(1)                           */
void *HeapQueueDequeue(heap_queue_ty *heap_queue);

/* Returns TRUE if heap_queue is empty or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty HeapQueueIsEmpty(const heap_queue_ty *heap_queue);

/* Returns number of elements in the heap_queue */
/* Complexity: O(n) */
size_t HeapQueueSize(const heap_queue_ty *heap_queue);

/* Returns the first element */
/* undefined - if the heap_queue is empty */
/* Complexity: O(1) */
void *HeapQueuePeek(const heap_queue_ty *heap_queue);

/* Clears all the heap_queue */
/* undefined - if the heap_queue is empty */
/* Complexity: O(n) */
void HeapQueueClear(heap_queue_ty *heap_queue);

/* Erases the first element that found based on given criteria */
/* Returns the removed data    */
/* Returns NULL if data not found  */
/* Complexity: O(n) */
void *HeapQueueErase(heap_queue_ty *heap_queue, Match_Function_ty match_func, void *param);

#endif	/* __HeapQueue_H__ */

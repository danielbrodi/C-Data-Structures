/****************************** File Header ***********************************\
* File Name: queue.h
* Author: Daniel Brodsky
* Description: API of a Queue (FIFO) API based on a Singly Linked List wrap. 
* Date: 29/03/2021
* Version: 1.0
\******************************************************************************/

#ifndef	__QUEUE_H__
#define	__QUEUE_H__

#include <stddef.h>	/* size_t */

#include "utils.h" /* status_ty, bolean_ty*/

/******************************************************************************/

typedef struct queue queue_ty;

/* Creates an empty queue and returns pointer to handler struct */
/* returns NULL on failure*/
/* Complexity: O(1) */
queue_ty *QueueCreate(void);

/* Frees entire queue */
/* Complexity: O(n) */
void QueueDestroy(queue_ty *queue);

/* Inserts the element in the end of the queue */
/* Return value: On success - SUCCESS  */
/* 				 On failure - FAILURE */
/* Complexity: O(1) */
status_ty Enqueue(queue_ty *queue, void *data);

/* Removes the first element from the queue */
/* undefined - if the queue is empty */
/* Complexity: O(1) */
void Dequeue(queue_ty *queue);

/* Returns TRUE if queue is empty or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty QueueIsEmpty(const queue_ty *queue);

/* Returns number of elements in the queue */
/* Complexity: O(n) */
size_t QueueSize(const queue_ty *queue);

/* Returns the first element */
/* Complexity: O(1) */
void *QueuePeek(const queue_ty *queue);

/* Appends queue_src to the end of queue_dest */
/* Complexity: O(1) */
void QueueAppend(queue_ty *queue_dest, queue_ty *queue_src);							 
/******************************************************************************/
#endif	/* __QUEUE_H__ */

/****************************** File Header ***********************************\
* File Name: queue.h
* Author: Daniel Brodsky
* Description: API of a Queue (FIFO) API based on a Singly Linked List wrap. 
* Date: 29/03/2021
* Version: 1.0
\******************************************************************************/

#ifndef	__QUEUE_H__
#define	__QUEUE_H__

typedef queue queue_ty;

/* Creates an empty queue and returns pointer to handler struct */
/* returns NULL on failure*/
/* Complexity: O(1) */
queue_ty *QueueCreate(void);

/* Frees entire queue */
/* Complexity: O(n) */
void QueueDestroy(queue_ty *queue);

/* Adds a new node after rear and moves rear to the next node. */
/* Undefined behaviour if iter is queue_END */
/* Complexity: O(1) */
status_ty EnQueue(queue_ty *queue, void *data);

/* Removes the front node and moves front to the next node. */
/* Undefined behaviour if the queue is empty */
/* Complexity: O(1) */
status_ty DeQueue(queue_ty *queue);

/* Returns TRUE if queue is empty or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty QueueIsEmpty(const queue_ty *queue);

/* Returns number of elements in the queue */
/* Complexity: O(n) */
size_t QueueGetSize(const queue_ty *queue);

/* Returns the data of the iterator */
/* Undefined behaviour if iter is queue_END */
/* Complexity: O(1) */
void *QueuePeek(const queue_iter_ty iter);

/* Insters the element after the iterator, returns iterator to the new node */
/* On failure returns the same iterator */
/* Undefined behaviour if iter is queue_END */
/* Complexity: O(1) */
queue_iter_ty QueueAppend(queue_iter_ty iter, void *data);

#endif	/* __QUEUE_H__ */

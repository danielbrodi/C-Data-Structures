/***********************************************
* File: Pqueue.h							 	*
* Date: 08/04/2021							    *
* Version: 1.1 								    *
* Description: Priority Queue API  		        * 
************************************************/
#ifndef	__PQUEUE_H__
#define	__PQUEUE_H__

#include <stddef.h>	/* size_t */

#include "utils.h"  /* status_ty, bolean_ty */

typedef struct p_queue p_queue_ty;                                                  
                                                          
typedef boolean_ty (*Match_Function_ty)(const void *data, const void *param);

/* Compare Func returns positive if data2 belongs somewhere after */
/* data1 in the list */
/* Returns 0 if the data are equal */
/* Returns negative otherwise */
typedef int (*Cmp_Func_ty)(const void *data1, const void *data2);

/* Creates an empty p_queue and returns pointer to handler struct */
/* returns NULL on failure */
/* Complexity: O(1) */
p_queue_ty *PqueueCreate(Cmp_Func_ty cmp_func);

/* Frees entire p_queue */
/* Complexity: O(n) */
void PqueueDestroy(p_queue_ty *p_queue);

/* Inserts the data in the appropriate place in the p_queue */
/* Return value: On success - SUCCESS                       */
/* 				 On failure - FAILURE                       */
/* Complexity: O(n) */
status_ty PqueueEnqueue(p_queue_ty *p_queue, void *data);

/* Removes the first element from the p_queue */
/* undefined - if the p_queue is empty        */
/* Returns dequeued data                      */
/* Complexity: O(1)                           */
void *PqueueDequeue(p_queue_ty *p_queue);

/* Returns TRUE if p_queue is empty or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty PqueueIsEmpty(const p_queue_ty *p_queue);

/* Returns number of elements in the p_queue */
/* Complexity: O(n) */
size_t PqueueSize(const p_queue_ty *p_queue);

/* Returns the first element */
/* undefined - if the p_queue is empty */
/* Complexity: O(1) */
void *PqueuePeek(const p_queue_ty *p_queue);

/* Clears all the p_queue */
/* undefined - if the p_queue is empty */
/* Complexity: O(n) */
void PqueueClear(p_queue_ty *p_queue);

/* Erases the first element that found based on given criteria */
/* Returns NULL if data not found  */
/* Complexity: O(n) */
void *PqueueErase(p_queue_ty *p_queue, Match_Function_ty match_func, void *param);

#endif	/* __PQUEUE_H__ */

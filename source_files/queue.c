/**********************************FILE-HEADER*********************************\
* File: queue.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 29/03/2021							   								
* Version: Beta					   								
* Reviewer: Ariel							   								
* Description: Queue implementation wrapped by Singly Linked List's API.			 
\******************************************************************************/

/****************************** Inclusions ************************************/

#include <assert.h> /* assert */
#include <stddef.h>	/* size_t, NULL */
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, free */

#include "slist.h" /* singly linked list API wrapper */
#include "queue.h"

/************************** Global Definitions ********************************/

struct queue
{
	slist_ty *list;
	slist_iter_ty front;	/* stores the first node */
	slist_iter_ty rear;		/* stores the last node */
};

/************************Functions Implementations*****************************/
/******************************************************************************/

queue_ty *QueueCreate()
{
	queue_ty *new_queue = (queue_ty *)malloc(sizeof(queue_ty));
	if (NULL == new_queue)
	{
		fprintf(stderr, "Failed to allocate memory for a new queue\n");
		return(NULL);
	}
	
	new_queue->list = SlistCreate();
	if (NULL == new_queue->list)
	{
		free(new_queue);
		fprintf(stderr, "Failed to allocate memory for a new queue\n");
		return(NULL);
	}
	
	new_queue->front = NULL;
	new_queue->rear = NULL;
	
	return(new_queue);
}
/******************************************************************************/
void QueueDestroy(queue_ty *queue)
{
	assert(queue);
	
	SlistDestroy(queue->list);
	
	free(queue->front);
	queue->front = NULL;
	
	free(queue->rear);
	queue->rear = NULL;
	
	free(queue);
	queue = NULL;
}
/******************************************************************************/
status_ty EnQueue(queue_ty *queue, void *data)
{
	slist_iter_ty node = NULL;
	
	assert(queue);
	
	node = SlistInsert(SlistIteratorBegin(queue->list), data);
	
	if (SlistIteratorBegin(queue->list) != node)
	{
		if(QueueIsEmpty(queue))
		{
			queue->front = node;
		}
		else
		{
			queue->rear->next = node;
		}
		queue->rear = node;
		return(SUCCESS);
	}
	else
	{
		return(FAILURE);
	}
}
/******************************************************************************/
void DeQueue(queue_ty *queue)
{
	slist_iter_ty node = NULL;
	
	assert(queue);
	assert(!QueueIsEmpty(queue));
	
	node = queue->front;
	queue->front = queue-front->next;
	
	if(NULL == queue->front)
	{
		queue->rear = NULL;
	}
	
	SlistRemove(node); /* frees and removes the front node from list */
}
/******************************************************************************/
boolean_ty QueueIsEmpty(const queue_ty *queue)
{
	assert(queue);
	
	return(NULL == queue->front && NULL == queue->rear);
}
/******************************************************************************/
size_t QueueGetSize(const queue_ty *queue)
{
	assert(queue);
	
	return(SlistSize(queue->list));
}
/******************************************************************************/
void *QueuePeek(const queue_ty *queue);
{
	assert(queue);
	assert(!QueueIsEmpty(queue));
	
	return(queue->front->data);
}
/******************************************************************************/
void QueueAppend(queue_iter_ty iter, void *data)
{

}

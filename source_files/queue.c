/**********************************FILE-HEADER*********************************\
* File: queue.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 29/03/2021							   								
* Version: 1.0 (Before Review)					   								
* Reviewer: Ariel							   								
* Description: Queue implementation wrapped by Singly Linked List's API.			 
\******************************************************************************/

/****************************** Inclusions ************************************/

#include <assert.h> /* assert */
#include <stddef.h>	/* size_t, NULL */
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, free */

#include "../include/slist.h" /* singly linked list API wrapper */
#include "../include/queue.h"

/************************** Global Definitions ********************************/

struct queue
{
	slist_ty *list;
	slist_iter_ty rear;		/* stores the last node in the queue which is not
																a dummy node */
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
	
	new_queue->rear = SlistIteratorBegin(new_queue->list);
	
	return(new_queue);
}
/******************************************************************************/
void QueueDestroy(queue_ty *queue)
{
	assert(queue);
	
	SlistDestroy(queue->list);
	queue->list = NULL;
	
	free(queue);
	queue = NULL;
}
/******************************************************************************/
status_ty Enqueue(queue_ty *queue, void *data)
{
	slist_iter_ty node = NULL;
	
	assert(queue);
	
	node = SlistInsert(queue->rear, data);
	
	if (queue->rear != node)
	{
		queue->rear = node;
		return(SUCCESS);
	}
	
	return(FAILURE);
}
/******************************************************************************/
void Dequeue(queue_ty *queue)
{
	assert(queue);
	assert(!QueueIsEmpty(queue));

	/* frees and removes the front node from list */
	SlistRemove(SlistIteratorBegin(queue->list));
	
	if (SlistIsEmpty(queue->list))
	{
	 	queue->rear = SlistIteratorBegin(queue->list);
	}
}
/******************************************************************************/
boolean_ty QueueIsEmpty(const queue_ty *queue)
{
	assert(queue);
	
	return(SlistIsEmpty(queue->list));
}
/******************************************************************************/
size_t QueueSize(const queue_ty *queue)
{
	assert(queue);
	
	return(SlistSize(queue->list));
}
/******************************************************************************/
void *QueuePeek(const queue_ty *queue)
{
	assert(queue);
	assert(!QueueIsEmpty(queue));
	
	return(SlistGetData(SlistIteratorBegin(queue->list)));
}
/******************************************************************************/
void QueueAppend(queue_ty *dest_queue, queue_ty *src_queue)
{	
	assert(dest_queue);
	assert(src_queue);
	
	SlistAppend(dest_queue->list, src_queue->list);
	
	dest_queue->rear = src_queue->rear;
	src_queue->rear = SlistIteratorBegin(src_queue->list);
}
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* for testing purposes */
void PrintQueue(queue_ty *queue)
{
	
	size_t i = 0;
	
	slist_iter_ty iter = NULL;
	assert(queue);
	
	if(FALSE == QueueIsEmpty(queue))
	{
		iter = SlistIteratorBegin(queue->list);
		
		for(i = 0; i < QueueSize(queue); ++i)
		{
			printf("%ld\n",(unsigned long)SlistGetData(iter));
			iter = SlistIteratorNext(iter);
		}
		printf("\n");
	}
}
/******************************************************************************/

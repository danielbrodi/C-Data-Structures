/*********************************FILE__HEADER*********************************\
* File:				heap_queue.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				14-06-2021
* Code Reviewer:	
* Pseudo Reviewer:	Eran					   								
* Version:			1.0							
* Description:		Heap Queue implementation.
\******************************************************************************/

#include <assert.h>	/*	assert	*/
#include <stdlib.h>	/*	malloc, free	*/
#include <stddef.h>	/* sise_t, NULL	*/

#include "heap_queue.h"
#include "utils.h"	/* boolean_ty, status_ty	*/
#include "vector.h"
#include "heap.h"

/******************************************************************************/

struct heap_queue
{
	vector_ty *vector;
	Cmp_Func_ty cmp_func;
};

/******************************************************************************/
heap_queue_ty *HeapQueueCreate(Cmp_Func_ty cmp_func)
{
	heap_queue_ty *new_pqueue = NULL;
	
	/*	assert for the cmp_func*/
	assert(cmp_func);
	
	/*	create and allocate memory for HeapQueue structure*/
	/*	handle memory issues if any*/
	new_pqueue = (heap_queue_ty *)malloc(sizeof(heap_queue_ty));
	if (new_pqueue)
	{
		/*	assign cmp func to HeapQueue*/
			new_pqueue->cmp_func = cmp_func;
			
		/*	create and allocate memory for the vector inside the HeapQueue*/
		/*	handle memory issues if any*/
		new_pqueue->vector = VectorCreate(10);
		if (!new_pqueue->vector)
		{
			new_pqueue->cmp_func = NULL;
			
			free(new_pqueue);
			new_pqueue = NULL;
		}
	}
	
	/*	return HeapQueue*/
	return (new_pqueue);
}
/******************************************************************************/
void HeapQueueDestroy(heap_queue_ty *heap_queue)
{
	/*	if HeapQueue not null*/
	if (heap_queue)
	{
		/*	destroy vector with inbuilt function*/
		VectorDestroy(heap_queue->vector);
		
		/*	nullify HeapQueue struct members*/
		heap_queue->vector = NULL;
		heap_queue->cmp_func = NULL;
		
		/*	free HeapQueue*/
		free(heap_queue);
		
		/*	nullify HeapQueue*/
		heap_queue = NULL;
	}
}
/******************************************************************************/
status_ty HeapQueueEnqueue(heap_queue_ty *heap_queue, void *data)
{
	status_ty ret_status = SUCCESS;
	
	/*	asserts*/
	assert(heap_queue);
	assert(data);
	
	/*	insert data to the end of the vector*/
	/*	if failed - return failure*/
	ret_status = VectorPushBack(heap_queue->vector, data);
	if (SUCCESS == ret_status)
	{
		/*	HeapifyUp*/
		HeapifyUp(VectorGetActualArray(heap_queue->vector),HeapQueueSize(heap_queue),
															heap_queue->cmp_func);
	}
	
	return (ret_status);
}
/******************************************************************************/
void *HeapQueueDequeue(heap_queue_ty *heap_queue)
{
	void *ret_data = NULL, *first_elem = NULL, *last_elem = NULL;
	
	status_ty status = SUCCESS;
	
	/*	asserts*/
	assert(heap_queue);
	
	/*peek first element and sava data to return it*/
	ret_data = HeapQueuePeek(heap_queue);
	
	/*	switch last and first element in the vector*/
	first_elem = ret_data;
	last_elem = *(VectorGetActualArray(heap_queue->vector) + VectorSize(heap_queue->vector) - 1);
	
	VectorSetElement(heap_queue->vector, 0, last_elem);
	VectorSetElement(heap_queue->vector, VectorSize(heap_queue->vector) - 1, first_elem);
	
	/*	remove the last element of the vector*/
	/*	if failed - return null*/
	VectorPopBack(heap_queue->vector);
	
	if (SUCCESS == status)
	{
		/*	HeapifyDown*/
		HeapifyDown(VectorGetActualArray(heap_queue->vector),HeapQueueSize(heap_queue),
															heap_queue->cmp_func);
	}
	
	return (SUCCESS == status ? ret_data : NULL);
}
/******************************************************************************/
boolean_ty HeapQueueIsEmpty(const heap_queue_ty *heap_queue)
{
	/*	asserts*/
	assert(heap_queue);
	
	/*	return true or false based on if the size of the vector is zero*/
	return (0 == VectorSize(heap_queue->vector));
}
/******************************************************************************/
size_t HeapQueueSize(const heap_queue_ty *heap_queue)
{
	/*	asserts*/
	assert(heap_queue);
	
	/*	return the size of the vector*/
	return (VectorSize(heap_queue->vector));
}
/******************************************************************************/
void *HeapQueuePeek(const heap_queue_ty *heap_queue)
{
	void *ret_data = NULL;
	
	/*	asserts*/
	assert(heap_queue);
	
	/* get data of first element in the vector	*/
	ret_data = *(VectorGetActualArray(heap_queue->vector));
	
	/*	return this data*/
	return (ret_data);
}
/******************************************************************************/
void HeapQueueClear(heap_queue_ty *heap_queue)
{
	/*	assert*/
	assert(heap_queue);
	
	/*	resereve vector's size to 1 */
	if (SUCCESS == VectorReserve(heap_queue->vector, 1))
	{ 
		/*	dequeue	last element */
		HeapQueueDequeue(heap_queue);
	}
}
/******************************************************************************/
void *HeapQueueErase(heap_queue_ty *heap_queue, Match_Function_ty match_func, void *param)
{
	UNUSED(heap_queue);
	UNUSED(match_func);
	UNUSED(param);
	
	return (NULL);
}
/******************************************************************************/

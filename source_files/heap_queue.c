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

#include "utils.h"	/* boolean_ty, status_ty	*/
#include "pqueue.h"
#include "vector.h"
#include "heap.h"

/******************************************************************************/

struct p_queue
{
	vector_ty *vector;
	Cmp_Func_ty cmp_func;
};

/******************************************************************************/
p_queue_ty *PqueueCreate(Cmp_Func_ty cmp_func)
{
	p_queue_ty *new_pqueue = NULL;
	
	/*	assert for the cmp_func*/
	assert(cmp_func);
	
	/*	create and allocate memory for pqueue structure*/
	/*	handle memory issues if any*/
	new_pqueue = (p_queue_ty *)malloc(sizeof(p_queue_ty));
	if (new_pqueue)
	{
		/*	assign cmp func to pqueue*/
			new_pqueue->cmp_func = cmp_func;
			
		/*	create and allocate memory for the vector inside the pqueue*/
		/*	handle memory issues if any*/
		new_pqueue->vector = VectorCreate(1);
		if (!new_pqueue->vector)
		{
			new_pqueue->cmp_func = NULL;
			
			free(new_pqueue);
			new_pqueue = NULL;
		}
	}
	
	/*	return pqueue*/
	return (new_pqueue);
}
/******************************************************************************/
void PqueueDestroy(p_queue_ty *p_queue)
{
	/*	if pqueue not null*/
	if (p_queue)
	{
		/*	destroy vector with inbuilt function*/
		VectorDestroy(p_queue->vector);
		
		/*	nullify pqueue struct members*/
		p_queue->vector = NULL;
		p_queue->cmp_func = NULL;
		
		/*	free pqueue*/
		free(p_queue);
		
		/*	nullify pqueue*/
		p_queue = NULL;
	}
}
/******************************************************************************/
status_ty PqueueEnqueue(p_queue_ty *p_queue, void *data)
{
	status_ty ret_status = SUCCESS;
	
	/*	asserts*/
	assert(p_queue);
	assert(data);
	
	/*	insert data to the end of the vector*/
	/*	if failed - return failure*/
	ret_status = VectorPushBack(p_queue->vector, data);
	if (SUCCESS == ret_status)
	{
		/*	HeapifyUp*/
		HeapifyUp(VectorGetActualArray(p_queue->vector),PqueueSize(p_queue),
															p_queue->cmp_func);
	}
	
	return (ret_status);
}
/******************************************************************************/
void *PqueueDequeue(p_queue_ty *p_queue)
{
	void *ret_data = NULL, *first_elem = NULL, *last_elem = NULL;
	
	status_ty status = SUCCESS;
	
	/*	asserts*/
	assert(p_queue);
	
	/*peek first element and sava data to return it*/
	ret_data = PqueuePeek(p_queue);
	
	/*	switch last and first element in the vector*/
	first_elem = ret_data;
	last_elem = *(VectorGetActualArray(p_queue->vector) + VectorSize(p_queue->vector) - 1);
	
	VectorSetElement(p_queue->vector, 0, last_elem);
	VectorSetElement(p_queue->vector, VectorSize(p_queue->vector) - 1, first_elem);
	
	/*	remove the last element of the vector*/
	/*	if failed - return null*/
	VectorPopBack(p_queue->vector);
	
	if (SUCCESS == status)
	{
		/*	HeapifyDown*/
		HeapifyDown(VectorGetActualArray(p_queue->vector),PqueueSize(p_queue),
															p_queue->cmp_func);
	}
	
	return (SUCCESS == status ? ret_data : NULL);
}
/******************************************************************************/
boolean_ty PqueueIsEmpty(const p_queue_ty *p_queue)
{
	/*	asserts*/
	assert(p_queue);
	
	/*	return true or false based on if the size of the vector is zero*/
	return (0 == VectorSize(p_queue->vector));
}
/******************************************************************************/
size_t PqueueSize(const p_queue_ty *p_queue)
{
	/*	asserts*/
	assert(p_queue);
	
	/*	return the size of the vector*/
	return (VectorSize(p_queue->vector));
}
/******************************************************************************/
void *PqueuePeek(const p_queue_ty *p_queue)
{
	void *ret_data = NULL;
	
	/*	asserts*/
	assert(p_queue);
	
	/* get data of first element in the vector	*/
	ret_data = *(VectorGetActualArray(p_queue->vector));
	
	/*	return this data*/
	return (ret_data);
}
/******************************************************************************/
void PqueueClear(p_queue_ty *p_queue)
{
	/*	assert*/
	assert(p_queue);
	
	/*	resereve vector's size to 1 */
	if (SUCCESS == VectorReserve(p_queue->vector, 1))
	{ 
		/*	dequeue	last element */
		PqueueDequeue(p_queue);
	}
}
/******************************************************************************/

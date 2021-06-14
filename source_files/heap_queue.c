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
#include "utils.h"	/* boolean_ty, status_ty	*/
#include "pqueue.h"

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
	new_pqueue = (p_queue_ty *)malloc(sizeof(pqueue_ty));
	if (new_pqueue)
	{
		/*	assign cmp func to pqueue*/
			new_pqueue->cmp_func = cmp_func;
			
		/*	create and allocate memory for the vector inside the pqueue*/
		/*	handle memory issues if any*/
		new_pqueue->vector = (vector_ty *)malloc(sizeof(vector_ty));
		if (!pqueue->vector)
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
		HeapifyUp(VectorGetActualArray(p_queue->vector), sizeof(size_t),
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
	ret_data = *(VectorGetActualArray(p_queue->vector));
	
	/*	switch last and first element in the vector*/
	first_elem = ret_data;
	last_elem = p_queue->vector + VectorSize(p_queue->vector) - 1;
	
	VectorSetElement(p_queue->vector, 0, last_elem);
	VectorSetElement(p_queue->vector, VectorSize(p_queue->vector) - 1, first_elem);
	
	/*	remove the last element of the vector*/
	/*	if failed - return null*/
	status == VectorPopBack(p_queue->vector);
	
	if (SUCCESS == status)
	{
		/*	HeapifyDown*/
		HeapifyDown(VectorGetActualArray(p_queue->vector), sizeof(size_t),
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

	/*	return the size of the vector*/
}
/******************************************************************************/
void *PqueuePeek(const p_queue_ty *p_queue)
{
	/*	asserts*/

	/* get data of element of first index of the vector	*/

	/*	return this data*/
}
/******************************************************************************/
void PqueueClear(p_queue_ty *p_queue)
{
	/*	assert*/

	/*	resereve vector's size to 1 */
	/*	dequeue	last element */
}
/******************************************************************************/

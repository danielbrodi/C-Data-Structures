/*********************************FILE__HEADER*********************************\
* File:				heap_queue.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				14-06-2021
* Code Reviewer:	
* Pseudo Reviewer:							   								
* Version:			1.0							
* Description:		Heap Queue implementation.
\******************************************************************************/

#include <assert.h>	/*	assert	*/

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
	/*	assert for the cmp_func*/
	
	/*	create and allocate memory for pqueue structure*/
	/*	handle memory issues if any*/

	/*	create and allocate memory for the vector inside the pqueue*/
	/*	handle memory issues if any*/

	/*	assign cmp func to pqueue*/

		/*	return pqueue*/
}
/******************************************************************************/
void PqueueDestroy(p_queue_ty *p_queue)
{
	/*	if pqueue not null*/

	/*	destroy vector with inbuilt function*/

	/*	nullify pqueue struct members*/

	/*	free pqueue*/

	/*	nullify pqueue*/
}
/******************************************************************************/
status_ty PqueueEnqueue(p_queue_ty *p_queue, void *data)
{
	/*	asserts*/

	/*	insert data to the end of the vector*/
	/*	if failed - return failure*/

	/*	HeapifyUp*/

	/*	return success*/
}
/******************************************************************************/
void *PqueueDequeue(p_queue_ty *p_queue)
{
	/*	asserts*/

	/*peek and sava data to return it*/
	
	/*	switch last and first element in the vector*/
	
	/*	remove the last element of the vector*/
	/*	if failed - return null*/

	/*	HeapifyDown*/

	/*	return data*/
}
/******************************************************************************/
boolean_ty PqueueIsEmpty(const p_queue_ty *p_queue)
{
	/*	asserts*/

	/*	return true or false based on if the size of the vector is zero*/
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

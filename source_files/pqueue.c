/*********************************FILE__HEADER*********************************\
* File:	pqueue.c						 		  								
* Author:	Daniel Brodsky					  								
* Date:	08/04/2021							   								
* Version:	1.0	(Reviewed)						
* Reviewer:	Eran						   								
* Description:	Priority Queue implementation wrapped by Sorted List's API.			 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>				/*	assert			*/
#include <stddef.h>				/*	size_t, NULL	*/
#include <stdlib.h>				/*	free			*/

#include "utils.h"				/*	status_ty, boolean_ty	*/
#include "sorted_list.h"		/*	sorted list API wrapper	*/
#include "pqueue.h"

/***************************** Global Definitions *****************************/
struct p_queue
{
	sorted_list_ty *list;		/*	stores a list of elements which are sorted
									by their priorities.	*/
};
/******************************************************************************/
/************************* Functions__Implementations *************************/
/******************************************************************************/
p_queue_ty *PqueueCreate(Cmp_Func_ty cmp_func)
{
	p_queue_ty *new_p_queue = NULL;
	
	assert(cmp_func);
	
	new_p_queue = (p_queue_ty *)malloc(sizeof(p_queue_ty));
	if (NULL == new_p_queue)
	{
		return (NULL);
	}
	
	new_p_queue->list = SortedListCreate(cmp_func);
	if (NULL == new_p_queue->list)
	{
		free(new_p_queue);
		new_p_queue = NULL;
		
		return (NULL);
	}
	
	return (new_p_queue);
}
/******************************************************************************/
void PqueueDestroy(p_queue_ty *p_queue)
{
	if(p_queue) 
	{
		SortedListDestroy(p_queue->list);
		p_queue->list = NULL;

		free(p_queue);
		p_queue = NULL;
	}
}
/******************************************************************************/
status_ty PqueueEnqueue(p_queue_ty *p_queue, void *data)
{
	assert(p_queue);
	
	/*
	Insert function returns the end dummy to indicate on a failure.
	IsEqual will check if the return value of Insert is the end dummy.
	If it will match, PqueueEnqueue will return FAILURE.
	*/
	return (SortedListIteratorIsEqual(
			SortedListInsert(p_queue->list, data),
			SortedListIteratorEnd(p_queue->list)));
}
/******************************************************************************/
void *PqueueDequeue(p_queue_ty *p_queue)
{
	assert(p_queue);
	assert(!PqueueIsEmpty(p_queue));
	
	return (SortedListPopFront(p_queue->list));
}
/******************************************************************************/
boolean_ty PqueueIsEmpty(const p_queue_ty *p_queue)
{
	assert(p_queue);
	
	return (SortedListIsEmpty(p_queue->list));
}
/******************************************************************************/
size_t PqueueSize(const p_queue_ty *p_queue)
{
	assert(p_queue);
	
	return (SortedListSize(p_queue->list));
}
/******************************************************************************/
void *PqueuePeek(const p_queue_ty *p_queue)
{
	assert(p_queue);
	assert(!PqueueIsEmpty(p_queue));
	
	return (SortedListGetData(SortedListIteratorBegin(p_queue->list)));
}
/******************************************************************************/
void PqueueClear(p_queue_ty *p_queue)
{
	assert(p_queue);
	assert(!PqueueIsEmpty(p_queue));
	
	while(!PqueueIsEmpty(p_queue))
	{
		PqueueDequeue(p_queue);
	}
}
/******************************************************************************/
void *PqueueErase(p_queue_ty *p_queue, Match_Function_ty match_func, void *param)
{
	void *ret_data = NULL;	/*	stores the data that will be returned.	*/
	sorted_list_iter_ty element_to_erase = NULL;
	sorted_list_iter_ty head = NULL;
	sorted_list_iter_ty tail = NULL;
	
	assert(p_queue);
	assert(match_func);

	head = SortedListIteratorBegin(p_queue->list);
	tail = SortedListIteratorEnd(p_queue->list);

	element_to_erase = SortedListFindIf(head, tail, match_func, param);

	if(!SortedListIteratorIsEqual(element_to_erase, tail))
	{
		ret_data = SortedListGetData(element_to_erase);
		SortedListRemove(element_to_erase);
	}

	return(ret_data);
}
/******************************************************************************/

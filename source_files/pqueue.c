/*********************************FILE__HEADER*********************************\
* File:	pqueue.c						 		  								
* Author:	Daniel Brodsky					  								
* Date:	08/04/2021							   								
* Version:	1.0	(Pre Review)						
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
									by their priorities	*/
};
/******************************************************************************/
/************************* Functions__Implementations *************************/
/******************************************************************************/
p_queue_ty *PqueueCreate(Cmp_Func_ty cmp_func)
{
	assert(cmp_func);
	
	p_queue_ty *new_p_queue = (p_queue_ty *)malloc(sizeof(p_queue_ty));
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
	assert(p_queue);
	
	if(p_queue) 
	{
		SortedListDestory(p_queue->list);
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
	Insert function returns the end dummy if it failed.
	IsEqual will check if the return value of Insert is the end dummy.
	IsEqual returns a boolean value TRUE or FALSE which stands for 1 or 0.
	PqueueEnqueue returns SUCCESS or FAILURE which stands for 0 or 1.
	SUCCESS stands for 0 while TRUE stands for 1, and same goes for
	FAILURE and FALSE. Thus, the use of the `NOT` operator.
	*/
	return (!(
			SortedListIteratorIsEqual(
			SortedListInsert(p_queue->list, data),
			SortedListIteratorEnd(p_queue->list))));
}
/******************************************************************************/
void *PqueueDequeue(p_queue_ty *p_queue)
{
	assert(p_queue);
	assert(!PqueueIsEmpty);
	
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
	assert(!PqueueIsEmpty);
	
	return (SortedListGetData(SortedListIteratorBegin(p_queue->list)));
}
/******************************************************************************/
void PqueueClear(p_queue_ty *p_queue)
{
	assert(p_queue);
	assert(!PqueueIsEmpty);
	
	while(!PqueueIsEmpty(p_queue->list))
	{
		PqueueDequeue(p_queue);
	}
}
/******************************************************************************/
void *PqueueErase(p_queue_ty *p_queue, Match_Function_ty match_func, void *param)
{
	void *ret_data = NULL;	/*	stores the data that will be returned	*/
	sorted_list_iter_ty element = NULL;
	sorted_list_iter_ty head = NULL;
	sorted_list_iter_ty tail = NULL
	
	assert(p_queue);
	assert(match_func);

	head = SortedListIteratorBegin(pqueue->list);
	tail = SortedListIteratorEnd(pqueue->list);

	element = SortedListFindIf(head, tail, match_func, param);

	if(!IsEqual(element, tail))
	{
		ret_data = SortedListGetData(element);
		SortedListRemove(element);
	}

	return(ret_data)
}
/******************************************************************************/

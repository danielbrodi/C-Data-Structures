/**********************************FILE-HEADER*********************************\
* File: list.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 21/03/2021							   								
* Version: 1.0 							   								
* Reviewer: Olga							   								
* Description: Single Linked List Functions Implementations.			 
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, realloc, free */
#include <assert.h> /* assert */

#include "../include/list.h"

/******************************* Global Definitions ***************************/
struct slist
{
	slist_iter_ty head;
	slist_iter_ty end;
};

struct slist_node
{
	void *data;
	slist_iter_ty next;
};

/************************Functions Implementations*****************************/

/******************************************************************************/
slist_ty *SlistCreate(void)
{
	slist_ty *new_list = (slist_ty *)malloc(sizeof(slist_ty));
	if (NULL == new_list)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return(NULL);
	}
	
	new_list->head = NULL;
	/* create a dummy node that will represent the end of the list */
	new_list->end = (slist_node *)malloc(sizeof(slist_node));
	if (NULL == new_list->end)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		free(new_list);
		return(NULL);
	}
	
	new_list->end->data = NULL;
	new_list->end->next = NULL;
	
	return(new_list->head);
}
/******************************************************************************/
void SlistDestroy(slist_ty *slist)
{
	slist_iter_ty temp = NULL;
	
	assert(slist);
	
	while(NULL != slist->head)
	{
		temp = slist->head;
		slist->head = slist->head->next;
		free(temp);
	}
	
	free(slist->end);
	slist->end = NULL;
	
	free(slist);
	slist = NULL;
}
/******************************************************************************/
slist_iter_ty SlistIteratorBegin(const slist_ty *slist)
{
	assert (slist);
	
	return(slist->head);
}
/******************************************************************************/
slist_iter_ty SlistIteratorEnd(const slist_ty *slist)
{
/*	slist_iter_ty iterator = slist->head;*/
	
	assert (slist);
	
/*	if (NULL == slist->head)*/
/*	{*/
/*		return(NULL);*/
/*	}*/
/*	*/
/*	while (NULL != iterator->next->data)*/
/*	{*/
/*		iterator = iterator->next;*/
/*	}*/
	
	return(slist->end);
}
/******************************************************************************/
slist_iter_ty SlistIteratorNext(const slist_iter_ty iter)
{
	assert(iter);
	
	return(iter->next);
}
/******************************************************************************/
boolean_ty SlistIteratorIsEqual(const slist_iter_ty iter_a, 
											const slist_iter_ty iter_b)
{
   IsMatch_Func(iter_a->data, iter_b->data) ? return(SUCCESS) : return(FAILURE);
}
/******************************************************************************/
void *SlistGetData(const slist_iter_ty iter)
{
	assert(iter);
	assert(iter->next);
	
	return(iter->data);
}
/******************************************************************************/
void SlistSetData(slist_iter_ty iter, void *data)
{
	assert(iter);
	assert(iter->next);
	assert(data);
	
	iter->data = data;
}
/******************************************************************************/
slist_iter_ty SlistInsert(slist_iter_ty iter, void *data)
{
	slist_iter_ty new_node = iter;
	
	assert(iter);
	assert(iter->next);
	assert(data);
	
	new_node->data = data;
	new_node->next = iter->next;
	iter->next = new_node;
	
	return(new_node);
}
/******************************************************************************/
slist_iter_ty SlistRemove(slist_iter_ty iter)
{
	assert(iter);
	assert(iter->next);
	
	iter = iter->next;
	
	return(iter);
}
/******************************************************************************/
boolean_ty SlistIsEmpty(const slist_ty *slist)
{
	assert(slist);
	
	NULL == slist->head ? return(TRUE); : return(FALSE);
}
/******************************************************************************/
size_t SlistSize(const slist_ty *slist)
{
	size_t counter = 0;
	
	slist_iter_ty iterator = slist->head;
	
	assert (slist);
	
	if (NULL == slist->head)
	{
		return(counter);
	}
	
	while (NULL != iterator->data)
	{
		iterator = iterator->next;
		++counter;
	}
	
	return(iterator);
}
/******************************************************************************/
slist_iter_ty SlistFind(const slist_iter_ty from_iter, 
	const slist_iter_ty to_iter, IsMatch_Func,
	void *param)
{
	assert(from_iter);
	assert(to_iter);
	assert(param);

	slist_iter_ty runner = from_iter;
	
	while(runner != to_iter->next)
	{
	  IsMatch_Func(data, runner->data) ? return(runner) : runner = runner->next;
	}

	return(to_iter);
}
/******************************************************************************/
status_ty SlistForEach(const slist_iter_ty from_iter,
const slist_iter_ty to_iter, Action_Func, void *param)
{
	assert(from_iter);
	assert(to_iter);

	slist_iter_ty iterator = from_iter;
	
	while(iterator != to_iter->next)
	{
	 Action_Func(iterator, param) ? iterator = iterator->next : return(FAILURE);
	}

	return(SUCCESS);
}
/******************************************************************************/

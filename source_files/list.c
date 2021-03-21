/**********************************FILE-HEADER*********************************\
* File: list.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 21/03/2021							   								
* Version: Beta 							   								
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
	
	return(new_list);
}
/******************************************************************************/
void SlistDestroy(slist_ty *slist)
{
	slist_iter_ty temp = NULL;
	
	assert(slist);
	
	while(NULL != slist->head)
	{
		tmp = slist->head;
		slist->head = temp;
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
	
	slist_iter_ty iterator = slist->head;
	
	return(iterator);
}
/******************************************************************************/
slist_iter_ty SlistIteratorEnd(const slist_ty *slist)
{
	slist_iter_ty iterator = slist->head;
	
	assert (slist);
	
	if (NULL == slist->head)
	{
		return(NULL);
	}
	
	while (NULL != iterator->next->data)
	{
		iterator = iterator->next;
	}
	
	return(iterator);
}
/******************************************************************************/
slist_iter_ty SlistIteratorNext(const slist_iter_ty iter)
{
	assert(iter);
	
	return(iter->next);
}




/**********************************FILE-HEADER*********************************\
* File: slist.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 22/03/2021							   								
* Version: 3.0 (After Review)						   								
* Reviewer: Olga							   								
* Description: Single Linked List Functions Implementations.			 
\******************************************************************************/

/****************************** Macros Definitions ****************************/

#define ITER_TO_NODE_PTR(iter) (slist_node_ty *)iter
#define NODE_PTR_TO_ITER(iter) (slist_iter_ty)(node)
#define IS_END(iter) (ITER_TO_NODE_PTR(iter)->next == NULL)

/********************************** Inclusions ********************************/
#include <assert.h> /* assert */
#include <stddef.h>	/* size_t */
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, free */

#include "utils.h" /* status_ty, bolean_ty*/
#include "slist.h"


/******************************* Global Definitions ***************************/
struct slist
{
	slist_iter_ty head;
	slist_iter_ty tail;
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
	
	/* create a dummy node that will represent the beginning of the list */
	new_list->head = (slist_node_ty *)malloc(sizeof(slist_node_ty));
	if (NULL == new_list->head)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		free(new_list);
		return(NULL);
	}
	new_list->head->data = NULL;
	new_list->head->next = NULL;
	
	/* create a dummy node that will represent the  of the list */
	new_list->tail = (slist_node_ty *)malloc(sizeof(slist_node_ty));
	if (NULL == new_list->tail)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		free(new_list->head);
		free(new_list);
		return(NULL);
	}
	new_list->tail->data = new_list;
	new_list->tail->next = NULL;
	
	new_list->head->next = new_list->tail;
	
	return(new_list);
}
/******************************************************************************/
void SlistDestroy(slist_ty *slist)
{
	slist_iter_ty runner = NULL;
	
	assert(slist);
	
	while(slist->tail != slist->head)
	{
		runner = slist->head;
		slist->head = slist->head->next;
		free(runner);
	}
	
	free(slist->tail);
	slist->tail = NULL;
	
	free(slist);
	slist = NULL;
}
/******************************************************************************/
slist_iter_ty SlistIteratorBegin(const slist_ty *slist)
{
	assert (slist);
	
	if(SlistIsEmpty(slist))
	{
		return(slist->head);
	}
	
	return(slist->head->next);
}
/******************************************************************************/
slist_iter_ty SlistIteratorEnd(const slist_ty *slist)
{
	assert(slist);
	
	return(slist->tail);
}
/******************************************************************************/
slist_iter_ty SlistIteratorNext(const slist_iter_ty iter)
{
	assert(ITER_TO_NODE_PTR(iter));
	assert(ITER_TO_NODE_PTR(iter)->next);
	
	return(ITER_TO_NODE_PTR(iter)->next);
}

/******************************************************************************/
void *SlistGetData(const slist_iter_ty iter)
{
	assert(iter);
	assert(ITER_TO_NODE_PTR(iter)->next);
	
	return(ITER_TO_NODE_PTR(iter)->data);
}
/******************************************************************************/
void SlistSetData(slist_iter_ty iter, void *data)
{
	assert(iter);
	assert(ITER_TO_NODE_PTR(iter)->next);
	assert(data);
	
	(ITER_TO_NODE_PTR(iter))->data = data;
}
/******************************************************************************/
boolean_ty SlistIteratorIsEqual(const slist_iter_ty iter_a, 
											const slist_iter_ty iter_b)
{
	assert(iter_a);
	assert(iter_b);
	
	return(iter_a == iter_b);
}
/******************************************************************************/
slist_iter_ty SlistInsert(slist_iter_ty iter, void *data)
{
	slist_iter_ty new_node = NULL;
	
	assert(iter);
	assert(ITER_TO_NODE_PTR(iter)->next);
	assert(data);
	
	new_node = (slist_iter_ty)malloc(sizeof(slist_node_ty));
	if (NULL == new_node)
	{
		return(iter);
	}
	
	new_node->data = data;
	new_node->next = ITER_TO_NODE_PTR(iter)->next;
	(ITER_TO_NODE_PTR(iter))->next = new_node;
	
	return(new_node);
}
/******************************************************************************/
slist_iter_ty SlistRemove(slist_iter_ty iter)
{
	slist_iter_ty temp = NULL;
	
	assert(iter);
	assert(ITER_TO_NODE_PTR(iter)->next);
	
	(ITER_TO_NODE_PTR(iter))->data = (ITER_TO_NODE_PTR(iter))->next->data;
	
	temp = (ITER_TO_NODE_PTR(iter))->next->next;
	
	if(NULL == temp)
	{
		((slist_ty *)(ITER_TO_NODE_PTR(iter))->data)->tail = iter;
	}
	
	free((ITER_TO_NODE_PTR(iter))->next);
	
	(ITER_TO_NODE_PTR(iter))->next = temp;
	
	return(iter);
}
/******************************************************************************/
boolean_ty SlistIsEmpty(const slist_ty *slist)
{
	assert(slist);
	
	if (slist->tail == slist->head->next)
	{
		return(TRUE);
	}
	
	return(FALSE);
}
/******************************************************************************/
size_t SlistSize(const slist_ty *slist)
{
	size_t counter = 0;
	
	slist_iter_ty iterator = slist->head->next;
	
	assert (slist);
	
	while (slist->tail != iterator)
	{
		iterator = iterator->next;
		++counter;
	}
	
	return(counter);
}
/******************************************************************************/
slist_iter_ty SlistFind(const slist_iter_ty from_iter, 
	const slist_iter_ty to_iter, IsMatch_Func is_match_func,
	void *param)
{
	slist_iter_ty runner = NULL;
	
	assert(from_iter);
	assert(to_iter);
	assert(param);

	runner = from_iter;
	
	while(runner != to_iter)
	{
		if(TRUE == is_match_func(runner->data, param))
		{
			return(runner);
		}
		runner = runner->next;
	}

	return(to_iter);
}
/******************************************************************************/
status_ty SlistForEach(slist_iter_ty from_iter,
const slist_iter_ty to_iter, Action_Func action_func, void *param)
{
	slist_iter_ty iterator = NULL;
		
	assert(from_iter);
	assert(to_iter);
	
	iterator = from_iter;
	
	while(iterator != to_iter)
	{
		if(SUCCESS != action_func(iterator->data, param))
		{
			return(FAILURE);
		}
		
	iterator = iterator->next;
	}
	
	return(SUCCESS);
}
/******************************************************************************/
void SlistAppend(slist_ty *dest_slist, slist_ty *src_slist)
{
	assert(dest_slist);
	assert(src_slist);
	
	if (SlistIsEmpty(src_slist))
	{
		return;
	}
	
	/* switch tail dummy of dest with first node in src */
	dest_slist->tail->next = src_slist->head->next->next;
	dest_slist->tail->data = src_slist->head->next->data;
	/* switch tail dummy of src with tail dummy of dest */
	src_slist->tail->data = dest_slist;
	dest_slist->tail = src_slist->tail;
	/* make sure src list is empty */
	src_slist->head->next->next = NULL;
	src_slist->head->next->data = src_slist;
	src_slist->tail = src_slist->head->next;
	
}
/******************************************************************************/

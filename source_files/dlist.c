/**********************************FILE-HEADER*********************************\
* File: dlist.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 01/04/2021							   								
* Version: Beta				   								
* Reviewer: Danel						   								
* Description: Doubly Linked List Functions Implementations.			 
\******************************************************************************/

/************************** Macros Definitions ********************************/

#define ITER_TO_NODE_PTR(iter) (dlist_node_ty *)iter
#define NODE_PTR_TO_ITER(iter) (dlist_iter_ty)(node)
#define IS_END(iter) (ITER_TO_NODE_PTR(iter)->next == NULL)

/**************************** Inclusions **************************************/
#include <assert.h>		/* assert */
#include <stddef.h>		/* size_t */
#include <stdio.h> 		/* fprintf, NULL */
#include <stdlib.h>		/* malloc, free */

#include "dlist.h"
#include "utils.h"		/* status_ty, bolean_ty*/

/************************ Global Definitions **********************************/
struct Dlist
{
	dlist_iter_ty head;			/* represents the beginning of the list */
	dlist_iter_ty tail;			/* represents the end of the list */
};

struct dlist_node
{
	void *data;
	dlist_iter_ty previous;		/* points to the previous node in the list */
	dlist_iter_ty next;			/* points to the next node in the list */
};

/************************Functions Implementations*****************************/
/******************************************************************************/
dlist_ty *DlistCreate(void)
{
	dlist_ty *new_list = (dlist_ty *)malloc(sizeof(dlist_ty));
	if (NULL == new_list)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return(NULL);
	}
	
	/* create a dummy node that will represent the end of the list */
	new_list->tail = (dlist_node_ty *)malloc(sizeof(dlist_node_ty));
	if (NULL == new_list->tail)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		free(new_list);
		return(NULL);
	}
	
	/* tail node points to null because it's the last node in the list */
	new_list->tail->data = new_list;
	new_list->tail->previous = NULL;
	new_list->tail->next = NULL;
	
	/* the first (and only) node of an empty list is the end dummy node */
	new_list->head = new_list->tail;
	
	return(new_list);
}
/******************************************************************************/
void DlistDestroy(dlist_ty *dlist)
{
	dlist_node_ty *runner = NULL;
	
	/* If the received dlist is NULL, no operation is performed */
	if (NULL == dlist)
	{
		return;
	}
	
	while(!DlistIsEmpty(dlist))
	{
		runner = dlist->head;
		slist->head = slist->head->next;
		free(runner);
	}
	
	free(dlist->tail);
	dlist->tail = NULL;
	
	free(dlist);
	dlist = NULL;
}
/******************************************************************************/
dlist_iter_ty DlistIteratorBegin(const dlist_ty *dlist)
{
	assert(dlist);
	
	if(DlistIsEmpty(dlist))
	{
		return(dlist->tail);
	}
	
	return(dlist->head);
}
/******************************************************************************/
dlist_iter_ty DlistIteratorEnd(const dlist_ty *dlist)
{
	assert(dlist);
	
	return(dlist->tail);
}
/******************************************************************************/
dlist_iter_ty DlistIteratorNext(const dlist_iter_ty iter)
{
	assert(ITER_TO_NODE_PTR(iter));
	assert(ITER_TO_NODE_PTR(iter)->next);
	
	return(ITER_TO_NODE_PTR(iter)->next);
}
/******************************************************************************/
dlist_iter_ty DlistIteratorPrevious(const dlist_iter_ty iter)
{
	assert(ITER_TO_NODE_PTR(iter));
	assert(ITER_TO_NODE_PTR(iter)->previous);
	
	return(ITER_TO_NODE_PTR(iter)->previous);
}
/******************************************************************************/
void *DlistGetData(const dlist_iter_ty iter)
{
	assert(iter);
	assert(ITER_TO_NODE_PTR(iter)->next);
	
	return(ITER_TO_NODE_PTR(iter)->data);
}
/******************************************************************************/
void DlistSetData(dlist_iter_ty iter, void *data)
{
	assert(iter);
	assert(ITER_TO_NODE_PTR(iter)->next);
	assert(data);
	
	(ITER_TO_NODE_PTR(iter))->data = data;
}
/******************************************************************************/
boolean_ty DlistIteratorIsEqual(const dlist_iter_ty iter_a, 
											const dlist_iter_ty iter_b)
{
	assert(iter_a);
	assert(iter_b);
	
	return(NODE_PTR_TO_ITER(iter_a) == NODE_PTR_TO_ITER(iter_b));
}
/******************************************************************************/
dlist_iter_ty DlistInsertBefore(dlist_iter_ty iter, void *data)
{
	dlist_iter_ty new_node = NULL;
	
	assert(iter);
	assert(data);
	
	new_node = (dlist_iter_ty)malloc(sizeof(dlist_node_ty));
	if (NULL == new_node)
	{
		return(iter);
	}
	
	new_node->data = data;
	new_node->previous = ITER_TO_NODE_PTR(iter)->previous;
	new_node->next = NODE_PTR_TO_ITER(iter);
	
	(ITER_TO_NODE_PTR(iter))->previous = new_node;
	
	return(new_node);
}
/******************************************************************************/
dlist_iter_ty DlistRemove(dlist_iter_ty iter)
{
	dlist_iter_ty temp = NULL;
	
	assert(iter);
	assert(ITER_TO_NODE_PTR(iter)->next);
	
	(ITER_TO_NODE_PTR(iter))->data = (ITER_TO_NODE_PTR(iter))->next->data;
	
	temp = (ITER_TO_NODE_PTR(iter))->next->next;
	
	if(NULL == temp)
	{
		((dlist_ty *)(ITER_TO_NODE_PTR(iter))->data)->tail = iter;
	}
	
	free((ITER_TO_NODE_PTR(iter))->next);
	
	(ITER_TO_NODE_PTR(iter))->next = temp;
	
	(ITER_TO_NODE_PTR(temp))->previous = iter;
	
	return(iter);
}
/******************************************************************************/
boolean_ty DlistIsEmpty(const dlist_ty *dlist)
{
	assert(dlist);
	
	if (dlist->tail == dlist->head)
	{
		return(TRUE);
	}
	
	return(FALSE);
}
/******************************************************************************/
size_t DlistSize(const dlist_ty *dlist)
{
	size_t counter = 0;
	
	dlist_iter_ty iterator = dlist->head;
	
	assert (Dlist);
	
	while (dlist->tail != iterator)
	{
		iterator = iterator->next;
		++counter;
	}
	
	return(counter);
}
/******************************************************************************/
dlist_iter_ty DlistFind(const dlist_iter_ty from_iter, 
	const dlist_iter_ty to_iter, IsMatch_Func is_match_func,
	void *param)
{
	dlist_iter_ty runner = NULL;
	
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
status_ty DlistForEach(dlist_iter_ty from_iter,
const dlist_iter_ty to_iter, Action_Func action_func, void *param)
{
	dlist_iter_ty iterator = NULL;
		
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
void DlistAppend(dlist_ty *dest_Dlist, dlist_ty *src_Dlist)
{
	assert(dest_Dlist);
	assert(src_Dlist);
	
	if (DlistIsEmpty(src_Dlist))
	{
		return;
	}
	
	/* switch tail dummy of dest with first node in src */
	dest_dlist->tail->next = src_dlist->head->next->next;
	dest_dlist->tail->data = src_dlist->head->next->data;
	/* switch tail dummy of src with tail dummy of dest */
	src_dlist->tail->data = dest_Dlist;
	dest_dlist->tail = src_dlist->tail;
	/* make sure src list is empty */
	src_dlist->head->next->next = NULL;
	src_dlist->head->next->data = src_Dlist;
	src_dlist->tail = src_dlist->head->next;
	
}
/******************************************************************************/

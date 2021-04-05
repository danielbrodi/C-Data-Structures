/**********************************FILE-HEADER*********************************\
* File: dlist.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 05/04/2021							   								
* Version: 1.5 (After Review)				   								
* Reviewer: Danel						   								
* Description: Doubly Linked List Functions Implementations.			 
\******************************************************************************/

/************************** Macros Definitions ********************************/

#define ITER_TO_NODE_PTR(iter) ((dlist_node_ty *)iter)
#define NODE_PTR_TO_ITER(iter) (dlist_iter_ty)(iter)

/**************************** Inclusions **************************************/
#include <assert.h>		/* assert */
#include <stddef.h>		/* size_t, NULL */
#include <stdlib.h>		/* malloc, free */

#include "dlist.h"
#include "utils.h"		/* status_ty, bolean_ty*/

/************************ Global Definitions **********************************/
struct dlist
{
	dlist_iter_ty head;			/* points to the first element in the list */
	dlist_iter_ty tail;			/* points to the end dummy of the list */
};

struct dlist_node
{
	dlist_iter_ty previous;		/* points to the previous node in the list */
	dlist_iter_ty next;			/* points to the next node in the list */
	void *data;
};
/************************Functions Implementations*****************************/
/******************************************************************************/
dlist_ty *DlistCreate(void)
{
	dlist_ty *new_list = (dlist_ty *)malloc(sizeof(dlist_ty));
	if (NULL == new_list)
	{
		return (NULL);
	}
	
	/* create a dummy node that will represent the end of the list */
	new_list->tail = (dlist_node_ty *)malloc(sizeof(dlist_node_ty));
	if (NULL == new_list->tail)
	{
		free(new_list);
		new_list = NULL;
		
		return (NULL);
	}
	
	/* tail node points to null because it's the last node in the list */
	new_list->tail->data = (void *)new_list;
	new_list->tail->next = NULL;
	
	/* the first (and only) node of an empty list is the end dummy node
		Its previous points to the current head element of the list */
	new_list->head = new_list->tail;
	new_list->head->previous = (dlist_node_ty *)new_list;
	
	return (new_list);
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
	
	while (!DlistIsEmpty(dlist))
	{
		runner = DlistIteratorBegin(dlist);
		dlist->head = DlistIteratorNext(DlistIteratorBegin(dlist));
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
	
	return (NODE_PTR_TO_ITER(dlist->head));
}
/******************************************************************************/
dlist_iter_ty DlistIteratorEnd(const dlist_ty *dlist)
{
	assert(dlist);
	
	return (NODE_PTR_TO_ITER(dlist->tail));
}
/******************************************************************************/
dlist_iter_ty DlistIteratorNext(const dlist_iter_ty iter)
{
	assert(ITER_TO_NODE_PTR(iter));
	assert(ITER_TO_NODE_PTR(iter)->next);
	
	return (ITER_TO_NODE_PTR(iter)->next);
}
/******************************************************************************/
dlist_iter_ty DlistIteratorPrevious(const dlist_iter_ty iter)
{
	assert(ITER_TO_NODE_PTR(iter));
	assert(ITER_TO_NODE_PTR(iter)->previous);
	
	return (ITER_TO_NODE_PTR(iter)->previous);
}
/******************************************************************************/
void *DlistGetData(const dlist_iter_ty iter)
{
	assert(ITER_TO_NODE_PTR(iter));
	assert(ITER_TO_NODE_PTR(iter)->next);
	
	return (ITER_TO_NODE_PTR(iter)->data);
}
/******************************************************************************/
void DlistSetData(dlist_iter_ty iter, void *data)
{
	assert(ITER_TO_NODE_PTR(iter));
	assert(ITER_TO_NODE_PTR(iter)->next);
	assert(data);
	
	(ITER_TO_NODE_PTR(iter))->data = data;
}
/******************************************************************************/
boolean_ty DlistIteratorIsEqual(const dlist_iter_ty iter_a, 
											const dlist_iter_ty iter_b)
{
	assert(ITER_TO_NODE_PTR(iter_a));
	assert(ITER_TO_NODE_PTR(iter_b));
	
	return (ITER_TO_NODE_PTR(iter_a) == ITER_TO_NODE_PTR(iter_b));
}
/******************************************************************************/
dlist_iter_ty DlistInsertBefore(dlist_iter_ty iter, void *data)
{
	dlist_node_ty *new_node = NULL;
	
	assert(ITER_TO_NODE_PTR(iter));
	assert(data);

	new_node = (dlist_node_ty *)malloc(sizeof(dlist_node_ty));
	if (NULL == new_node)
	{
		return (iter); /* allocation failed */
	}
	
	/*	switch HEAD element: insert a copy node of the current head node after
		the current head element, and insert the new data to the current
		head element */
	if (ITER_TO_NODE_PTR(iter) == ITER_TO_NODE_PTR(iter)->previous->previous) 
	{
		new_node->data = ITER_TO_NODE_PTR(iter)->data;
		new_node->previous = ITER_TO_NODE_PTR(iter);
		new_node->next = ITER_TO_NODE_PTR(iter)->next;
		
		if (NULL != new_node->next)
		{
			new_node->next->previous = new_node;
		}
		
		/* if the list is empty update both tail and head pointers */						
		if (NULL == ITER_TO_NODE_PTR(iter)->next)
		{
			((dlist_ty *)(ITER_TO_NODE_PTR(iter))->data)->tail = new_node;
			((dlist_ty *)(ITER_TO_NODE_PTR(iter))->data)->head = iter;
		}
		
		ITER_TO_NODE_PTR(iter)->next = new_node;
		ITER_TO_NODE_PTR(iter)->data = data;
		
		return (iter);
	}
	/* no head element switching is required */
	else
	{
		new_node->data = data;
		new_node->previous = iter->previous;
		new_node->next = iter;
		
		new_node->previous->next = new_node;
		
		ITER_TO_NODE_PTR(iter)->previous = new_node;
	}
	
	return (new_node);
}
/******************************************************************************/
dlist_iter_ty DlistRemove(dlist_iter_ty iter)
{
	dlist_iter_ty new_node = NULL;
	
	assert(iter);
	assert(ITER_TO_NODE_PTR(iter)->next);
	
	ITER_TO_NODE_PTR(iter)->data = ITER_TO_NODE_PTR(iter)->next->data;
	
	new_node = (ITER_TO_NODE_PTR(iter))->next->next;
	
	if (NULL == new_node)
	{
		((dlist_ty *)(ITER_TO_NODE_PTR(iter))->data)->tail = 
														ITER_TO_NODE_PTR(iter);
	}
	
	free((ITER_TO_NODE_PTR(iter))->next);
	
	(ITER_TO_NODE_PTR(iter))->next = new_node;
	
	if (NULL != new_node)
	{
	(ITER_TO_NODE_PTR(new_node))->previous = ITER_TO_NODE_PTR(iter);
	}
	
	return (iter);
}
/******************************************************************************/
dlist_iter_ty DlistPushFront(dlist_ty *dlist, void *data)
{
	dlist_iter_ty pushed_node = NULL;
	
	assert (dlist);
	assert(data);
	
	pushed_node = DlistInsertBefore(DlistIteratorBegin(dlist), data);
	
	if (!DlistIteratorIsEqual(DlistIteratorBegin(dlist), pushed_node))
	{
		return (DlistIteratorEnd(dlist));
	}
	
	return (pushed_node);
}
/******************************************************************************/
dlist_iter_ty DlistPushBack(dlist_ty *dlist, void *data)
{
	assert(dlist);
	assert(data);

	return (DlistInsertBefore(DlistIteratorEnd(dlist), data));
}
/******************************************************************************/
void *DlistPopFront(dlist_ty *dlist)
{
	void *ret = NULL;
	
	assert(!DlistIsEmpty(dlist));
	
	ret = DlistGetData(DlistIteratorBegin(dlist));
	
	DlistRemove(DlistIteratorBegin(dlist));
	
	return (ret);
}
/******************************************************************************/
void *DlistPopBack(dlist_ty *dlist)
{
	void *ret = NULL;
	
	assert(!DlistIsEmpty(dlist));
	
	ret = DlistGetData(DlistIteratorPrevious(DlistIteratorEnd(dlist)));
	
	DlistRemove(DlistIteratorPrevious(DlistIteratorEnd(dlist)));
	
	return (ret);
}
/******************************************************************************/
boolean_ty DlistIsEmpty(const dlist_ty *dlist)
{
	dlist_node_ty *head_node = NULL, *tail_node = NULL;
	
	assert(dlist);
	
	head_node = DlistIteratorBegin(dlist);
	tail_node = DlistIteratorEnd(dlist);
	
	return (DlistIteratorIsEqual(head_node, tail_node));
}
/******************************************************************************/
size_t DlistSize(const dlist_ty *dlist)
{
	size_t counter = 0;
	
	dlist_node_ty *nodes_runner = NULL, *head_node = NULL;
	
	assert (dlist);
	
	head_node = ITER_TO_NODE_PTR(DlistIteratorBegin(dlist));
	nodes_runner = ITER_TO_NODE_PTR(DlistIteratorEnd(dlist));
	
	while (head_node != nodes_runner)
	{
		nodes_runner = DlistIteratorPrevious(nodes_runner);
		++counter;
	}
	
	return (counter);
}
/******************************************************************************/
dlist_iter_ty DlistFind(const dlist_iter_ty from_iter, 
								const dlist_iter_ty to_iter, 
										IsMatch_Func_ty match_func,
												void *param)
{
	dlist_node_ty *runner = NULL;
	
	assert(from_iter);
	assert(to_iter);
	assert(param);

	runner = ITER_TO_NODE_PTR(from_iter);
	
	while (runner != ITER_TO_NODE_PTR(to_iter))
	{
		if (TRUE == match_func(runner->data, param))
		{
			return (NODE_PTR_TO_ITER(runner));
		}
		runner = DlistIteratorNext(runner);
	}

	return (to_iter);
}
/******************************************************************************/
size_t DlistMultiFind(const dlist_iter_ty from_iter, 
								const dlist_iter_ty to_iter, 
									IsMatch_Func_ty match_func, void *param,
														dlist_ty *dlist_output)
{	
	dlist_node_ty *runner = NULL;
	size_t matches_counter = 0;
	
	assert(from_iter);
	assert(to_iter);
	assert(dlist_output);
	assert(param);
	
	runner = ITER_TO_NODE_PTR(from_iter);
	
	while (runner != ITER_TO_NODE_PTR(to_iter))
	{
		if (TRUE == match_func(runner->data, param))
		{
			DlistPushFront(dlist_output, runner->data);
			++matches_counter;
		}
		runner = DlistIteratorNext(runner);
	}

	return (matches_counter);
}
/******************************************************************************/
status_ty DlistForEach(dlist_iter_ty from_iter,
			const dlist_iter_ty to_iter, Action_Func_ty action_func,
													 void *param)
{
	dlist_node_ty *runner = NULL;
		
	assert(from_iter);
	assert(to_iter);
	
	runner = ITER_TO_NODE_PTR(from_iter);

	while (runner != ITER_TO_NODE_PTR(to_iter))
	{
		if (SUCCESS != action_func(runner->data, param))
		{
			return (FAILURE);
		}
		
		runner = DlistIteratorNext(runner);
	}
	
	return (SUCCESS);
}	
/******************************************************************************/
dlist_iter_ty DlistSplice(dlist_iter_ty dest_iter, 
								dlist_iter_ty src_from, dlist_iter_ty src_to)
{
	dlist_node_ty *temp = NULL;
	
	assert(dest_iter);
	assert(src_from);
	assert(src_to);
	assert(!DlistIteratorIsEqual(src_to, src_from));
	
	temp = ITER_TO_NODE_PTR(src_from)->previous;
	
	/* check if dest_iter is the HEAD element in its list */
	if (ITER_TO_NODE_PTR(dest_iter) == 
								ITER_TO_NODE_PTR(dest_iter)->previous->previous)
	{
		ITER_TO_NODE_PTR(dest_iter)->previous->previous = 
													ITER_TO_NODE_PTR(src_from);
	}
	else
	{
		ITER_TO_NODE_PTR(dest_iter)->previous->next = ITER_TO_NODE_PTR(src_from);
	}
	
	/* check if src_from is the HEAD element in its list */
	if (ITER_TO_NODE_PTR(src_from) == 
								ITER_TO_NODE_PTR(src_from)->previous->previous)
	{
		ITER_TO_NODE_PTR(src_from)->previous->previous = ITER_TO_NODE_PTR(src_to);
	}
	else
	{
		ITER_TO_NODE_PTR(src_from)->previous->next = ITER_TO_NODE_PTR(src_to);
	}

	ITER_TO_NODE_PTR(src_from)->previous = ITER_TO_NODE_PTR(dest_iter)->previous;
	
	ITER_TO_NODE_PTR(src_to)->previous->next = ITER_TO_NODE_PTR(dest_iter);
	
	ITER_TO_NODE_PTR(dest_iter)->previous = ITER_TO_NODE_PTR(src_to)->previous;
	
	ITER_TO_NODE_PTR(src_to)->previous = temp;
	
	return (src_from);
}
/******************************************************************************/

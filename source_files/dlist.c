/*********************************FILE__HEADER*********************************\
* File: dlist.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 05/04/2021							   								
* Version: 2.0 (Before Review)				   								
* Reviewer: Danel						   								
* Description: Doubly Linked List Functions Implementations.			 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>		/* assert */
#include <stddef.h>		/* size_t, NULL */
#include <stdlib.h>		/* malloc, free */

#include "utils.h"		/* status_ty, bolean_ty*/
#include "dlist.h"

/***************************** Macros Definitions *****************************/

#define ITER_TO_NODE_PTR(iter) ((dlist_node_ty *)iter)
#define NODE_PTR_TO_ITER(node) (dlist_iter_ty)(node)

/***************************** Global Definitions *****************************/
struct dlist
{
	dlist_node_ty *head;		/* points to the first element in the list */
	dlist_node_ty *tail;		/* points to the end dummy of the list */
};

struct dlist_node
{
	dlist_node_ty *previous;	/* points to the previous node in the list */
	dlist_node_ty *next;		/* points to the next node in the list */
	void *data;
};
/******************************************************************************/
/************************* Functions__Implementations *************************/
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
	
	/* tail node points to null because it's the last node in the list,
		its previous points to the list struct handler */
	new_list->tail->previous = (dlist_node_ty *)new_list;
	new_list->tail->next = NULL;
	new_list->tail->data = (void *)new_list;
		
	/* the first (and only) node of an empty list is the end dummy node,
		so the head points to the tail */
	new_list->head = new_list->tail;
	
	return (new_list);
}
/******************************************************************************/
void DlistDestroy(dlist_ty *dlist)
{	
	/* If the received dlist is NULL, no operation is performed */
	if (NULL != dlist)
	{
		while (!DlistIsEmpty(dlist))
		{
			DlistRemove(DlistIteratorBegin(dlist));
		}
		
		dlist->head = NULL;
		
		free(dlist->tail);
		dlist->tail = NULL;
		
		free(dlist);
		dlist = NULL;
	}
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
	assert(ITER_TO_NODE_PTR(iter)->next);	/* check if iter is the end dummy */
	
	return (NODE_PTR_TO_ITER((ITER_TO_NODE_PTR(iter)->next)));
}
/******************************************************************************/
dlist_iter_ty DlistIteratorPrevious(const dlist_iter_ty iter)
{
	assert(ITER_TO_NODE_PTR(iter));
	/* checks if iter is the head element in its list */
	assert(ITER_TO_NODE_PTR(iter)->previous->previous != ITER_TO_NODE_PTR(iter));
	
	return (NODE_PTR_TO_ITER((ITER_TO_NODE_PTR(iter)->previous)));
}
/******************************************************************************/
void *DlistGetData(const dlist_iter_ty iter)
{
	assert(ITER_TO_NODE_PTR(iter));
	assert(ITER_TO_NODE_PTR(iter)->next);	/* check if iter is the end dummy */
	
	return (ITER_TO_NODE_PTR(iter)->data);
}
/******************************************************************************/
void DlistSetData(dlist_iter_ty iter, void *data)
{
	assert(ITER_TO_NODE_PTR(iter));
	assert(ITER_TO_NODE_PTR(iter)->next);	/* check if iter is the end dummy */
	assert(data);
	
	(ITER_TO_NODE_PTR(iter))->data = data;
}
/******************************************************************************/
boolean_ty DlistIteratorIsEqual(const dlist_iter_ty iter_a, 
											const dlist_iter_ty iter_b)
{
	assert(ITER_TO_NODE_PTR(iter_a));
	assert(ITER_TO_NODE_PTR(iter_b));
	
	/* returns TRUE if both iterators point to the same element
		otherwise returns FALSE */
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
		return (iter); /* memory allocation failed */
	}
	
	/*
	The previous of the head element in a list points to the struct
	handler of the list.
	The previous of the previous of the head element which is:
	"head->previous->previous" points to the element itself.
	The reason for that is because the "head" struct member in a
	list's structure is located at offset 0 in the memory.
	
	Also, the "previous" struct member in a node's structure is also located at
	offset 0.
	
	Thus, if a pointer to a list is casted and called as a pointer to a 
	node, a pointer to the "previous" member of it won't result in an error
	although there is no "previous" member in a list's structure.
	It will actually point to the "head" member of the list,
	because both "previous" and "head" members are located at offset 0 of
	their structures. So when the compiler will see a casted call to the list,
	that seems to look like a call to a node, and to its first struct member,
	it will access the member that is located in offset 0 of the struct,
	which means the first member, which means the "head" member of the list.
	
	So the only reason for the previous of a previous of an element to be
	the element itself, is if the element is the head node of its list.
	*/	
	if (ITER_TO_NODE_PTR(iter) == ITER_TO_NODE_PTR(iter)->previous->previous)
	{
		/*	the head's previous must point to the list's data structure	*/
		new_node->previous = (dlist_node_ty *)(iter->previous);
		/* 
		make the head pointer in the list structure to point to the new_node
		as the new head element of the list.
		*/
		new_node->previous->previous = new_node;
	}
	else
	{
		new_node->previous = ITER_TO_NODE_PTR(iter)->previous;
		new_node->previous->next = new_node;
	}
	
	/* place the new node before the node that is pointed by iter */
	new_node->data = data;
	new_node->next = ITER_TO_NODE_PTR(iter);
	
	ITER_TO_NODE_PTR(iter)->previous = new_node;

	return (NODE_PTR_TO_ITER(new_node));
}
/******************************************************************************/
dlist_iter_ty DlistRemove(dlist_iter_ty iter)
{
	dlist_node_ty *ret_node = NULL;
	
	assert(iter);
	assert(ITER_TO_NODE_PTR(iter)->next);	/* check if iter is the end dummy */
	
	/* 
	if the received node is the head element of its list,
	update the head element as the element that located right after the 
	current head.
	#	Look at line 162 for elaborated explanation.	#
	*/
	if (ITER_TO_NODE_PTR(iter)->previous->previous == ITER_TO_NODE_PTR(iter))
	{
		ITER_TO_NODE_PTR(iter)->next->previous = 
							(dlist_node_ty *)(ITER_TO_NODE_PTR(iter)->previous);
		ITER_TO_NODE_PTR(iter)->previous->previous = 
												ITER_TO_NODE_PTR(iter)->next;
	}
	else
	{
	ITER_TO_NODE_PTR(iter)->previous->next = ITER_TO_NODE_PTR(iter)->next;
	ITER_TO_NODE_PTR(iter)->next->previous = ITER_TO_NODE_PTR(iter)->previous;
	}
	
	ret_node = ITER_TO_NODE_PTR(iter)->next;
	
	free(iter);
	iter = NULL;
	
	return (NODE_PTR_TO_ITER(ret_node));
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
	dlist_node_ty *head = NULL, *tail = NULL;
	
	assert(dlist);
	
	head = ITER_TO_NODE_PTR(DlistIteratorBegin(dlist));
	tail = ITER_TO_NODE_PTR(DlistIteratorEnd(dlist));
	
	return (DlistIteratorIsEqual(NODE_PTR_TO_ITER(head), NODE_PTR_TO_ITER(tail)));
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
		nodes_runner = ITER_TO_NODE_PTR(
						DlistIteratorPrevious(NODE_PTR_TO_ITER(nodes_runner)));
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
	
	assert(ITER_TO_NODE_PTR(from_iter));
	assert(ITER_TO_NODE_PTR(to_iter));
	assert(param);

	runner = ITER_TO_NODE_PTR(from_iter);
	
	while (runner != ITER_TO_NODE_PTR(to_iter))
	{
		if (TRUE == match_func(runner->data, param))
		{
			return (NODE_PTR_TO_ITER(runner));
		}
		runner = ITER_TO_NODE_PTR(DlistIteratorNext(NODE_PTR_TO_ITER(runner)));
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
	
	assert(ITER_TO_NODE_PTR(from_iter));
	assert(ITER_TO_NODE_PTR(to_iter));
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
		runner = ITER_TO_NODE_PTR(DlistIteratorNext(NODE_PTR_TO_ITER(runner)));
	}

	return (matches_counter);
}
/******************************************************************************/
status_ty DlistForEach(dlist_iter_ty from_iter,
			const dlist_iter_ty to_iter, Action_Func_ty action_func,
													 void *param)
{
	dlist_node_ty *runner = NULL;
		
	assert(ITER_TO_NODE_PTR(from_iter));
	assert(ITER_TO_NODE_PTR(to_iter));
	
	runner = ITER_TO_NODE_PTR(from_iter);

	while (runner != ITER_TO_NODE_PTR(to_iter))
	{
		if (SUCCESS != action_func(runner->data, param))
		{
			return (FAILURE);
		}
		
		runner = ITER_TO_NODE_PTR(DlistIteratorNext(NODE_PTR_TO_ITER(runner)));
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

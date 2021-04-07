/*********************************FILE__HEADER*********************************\
* File: sorted_list.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 07/04/2021							   								
* Version: 1.0 (Before Review)				   								
* Reviewer: Ariel						   								
* Description: Sorted Linked List Functions Implementations.			 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>		/*	assert			*/
#include <stddef.h>		/*	size_t, NULL	*/
#include <stdlib.h>		/*	malloc, free	*/

#include "utils.h"		/*	status_ty, bolean_ty			*/
#include "dlist.h"		/*	doubly linked list API wrapper	*/
#include "sorted_list.h"

/***************************** Macros Definitions *****************************/

#define D_ITER_TO_S_ITER(iter) (sorted_list_iter_ty)(iter)
#define S_ITER_TO_D_ITER(iter) (dlist_iter_ty)(iter)
#define UNUSED(x) (void)(x)

/***************************** Global Definitions *****************************/
struct sorted_list
{
	dlist_ty *list;	/* doubly linked list with a dummy node in the end of it */
	Compare_Func_ty compare_func; /* will sort the elements by its criteria */
};
/******************************************************************************/
/************************* Functions__Implementations *************************/
/******************************************************************************/
sorted_list_ty *SortedListCreate(Compare_Func_ty compare_func)
{
	sorted_list_ty *new_list = (sorted_list_ty *)malloc(sizeof(sorted_list_ty));
	if (NULL == new_list)
	{
		return(NULL);
	}
	
	new_list->list = DlistCreate();
	if (NULL == new_list->list)
	{
		free(new_list);
		new_list = NULL;
		
		return(NULL);
	}
	
	new_list->compare_func = compare_func;
	
	return(new_list);
}
/******************************************************************************/
void SortedListDestroy(sorted_list_ty *sorted_list)
{
	assert(sorted_list);
	assert(sorted_list->list);
	
	DlistDestroy(sorted_list->list);
	sorted_list->list = NULL;
	
	free(sorted_list);
	sorted_list = NULL;
}
/******************************************************************************/
sorted_list_iter_ty SortedListIteratorBegin(const sorted_list_ty *sorted_list)
{
	assert(sorted_list);
	
	return (D_ITER_TO_S_ITER(DlistIteratorBegin(sorted_list->list)));
}
/******************************************************************************/
sorted_list_iter_ty SortedListIteratorEnd(const sorted_list_ty *sorted_list)
{
	assert(sorted_list);
	
	return (D_ITER_TO_S_ITER(DlistIteratorEnd(sorted_list->list)));
}
/******************************************************************************/
sorted_list_iter_ty SortedListIteratorNext(const sorted_list_iter_ty iter)
{	
	return D_ITER_TO_S_ITER(DlistIteratorNext(S_ITER_TO_D_ITER(iter)));
}
/******************************************************************************/
sorted_list_iter_ty SortedListIteratorPrevious(const sorted_list_iter_ty iter)
{
	return D_ITER_TO_S_ITER(DlistIteratorPrevious(S_ITER_TO_D_ITER(iter)));
}
/******************************************************************************/
boolean_ty SortedListIteratorIsEqual(const sorted_list_iter_ty iter_a, 
const sorted_list_iter_ty iter_b)
{
	return (DlistIteratorIsEqual(
							S_ITER_TO_D_ITER(iter_a), S_ITER_TO_D_ITER(iter_b)));
}
/******************************************************************************/
void *SortedListGetData(const sorted_list_iter_ty iter)
{
	return DlistGetData(S_ITER_TO_D_ITER(iter));
}
/******************************************************************************/
sorted_list_iter_ty SortedListRemove(sorted_list_iter_ty iter)
{

	return (D_ITER_TO_S_ITER(DlistRemove(S_ITER_TO_D_ITER(iter))));
}
/******************************************************************************/
void *SortedListPopFront(sorted_list_ty *sorted_list)
{
	assert (sorted_list);
	
	return (DlistPopFront(sorted_list->list));
}
/******************************************************************************/
void *SortedListPopBack(sorted_list_ty *sorted_list)
{
	assert (sorted_list);
	
	return (DlistPopBack(sorted_list->list));
}
/******************************************************************************/
boolean_ty SortedListIsEmpty(const sorted_list_ty *sorted_list)
{
	assert (sorted_list);
	
	return (DlistIsEmpty(sorted_list->list));
}
/******************************************************************************/
status_ty IsValidElem(void *data, const void *param)
{
	UNUSED(data);
	++(*(int *)param);
	return (SUCCESS);
}
/******************************************************************************/
size_t SortedListSize(const sorted_list_ty *sorted_list)
{
	size_t counter = 0;
	sorted_list_iter_ty head = NULL;
	sorted_list_iter_ty tail = NULL;
	
	assert(sorted_list);
	
	head = SortedListIteratorBegin(sorted_list);
	tail = SortedListIteratorEnd(sorted_list);
	
	SortedListForEach(head, tail, IsValidElem, (void *)&counter);
		 									 
	return (counter);
}
/******************************************************************************/
sorted_list_iter_ty SortedListInsert(sorted_list_ty *list, void *data)
{
	sorted_list_iter_ty runner = NULL;
	sorted_list_iter_ty tail = NULL;
	sorted_list_iter_ty ret = NULL;
	
	assert(list);
	
	runner = SortedListIteratorBegin(list);
	tail = SortedListIteratorEnd(list);
	
	while (!SortedListIteratorIsEqual(tail, runner) && 
					list->compare_func(SortedListGetData(runner), data) >= 0)
	{
		runner = SortedListIteratorNext(runner);
	}
	
	ret = D_ITER_TO_S_ITER(DlistInsertBefore(S_ITER_TO_D_ITER(runner), data));
	
	if (SortedListIteratorIsEqual(ret, runner))
	{
		return (tail);	/* insert failed			*/
	}
	
	return (ret); 		/* return the new element	*/
}
/******************************************************************************/
sorted_list_iter_ty SortedListFind(const sorted_list_ty *list, 
                            const sorted_list_iter_ty from_iter, 
								const sorted_list_iter_ty to_iter,
												void *param)
{
	sorted_list_iter_ty runner = NULL;
	int status = 1;	/*	for a positive indication	*/
	
	assert(list);
	assert(from_iter);
	assert(to_iter);
	
	runner = SortedListIteratorBegin(list);
	
	/* 
	loop through the list till a matching element will be found
	or until the runner will reach elements that should be located after
	the given data, which means they will never match it.
	*/
	while (runner != to_iter && status > 0)
	{
		status = list->compare_func(SortedListGetData(runner), param);
		runner = SortedListIteratorNext(runner);
	}
	
	if (0 == status)
	{
		return (SortedListIteratorPrevious(runner));	/*	data found	*/
	}
	
	return (to_iter);	/* no matching data is found in the list	*/
}
/******************************************************************************/
sorted_list_iter_ty SortedListFindIf(const sorted_list_iter_ty from_iter, 
								const sorted_list_iter_ty to_iter, 
					Is_Match_Func_ty match_func, void *param)
{
	sorted_list_iter_ty runner = NULL;

	assert(from_iter);
	assert(to_iter);

	runner = from_iter;

	while (!SortedListIteratorIsEqual(runner, to_iter))
	{
		if (TRUE == match_func(SortedListGetData(runner), param))
		{
			return (runner);
		}
		runner = SortedListIteratorNext(runner);
	}

	return (to_iter);
}
/******************************************************************************/
status_ty SortedListForEach(sorted_list_iter_ty from_iter,
			const sorted_list_iter_ty to_iter, Action_Function_ty action_func,
													 void *param)
{
	sorted_list_iter_ty runner = NULL;

	assert(from_iter);
	assert(to_iter);

	runner = from_iter;

	while (!SortedListIteratorIsEqual(runner, to_iter))
	{
		if (SUCCESS != action_func(SortedListGetData(runner), param))
		{
		return (FAILURE);
		}

		runner = SortedListIteratorNext(runner);
	}

	return (SUCCESS);
}				 
/******************************************************************************/
void SortedListMerge(sorted_list_ty *dest_list, 
						sorted_list_ty *src_list)
{
	sorted_list_iter_ty dest_runner = NULL;
	sorted_list_iter_ty src_runner = NULL;
	sorted_list_iter_ty dest_tail = NULL;
	sorted_list_iter_ty src_tail = NULL;
	
	assert(dest_list);
	assert(src_list);

	dest_runner = SortedListIteratorBegin(dest_list);
	src_runner = SortedListIteratorBegin(src_list);
	
	dest_tail = SortedListIteratorEnd(dest_list);
	src_tail = SortedListIteratorEnd(src_list);
	
	while (!SortedListIteratorIsEqual(dest_runner, 
			SortedListIteratorEnd(dest_list)) && !SortedListIsEmpty(src_list))
	{
		while ((dest_list->compare_func(
			SortedListGetData(dest_runner), SortedListGetData(src_runner)) < 0)
												&& src_runner != src_tail)
		{
			src_runner = SortedListIteratorNext(src_runner);
		}
		
		if (!SortedListIteratorIsEqual(src_runner,
											 SortedListIteratorBegin(src_list)))
		{
			DlistSplice(S_ITER_TO_D_ITER(dest_runner),
			SortedListIteratorBegin(src_list), S_ITER_TO_D_ITER(src_runner));
			
			src_runner = SortedListIteratorBegin(src_list);
		}
		
		dest_runner = SortedListIteratorNext(dest_runner);
	}
	
	if (!SortedListIsEmpty(src_list))
	{
		DlistSplice(S_ITER_TO_D_ITER(SortedListIteratorEnd(dest_list)),
			SortedListIteratorBegin(src_list), src_tail);
	}
}
/******************************************************************************/

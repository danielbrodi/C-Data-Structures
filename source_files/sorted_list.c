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

#include "utils.h"		/*	status_ty, bolean_ty				*/
#include "dlist.h"		/*	doubly linked list API wrapper		*/
#include "sorted_list.h"

/***************************** Macros Definitions *****************************/

#define D_ITER_TO_S_ITER(iter) (sorted_list_iter_ty)(iter)
#define S_ITER_TO_D_ITER(iter) (dlist_iter_ty)(iter)

/***************************** Global Definitions *****************************/
struct sorted_list
{
	dlist_ty *list;	/* doubly linked list with a dummy node in the end of it */
	Compare_Func_ty *compare_func; /* will sort the elements by its criteria */
};

/**************************** Forward Declarations ****************************/
int CompareElements(const void *data1, const void *data2);

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
		new_list = NULL:
		
		return(NULL);
	}
	
	new_list->compare = CompareElements;
	
	return(new_queue);
}
/******************************************************************************/
int CompareElements(const void *data1, const void *data2)
{
	assert(data1);
	assert(data2);
	
	return ((int)(long)(data2) - (int)(long)(data1));
}
/******************************************************************************/
void SortedListDestroy(sorted_list_ty *sorted_list)
{
	assert(sorted_list);
	assert(sorted_list_>list);
	
	DlistDestory(sorted_list->list);
	sorted_list->list = NULL;
	
	free(sorted_list);
	sorted_list = NULL;
}
/******************************************************************************/
sorted_list_iter_ty SortedListIteratorBegin(const sorted_list_ty *sorted_list)
{
	assert(sorted_list);
	
	return (D_ITER_TO_S_ITER(DlistIteratorTobegin(sorted_list->list)));
}
/******************************************************************************/
sorted_list_iter_ty SortedListIteratorEnd(const sorted_list_ty *sorted_list)
{
	assert(sorted_list);
	
	return (D_ITER_TO_S_ITER(DlistIteratorTobegin(sorted_list->list)));
}
/******************************************************************************/
sorted_list_iter_ty SortedListIteratorNext(const sorted_list_iter_ty iter)
{	
	return D_ITER_TO_S_ITER(DlistIteratorTonext(S_ITER_TO_D_ITER(iter)));
}
/******************************************************************************/
sorted_list_iter_ty SortedListIteratorPrevious(const sorted_list_iter_ty iter)
{
	return D_ITER_TO_S_ITER(DlistIteratorToPrevious(S_ITER_TO_D_ITER(iter)));
}
/******************************************************************************/
boolean_ty SortedListIteratorIsEqual(const sorted_list_iter_ty iter_a, 
const sorted_list_iter_ty iter_b)
{
	return (DlistIteratorIsEqual(
							S_ITER_TO_D_ITER(iter_a), S_ITER_TO_D_ITER(ite_b)));
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
size_t SortedListSize(const sorted_list_ty *sorted_list)
{
	size_t counter = 0;
	sorted_list_iter_ty runner = NULL;
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
	int status = 1;		/*	for a positive indication	*/
	
	assert(list);
	assert(data);
	
	runner = SortedListIteratorBegin(list);
	tail = SortedListIteratorEnd(list);
	
	while (tail != runner && status > 0)
	{
		status = list->compare_func(SortedListGetData(runner), data);
		runner = SortedListIteratorNext(runner);
	}
	
	/* insert as the last element in the list if the runner reached the end */
	if (SortedListIteratorIsEqual(tail, runner))
	{
		return (D_ITER_TO_S_ITER(DlistPushBack(list->list, data)));
	}
	
	ret = D_ITER_TO_S_ITER(DlistInsertBefore(
				S_ITER_TO_D_ITER(SortedListIteratorPrevious(runner)), data));
	
	if (SortedListIteratorIsEqual(ret, SortedListIteratorPrevious(runner)))
	{
		return (tail);	/* insert failed			*/
	}
	
	return (ret); 		/* return the new element	*/
	
	
/******************************************************************************/
sorted_list_iter_ty SortedListFind(const sorted_list_ty *list, 
                            const sorted_list_iter_ty from_iter, 
								const sorted_list_iter_ty to_iter,
												void *param)
{
	sorted_list_iter_ty runner = NULL;
	sorted_list_iter_ty tail = NULL;
	sorted_list_iter_ty ret = NULL;
	int status = 1;	/*	for a positive indication	*/
	
	assert(list);
	assert(from_iter);
	assert(to_iter);
	assert(param);
	
	/* 
	loop through the list till a matching element will be found
	or until the runner will reach elements that should be located after
	the given data, which means they will never match it.
	*/
	while (runner != to_iter && status > 0)
	{
		status = list->compare_func(SortedListGetData(runner), data);
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
										Is_Match_Func_ty match_func,
												void *param)
{
	return (D_ITER_TO_S_ITER(
	DlistFind(S_ITER_TO_D_ITER(from_iter), S_ITER_TO_D_ITER(to_iter),
														match_func, param)));
}
/******************************************************************************/
status_ty SortedListForEach(sorted_list_iter_ty from_iter,
			const sorted_list_iter_ty to_iter, Action_Funcion_ty action_func,
													 void *param)
{
	return (DlistForEach(S_ITER_TO_D_ITER(from_iter), S_ITER_TO_D_ITER(to_iter),
														action_func, param));
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
	
	while (dest_runner != dest_tail && src_runner != src_tail)
	{
		while ((dest_list->compare_func(
			SortedListGetData(dest_runner), SortedListGetData(src_runner)) < 0)
												&& src_runner != src_tail)
		{
			src_runner = SortedListIteratorNext(src_runner);
		}
		
		DlistSplice(S_ITER_TO_D_ITER(dest_runner),
			SortedListIteratorBegin(src_list), S_ITER_TO_D_ITER(src_runner));
		
		src_runner = SortedListIteratorBegin(src_list);
		dest_runner = SortedListIteratorNext(dest_runner);
	}	
}
/******************************************************************************/

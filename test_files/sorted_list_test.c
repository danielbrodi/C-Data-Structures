/*********************************FILE__HEADER*********************************\
* File: sorted_list_test.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 07/04/2021						   								
* Version: Beta				   								
* Reviewer: Ariel						   								
* Description: Sorted Linked List API's Functions Testings.		 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>	/*	assert	*/
#include <stddef.h>	/*	size_t	*/
#include <stdio.h>	/* printf, NULL */
#include <stdlib.h> /* rand, srand */
#include <string.h> /* strcmp */
#include <time.h>	/* time */

#include "utils.h" /* status_ty, boolean_ty, ANSI_COLOR_*/
#include "sorted_list.h"

/***************************** Macros Definitions *****************************/
/* print colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 1 to 100 */
#define RANDOM_NUM ((rand() % 100) + 1)

#define UNUSED(x) (void)(x)
/**************************** Forward Declarations ****************************/
int CompareElements(const void *data1, const void *data2);
static void SortedListCreateTest(sorted_list_ty *sorted_list);
static void SortedListDestroyTest(sorted_list_ty *list1, sorted_list_ty *list2);
static void SortedListIteratorBeginTest(sorted_list_ty *sorted_list);
static void SortedListInsertTest(sorted_list_ty *sorted_list);
static void SortedListRemoveTest(sorted_list_ty *sorted_list);
static void SortedListIsEmptyTest(sorted_list_ty *sorted_list);
static void SortedListPopFrontTest(sorted_list_ty *sorted_list);
static void SortedListPopBackTest(sorted_list_ty *sorted_list);
static void SortedListFindTest(sorted_list_ty *sorted_list);
static void SortedListFindIfTest(sorted_list_ty *sorted_list);
static boolean_ty IsMatch(const void *data, void *param);
static boolean_ty IsDividedBy(const void *data, const void *param);
static void SortedListForEachTest(sorted_list_ty *sorted_list);
static status_ty PrintList(void *data, const void *param);
static void SortedListMergeTest(sorted_list_ty *dest_list,
													sorted_list_ty *src_list);
/******************************************************************************/
/******************************* Main__Function *******************************/
int main()	
{
	/* Intializes two empty new sorted lists */
	sorted_list_ty *dest_list = SortedListCreate(CompareElements);
	sorted_list_ty *src_list = SortedListCreate(CompareElements);
	
	/* Intializes random number generator */
	srand(time(0));
	
	SortedListCreateTest(dest_list);
	SortedListIteratorBeginTest(dest_list);
	SortedListInsertTest(dest_list);
	SortedListRemoveTest(dest_list);
	SortedListIsEmptyTest(dest_list);
	SortedListPopFrontTest(dest_list);
	SortedListPopBackTest(dest_list);
	SortedListFindTest(dest_list);
	SortedListFindIfTest(dest_list);
	SortedListForEachTest(dest_list);
	SortedListMergeTest(dest_list, src_list);
	SortedListDestroyTest(dest_list, src_list);
	
	return (0);
}
/******************************************************************************/
/************************Test Functions Implementations************************/
/******************************************************************************/
static void SortedListCreateTest(sorted_list_ty *sorted_list)
{
	printf("\nSorted List Creation Test: ");
	NULL == sorted_list ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
static void SortedListDestroyTest(sorted_list_ty *list1, sorted_list_ty *list2)
{
	SortedListDestroy(list1);
	SortedListDestroy(list2);
	printf (ANSI_COLOR_CYAN "\nThe Lists have been deleted\n\n" 
															ANSI_COLOR_RESET);
}
/******************************************************************************/
static void SortedListIteratorBeginTest(sorted_list_ty *sorted_list)
{
	printf("Iter To Begin/End/IsEqual Test: ");
	SortedListIteratorIsEqual(SortedListIteratorBegin(sorted_list),
	 		SortedListIteratorEnd(sorted_list)) ? PRINT_SUCCESS : PRINT_FAILURE;
	 											  
}
/******************************************************************************/
static void SortedListInsertTest(sorted_list_ty *sorted_list)
{	
	boolean_ty is_working = TRUE;
	sorted_list_iter_ty new_node = NULL;
	sorted_list_iter_ty tail = SortedListIteratorEnd(sorted_list);
	
	size_t num_of_inserts = 10, i = 0;
	
	printf("Sorted List Insert+Next+GetData Test: ");
	
	for(i = 0; i < num_of_inserts; ++i)
	{
		new_node = SortedListInsert(sorted_list, (void *)(long)RANDOM_NUM);
		/*
		if the tail node is the return value of the insert function,
		it indicates that the insertation has been failed.
		*/
		is_working *= !SortedListIteratorIsEqual(tail, new_node);
	}
	
	new_node = SortedListIteratorBegin(sorted_list);
	
	/* check if the list is sorted as needed by the criteria */
	while (num_of_inserts - 1 > 0 && CompareElements(
					SortedListGetData(new_node),
					SortedListGetData(SortedListIteratorNext(new_node))) >= 0)
	{
		new_node = SortedListIteratorNext(new_node);
		--num_of_inserts;
	}
	
	is_working *= SortedListIteratorIsEqual(
										tail, SortedListIteratorNext(new_node));
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
	 											
}
/******************************************************************************/
static void SortedListRemoveTest(sorted_list_ty *sorted_list)
{
	boolean_ty is_working = TRUE;
	size_t original_size = SortedListSize(sorted_list);
	printf("Sorted List Remove Test: ");
	
	while(original_size > 0)
	{
		SortedListRemove(SortedListIteratorBegin(sorted_list));
		is_working *= (original_size - 1) == SortedListSize(sorted_list);
		--original_size;
	}
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
	
}
/******************************************************************************/
static void SortedListIsEmptyTest(sorted_list_ty *sorted_list)
{
	printf("Sorted List IsEmpty Test: ");
	TRUE == SortedListIsEmpty(sorted_list) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void SortedListPopFrontTest(sorted_list_ty *sorted_list)
{
	boolean_ty is_working = TRUE;
	
	void *popped_value = NULL;
	
	size_t original_size = 0;
	
	int num1 = 4, num2 = 0, num3 = 2;
	
	SortedListInsert(sorted_list, (void *)(long)num1);
	SortedListInsert(sorted_list, (void *)(long)num2);
	SortedListInsert(sorted_list, (void *)(long)num3);
	
	original_size = SortedListSize(sorted_list);
	
	printf("Sorted List PopFront Test: ");
	
	popped_value = SortedListPopFront(sorted_list);
	is_working *= original_size - 1 == SortedListSize(sorted_list) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num2);
	
	popped_value = SortedListPopFront(sorted_list);
	is_working *= original_size - 2 == SortedListSize(sorted_list) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num3);
	
	popped_value = SortedListPopFront(sorted_list);
	is_working *= original_size - 3 == SortedListSize(sorted_list) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num1);
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void SortedListPopBackTest(sorted_list_ty *sorted_list)
{
	boolean_ty is_working = TRUE;
	
	void *popped_value = NULL;
	
	size_t original_size = 0;
	
	int num1 = 4, num2 = 0, num3 = 2;
	
	SortedListInsert(sorted_list, (void *)(long)num1);
	SortedListInsert(sorted_list, (void *)(long)num2);
	SortedListInsert(sorted_list, (void *)(long)num3);
	
	original_size = SortedListSize(sorted_list);
	
	printf("Sorted List PopBack Test: ");
	
	popped_value = SortedListPopBack(sorted_list);
	is_working *= original_size - 1 == SortedListSize(sorted_list) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num1);
	
	popped_value = SortedListPopBack(sorted_list);
	is_working *= original_size - 2 == SortedListSize(sorted_list) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num3);
	
	popped_value = SortedListPopBack(sorted_list);
	is_working *= original_size - 3 == SortedListSize(sorted_list) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num2);
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void SortedListFindTest(sorted_list_ty *sorted_list)
{
	sorted_list_iter_ty head = SortedListIteratorBegin(sorted_list);
	sorted_list_iter_ty tail = SortedListIteratorEnd(sorted_list);
	sorted_list_iter_ty ret = NULL;
	
	int num1 = RANDOM_NUM, num2 = -10, num3 = RANDOM_NUM;
	
	printf("Sorted List Find Test: ");
	
	SortedListInsert(sorted_list, (void *)(long)num1);
	SortedListInsert(sorted_list, (void *)(long)num2);
	SortedListInsert(sorted_list, (void *)(long)num3);
	
	ret = SortedListFind(sorted_list, head, tail, (void *)(long)num2);
	
	if(SortedListIteratorIsEqual(ret, tail))
	{
		PRINT_FAILURE;
	}
	
	if(IsMatch(SortedListGetData(ret), (void *)(long)num2))
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
	}
	
	SortedListPopFront(sorted_list);
	SortedListPopFront(sorted_list);
	SortedListPopFront(sorted_list);
}
/******************************************************************************/
static void SortedListFindIfTest(sorted_list_ty *sorted_list)
{
	boolean_ty is_working = TRUE;
	
	sorted_list_iter_ty head = NULL;
	sorted_list_iter_ty tail = SortedListIteratorEnd(sorted_list);
	sorted_list_iter_ty ret_node = NULL;
	
	size_t num_of_inserts = 10, i = 0;
	int num_to_divide_by = 2;
	
	printf("Sorted List FindIf Test: ");
	
	for(i = 0; i < num_of_inserts; ++i)
	{
		ret_node = SortedListInsert(sorted_list, (void *)(long)(RANDOM_NUM));
		/*
		if the tail node is the return value of the insert function,
		it indicates that the insertation has been failed.
		*/
		is_working *= !SortedListIteratorIsEqual(tail, ret_node);
	}
	
	head = SortedListIteratorBegin(sorted_list);
	
	ret_node = SortedListFindIf(head, tail, IsDividedBy,
	 											(void *)(long)num_to_divide_by);
	
	is_working *= !SortedListIteratorIsEqual(ret_node, tail);
	if (!is_working)
	{	
		PRINT_FAILURE;
		return;
	}
	
	is_working *= IsDividedBy(SortedListGetData(ret_node),
	 											(void *)(long)num_to_divide_by);
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void SortedListForEachTest(sorted_list_ty *sorted_list)
{
	int x = -1;
	status_ty result = FAILURE;
	printf("Printing List:" ANSI_COLOR_CYAN " *list");
	result = SortedListForEach(SortedListIteratorBegin(sorted_list), 
				SortedListIteratorEnd(sorted_list), PrintList, (void *)(long)x);
	printf(" <--> END_DUMMY -> NULL" ANSI_COLOR_RESET);
	printf("\nForEach Test(PrintList): ");
	(SUCCESS == result) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
int CompareElements(const void *data1, const void *data2)
{	
	return ((int)(long)(data2) - (int)(long)(data1));
}
/******************************************************************************/
static boolean_ty IsMatch(const void *data, void *param)
{	
	return (((int)(long)data == (int)(long)param));
}
/******************************************************************************/
static boolean_ty IsDividedBy(const void *data, const void *param)
{	
	return (0 == ((int)(long)data % (int)(long)param));
}
/******************************************************************************/
static status_ty PrintList(void *data, const void *param)
{
	UNUSED(param);
	if (NULL == data || NULL == param)
	{
		return (FAILURE);
	}
	
	printf(" <--> %d", (int)(long)data);
	return (SUCCESS);
}
/******************************************************************************/
static void SortedListMergeTest(sorted_list_ty *dest_list,
													sorted_list_ty *src_list)
{
	boolean_ty is_working = TRUE;
	void *popped_value = NULL;
	
	int num1 = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5, num6 = 6;
	
	printf("SortedList Merge Test: ");
	
	/** Empty both lists **/
	while(!SortedListIsEmpty(dest_list))
	{
		SortedListRemove(SortedListIteratorBegin(dest_list));
	}
	
	while(!SortedListIsEmpty(src_list))
	{
		SortedListRemove(SortedListIteratorBegin(src_list));
	}
	
	/* fill up dest list */
	SortedListInsert(dest_list, (void *)(long)num1);
	SortedListInsert(dest_list, (void *)(long)num2);
	SortedListInsert(dest_list, (void *)(long)num3);

	/* fill up src list */
	SortedListInsert(src_list, (void *)(long)num4);
	SortedListInsert(src_list, (void *)(long)num5);
	SortedListInsert(src_list, (void *)(long)num6);
	
	
	printf("\nPRINTING DEST:\n");
	SortedListForEach(SortedListIteratorBegin(dest_list), 
				SortedListIteratorEnd(dest_list), PrintList, (void *)(long)1);
	
	printf("\nPRINTING SRC:\n");
	SortedListForEach(SortedListIteratorBegin(src_list), 
				SortedListIteratorEnd(src_list), PrintList, (void *)(long)1);
	
	printf("\nSIZE OF DEST: \n%lu\n", SortedListSize(src_list));
	printf("\nSIZE OF SRC: \n%lu\n", SortedListSize(src_list));
	
	
	
	/* dest list: 1,2,3 && src list: 4,5,6 */

	SortedListMerge(dest_list, src_list);
	
	/* 
	After Merge the expected result is an empty src_list,
	and the following dest_list: 1,2,3,4,5,6.
	 */
	printf("\nPRINTING DEST:\n");
	SortedListForEach(SortedListIteratorBegin(dest_list), 
				SortedListIteratorEnd(dest_list), PrintList, (void *)(long)1);
	popped_value = SortedListPopBack(dest_list);
	is_working *= IsMatch(popped_value, (void *)(long)num6);
	
	popped_value = SortedListPopBack(dest_list);
	is_working *= IsMatch(popped_value, (void *)(long)num5);
	
	popped_value = SortedListPopBack(dest_list);
	is_working *= IsMatch(popped_value, (void *)(long)num4);
	
	popped_value = SortedListPopBack(dest_list);
	is_working *= IsMatch(popped_value, (void *)(long)num3);
	
	popped_value = SortedListPopBack(dest_list);
	is_working *= IsMatch(popped_value, (void *)(long)num2);
	
	popped_value = SortedListPopBack(dest_list);
	is_working *= IsMatch(popped_value, (void *)(long)num1);
	
	printf("\nPRINTING DEST:\n");
	SortedListForEach(SortedListIteratorBegin(dest_list), 
				SortedListIteratorEnd(dest_list), PrintList, (void *)(long)1);
													
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;		
}
/******************************************************************************/

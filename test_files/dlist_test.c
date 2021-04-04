/**********************************FILE-HEADER*********************************\
* File: dlist_test.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 04/04/2021						   								
* Version: 1.0 (Before Review)				   								
* Reviewer: Danel						   								
* Description: Doubly Linked List API's Functions Testings.		 
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stddef.h>	/* size_t */
#include <stdio.h>	/* printf, NULL */
#include <stdlib.h> /* rand, srand */
#include <string.h> /* strcmp */
#include <time.h>	/* time */

#include "dlist.h"
#include "utils.h" /* status_ty, boolean_ty, ANSI_COLOR_*/

/***************************** Macros Definitions *****************************/
/* prints colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 1 to 100 */
#define RANDOM_NUM (rand() % 100) + 1

#define UNUSED(x) (void)(x)
/****************************Forward Declarations******************************/
static void DlistCreateTest(dlist_ty *dlist);
static void DlistDestroyTest(dlist_ty *dlist, dlist_ty *dlist_output);
static void DlistIteratorBeginTest(dlist_ty *dlist);
static void DlistInsertBeforeTest(dlist_ty *dlist);
static void DlistRemoveTest(dlist_ty *dlist);
static void DlistIsEmptyTest(dlist_ty *dlist);
static void DlistPushFrontTest(dlist_ty *dlist);
static void DlistPushBackTest(dlist_ty *dlist);
static void DlistPopFrontTest(dlist_ty *dlist);
static void DlistPopBackTest(dlist_ty *dlist);
static void DlistSetDataTest(dlist_ty *dlist);
static status_ty PrintList(void *data, void *param);
static boolean_ty IsMatch(const void *data, void *param);
static void InsertIntToList(dlist_ty *dlist);
static void DlistForEachTest(dlist_ty *dlist);
static void DlistFindTest(dlist_ty *dlist);
static void DlistMultiFindTest(dlist_ty *dlist, dlist_ty *dlist_output);
static void DlistSpliceTest(dlist_ty *dlist_dest, dlist_ty *dlist_src);
/******************************************************************************/
/********************************Main Function*********************************/
int main()	
{
	/* Intializes two empty new doubly linked lists */
	dlist_ty *new_list = DlistCreate();
	dlist_ty *dlist_output = DlistCreate();
	
	/* Intializes random number generator */
	srand(time(0));
	
	DlistCreateTest(new_list);
	DlistIteratorBeginTest(new_list);
	DlistInsertBeforeTest(new_list);
	DlistRemoveTest(new_list);
	DlistIsEmptyTest(new_list);
	DlistPushFrontTest(new_list);
	DlistPushBackTest(new_list);
	DlistPopFrontTest(new_list);
	DlistPopBackTest(new_list);
	DlistSetDataTest(new_list);
	InsertIntToList(new_list);
	DlistForEachTest(new_list);
	DlistFindTest(new_list);
	DlistMultiFindTest(new_list, dlist_output);
	DlistSpliceTest(new_list, dlist_output);
	DlistDestroyTest(new_list, dlist_output);
	
	return (0);
}
/******************************************************************************/
/************************Test Functions Implementations************************/
/******************************************************************************/
static void DlistCreateTest(dlist_ty *dlist)
{
	printf("\nDoubly Linked List Creation Test: ");
	NULL == dlist ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
static void DlistDestroyTest(dlist_ty *dlist, dlist_ty *dlist_output)
{
	DlistDestroy(dlist);
	DlistDestroy(dlist_output);
	printf (ANSI_COLOR_CYAN "\nThe Lists have been deleted\n\n" 
															ANSI_COLOR_RESET);
}
/******************************************************************************/
static void DlistIteratorBeginTest(dlist_ty *dlist)
{
	printf("Iter To Begin/End/IsEqual Test: ");
	DlistIteratorIsEqual(DlistIteratorBegin(dlist), DlistIteratorEnd(dlist)) ?
	 											  PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void DlistInsertBeforeTest(dlist_ty *dlist)
{	

	boolean_ty is_working = TRUE;
	dlist_iter_ty new_node = NULL;
	
	printf("Dlist Insert Test: ");
	
	new_node = DlistInsertBefore(DlistIteratorBegin(dlist), "Messi");
	
	is_working *= DlistIteratorIsEqual(DlistIteratorBegin(dlist), new_node) ?
	 											  			TRUE : FALSE;
	
	is_working *= strcmp(DlistGetData(new_node), "Messi") ? FALSE : TRUE;
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void DlistRemoveTest(dlist_ty *dlist)
{
	size_t original_size = DlistSize(dlist);
	printf("Remove & Size Test: ");
	DlistRemove(DlistIteratorBegin(dlist));
	DlistSize(dlist) == (original_size - 1) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void DlistIsEmptyTest(dlist_ty *dlist)
{
	printf("Dlist IsEmpty Test: ");
	TRUE == DlistIsEmpty(dlist) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void DlistPushFrontTest(dlist_ty *dlist)
{
	boolean_ty is_working = TRUE;
	dlist_iter_ty node = NULL;
	
	printf("Dlist PushFront Test: ");
	
	node = DlistPushFront(dlist, "Lebron");
	
	is_working *= DlistIteratorIsEqual(DlistIteratorBegin(dlist), node) ?
	 											  			TRUE : FALSE;
	
	is_working *= strcmp(DlistGetData(node), "Lebron") ? FALSE : TRUE;
	
	is_working *= strcmp(DlistGetData(DlistIteratorBegin(dlist)), "Lebron")
	 														? FALSE : TRUE;
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
	
	DlistRemove(node);
}
/******************************************************************************/
static void DlistPushBackTest(dlist_ty *dlist)
{
	boolean_ty is_working = TRUE;
	dlist_iter_ty node = NULL;
	
	printf("Dlist PushBack Test: ");
	
	node = DlistPushBack(dlist, "Elon");
	
	is_working *= DlistIteratorIsEqual(
		DlistIteratorPrevious(DlistIteratorEnd(dlist)), node) ? TRUE : FALSE;
	
	is_working *= strcmp(DlistGetData(node), "Elon") ? FALSE : TRUE;
	
	is_working *= strcmp(
	DlistGetData(DlistIteratorPrevious(DlistIteratorEnd(dlist))), "Elon")
																 ? FALSE : TRUE;
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
	
	DlistRemove(node);
}
/******************************************************************************/
static void DlistPopFrontTest(dlist_ty *dlist)
{
	boolean_ty is_working = TRUE;
	
	dlist_iter_ty new_node = DlistIteratorBegin(dlist);
	void *popped_value = NULL;
	
	size_t original_size = 0;
	int num1 = 1, num2 = 2, num3 = 3;
	
	new_node = DlistInsertBefore(new_node, (void *)(long)num1);
	new_node = DlistInsertBefore(new_node, (void *)(long)num2);
	new_node = DlistInsertBefore(new_node, (void *)(long)num3);
	
	original_size = DlistSize(dlist);
	
	printf("Dlist PopFront Test: ");
	
	popped_value = DlistPopFront(dlist);
	is_working *= original_size - 1 == DlistSize(dlist) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num3);
	
	popped_value = DlistPopFront(dlist);
	is_working *= original_size - 2 == DlistSize(dlist) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num2);
	
	popped_value = DlistPopFront(dlist);
	is_working *= original_size - 3 == DlistSize(dlist) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num1);
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
	
}
/******************************************************************************/
static void DlistPopBackTest(dlist_ty *dlist)
{
	boolean_ty is_working = TRUE;
	
	dlist_iter_ty new_node = DlistIteratorBegin(dlist);
	void *popped_value = NULL;
	
	size_t original_size = 0;
	int num1 = 1, num2 = 2, num3 = 3;
	
	new_node = DlistInsertBefore(new_node, (void *)(long)num1);
	new_node = DlistInsertBefore(new_node, (void *)(long)num2);
	new_node = DlistInsertBefore(new_node, (void *)(long)num3);
	
	original_size = DlistSize(dlist);
	
	printf("Dlist PopBack Test: ");
	
	popped_value = DlistPopBack(dlist);
	is_working *= original_size - 1 == DlistSize(dlist) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num1);
	
	popped_value = DlistPopBack(dlist);
	is_working *= original_size - 2 == DlistSize(dlist) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num2);
	
	popped_value = DlistPopBack(dlist);
	is_working *= original_size - 3 == DlistSize(dlist) ? TRUE : FALSE;
	is_working *= IsMatch(popped_value, (void *)(long)num3);
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void DlistSetDataTest(dlist_ty *dlist)
{
	dlist_iter_ty new_node = DlistIteratorBegin(dlist);
	
	printf("Dlist Set+Get Data Test: ");
	
	new_node = DlistInsertBefore(new_node, "Messi");
	
	if (strcmp(DlistGetData(new_node), "Messi"))
	{
		PRINT_FAILURE;
	}
	
	DlistSetData(new_node, "Ronaldo");

	strcmp(DlistGetData(new_node), "Ronaldo") ? PRINT_FAILURE : PRINT_SUCCESS;
	
	DlistRemove(new_node);
}
/******************************************************************************/
static void InsertIntToList(dlist_ty *dlist)
{	
	dlist_iter_ty new_node = DlistIteratorBegin(dlist);
	
	int num1 = RANDOM_NUM, num2 = -1, num3 = RANDOM_NUM;
	
	printf("\nInserting to the list: %d, %d, %d\n", num1, num2, num3);
	
	new_node = DlistInsertBefore(new_node, (void *)(long)num1);
	new_node = DlistInsertBefore(new_node, (void *)(long)num2);
	new_node = DlistInsertBefore(new_node, (void *)(long)num3);
}
/******************************************************************************/
static status_ty PrintList(void *data, void *param)
{
	UNUSED(param);
	if (NULL == data || NULL == param)
	{
		return (FAILURE);
	}
	
	printf("%d ", (int)(long)data);
	return (SUCCESS);
}
/******************************************************************************/
static boolean_ty IsMatch(const void *data, void *param)
{	
	return (((int)(long)data == (int)(long)param));
}
/******************************************************************************/
static void DlistForEachTest(dlist_ty *dlist)
{
	int x = -1;
	status_ty result = FAILURE;
	printf("Printing List: ");
	result = DlistForEach(DlistIteratorBegin(dlist), DlistIteratorEnd(dlist), 
													PrintList, (void *)(long)x);
	printf("\nForEach Test(PrintList): ");
	(SUCCESS == result) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void DlistFindTest(dlist_ty *dlist)
{
	int x = -1;
	dlist_iter_ty new_node = DlistFind(DlistIteratorBegin(dlist),
							DlistIteratorEnd(dlist), IsMatch, (void *)(long)x);
	printf("Dlist Find Test: ");
	new_node == DlistIteratorEnd(dlist) ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
static void DlistMultiFindTest(dlist_ty *dlist, dlist_ty *dlist_output)
{
	int x = -1;
	printf("Dlist MultiFind Test: ");
	1 == DlistMultiFind(DlistIteratorBegin(dlist), DlistIteratorEnd(dlist), 
					IsMatch, (void *)(long)x, dlist_output) ? PRINT_SUCCESS :
					 											PRINT_FAILURE;
}
/******************************************************************************/
static void DlistSpliceTest(dlist_ty *dlist_dest, dlist_ty *dlist_src)
{
	int num1 = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5, num6 = 6;
	int x = -1;
	
	printf("Dlist Splice Test: ");
	
	/** Empty both lists **/
	while(!DlistIsEmpty(dlist_dest))
	{
		DlistRemove(DlistIteratorBegin(dlist_dest));
	}
	
	while(!DlistIsEmpty(dlist_src))
	{
		DlistRemove(DlistIteratorBegin(dlist_src));
	}
	
	DlistInsertBefore(DlistIteratorBegin(dlist_dest), (void *)(long)num1);
	DlistInsertBefore(DlistIteratorBegin(dlist_dest), (void *)(long)num2);
	DlistInsertBefore(DlistIteratorBegin(dlist_dest), (void *)(long)num3);
	printf("Printing List DEST: ");
	DlistForEach(DlistIteratorBegin(dlist_dest), DlistIteratorEnd(dlist_dest), 
													PrintList, (void *)(long)x);
	DlistInsertBefore(DlistIteratorBegin(dlist_src), (void *)(long)num4);
	DlistInsertBefore(DlistIteratorBegin(dlist_src), (void *)(long)num5);
	DlistInsertBefore(DlistIteratorBegin(dlist_src), (void *)(long)num6);
	printf("Printing List SRC: ");
	DlistForEach(DlistIteratorBegin(dlist_src), DlistIteratorEnd(dlist_src), 
													PrintList, (void *)(long)x);
		
	printf("\nTAIL->PREVIOUS in DEST: %d\n", (int)(long)DlistGetData(DlistIteratorPrevious(DlistIteratorEnd(dlist_dest))));
	printf("TAIL->PREVIOUS in SRC: %d\n", (int)(long)DlistGetData(DlistIteratorPrevious(DlistIteratorEnd(dlist_src))));												
	DlistSplice(DlistIteratorPrevious(DlistIteratorEnd(dlist_dest)), DlistIteratorBegin(dlist_src), DlistIteratorEnd(dlist_src));
	
	printf("**AFTER SPLICE:**\n");
	printf("\n TAIL->PREVIOUS in DEST: %d\n", (int)(long)DlistGetData(DlistIteratorPrevious(DlistIteratorEnd(dlist_dest))));
		printf("Printing List SRC: ");
	DlistForEach(DlistIteratorBegin(dlist_src), DlistIteratorEnd(dlist_src), 
													PrintList, (void *)(long)x);
				printf("Printing List DEST: ");
	DlistForEach(DlistIteratorBegin(dlist_dest), DlistIteratorEnd(dlist_dest), 
													PrintList, (void *)(long)x);										
}


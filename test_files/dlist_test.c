/**********************************FILE-HEADER*********************************\
* File: dlist_test.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 01/04/2021							   								
* Version: Beta				   								
* Reviewer: Danel						   								
* Description: Doubly Linked List API's Functions Testings.		 
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stddef.h>	/* size_t */
#include <stdio.h>	/* printf, fprintf */
#include <stdlib.h> /* rand, srand */
#include <string.h> /* strcmp */
#include <time.h>	/* time */

#include "utils.h" /* status_ty, bolean_ty, ANSI_COLOR_*/
#include "dlist.h"

/***************************** Macros Definitions *****************************/
/* prints colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 0 to 99 */
#define RANDOM_NUM rand() % 100

#define UNUSED(x) (void)(x)
/****************************Forward Declarations******************************/
static void DlistCreateTest(dlist_ty *dlist);
static void DlistDestroyTest(dlist_ty *dlist);
static void DlistIteratorBeginTest(dlist_ty *dlist);
static void DlistInsertBeforeTest(dlist_ty *dlist);
static void DlistRemoveTest(dlist_ty *dlist);
static void DlistIsEmptyTest(dlist_ty *dlist);
static void DlistSetDataTest(dlist_ty *dlist);
static status_ty PrintList(void *data, void *param);
static boolean_ty IsMatch(const void *data, void *param);
static void InsertIntToList(dlist_ty *dlist);
static void DlistForEachTest(dlist_ty *dlist);
static void DlistFindTest(dlist_ty *dlist);
/******************************************************************************/
/********************************Main Function*********************************/
int main()	
{
	/* Intializes new singly linked list */
	dlist_ty *new_list = DlistCreate();
	
	/* Intializes random number generator */
	srand(time(0));
	
	DlistCreateTest(new_list);
	DlistIteratorBeginTest(new_list);
	DlistInsertBeforeTest(new_list);
	DlistRemoveTest(new_list);
	DlistIsEmptyTest(new_list);
	DlistSetDataTest(new_list);
	InsertIntToList(new_list);
	DlistForEachTest(new_list);
	DlistFindTest(new_list);
	DlistDestroyTest(new_list);
	
	return(0);
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
static void DlistDestroyTest(dlist_ty *dlist)
{
	DlistDestroy(dlist);
	printf (ANSI_COLOR_CYAN "\nThe List has been deleted\n\n" ANSI_COLOR_RESET);
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
	dlist_iter_ty new_node = NULL;
	
	printf("Dlist Insert Test: ");
	
	new_node = DlistInsertBefore(DlistIteratorBegin(dlist), "Messi");
	
	strcmp(DlistGetData(new_node), "Messi") ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
static void DlistRemoveTest(dlist_ty *dlist)
{
	size_t original_size = DlistSize(dlist);
	DlistInsertBefore(DlistIteratorBegin(dlist), "Messi");
	printf(ANSI_COLOR_CYAN "\nList's size is: %lu\n" ANSI_COLOR_RESET, DlistSize(dlist));
	printf("Remove & Size Test: ");
	DlistRemove(DlistIteratorBegin(dlist));
	printf(ANSI_COLOR_CYAN "\nList's size is: %lu\n" ANSI_COLOR_RESET, DlistSize(dlist));
	DlistSize(dlist) == (original_size - 1) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void DlistIsEmptyTest(dlist_ty *dlist)
{
	printf("Dlist IsEmpty Test: ");
	printf(ANSI_COLOR_CYAN "\nList's size is: %lu\n" ANSI_COLOR_RESET, DlistSize(dlist));
	TRUE == DlistIsEmpty(dlist) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void DlistSetDataTest(dlist_ty *dlist)
{
	dlist_iter_ty new_node = DlistIteratorBegin(dlist);
	
	printf("Dlist Set+Get Data Test: ");
	
	new_node = DlistInsertBefore(new_node, "Messi");
	
	printf(ANSI_COLOR_CYAN "\nList's size is(AFTER INSERT): %lu\n" ANSI_COLOR_RESET, DlistSize(dlist));
	
	if(strcmp(DlistGetData(new_node), "Messi"))
	{
		PRINT_FAILURE;
	}
	
	DlistSetData(new_node, "Ronaldo");

	strcmp(DlistGetData(new_node), "Ronaldo") ? PRINT_FAILURE : PRINT_SUCCESS;
	
	DlistRemove(new_node);
	
	printf(ANSI_COLOR_CYAN "\nList's size is(AFTER REMOVE): %lu\n" ANSI_COLOR_RESET, DlistSize(dlist));
}
/******************************************************************************/
static void InsertIntToList(dlist_ty *dlist)
{	
	dlist_iter_ty new_node = DlistIteratorBegin(dlist);
	
	int num1 = RANDOM_NUM, num2 = 3, num3 = RANDOM_NUM;
	
	printf("\nInserting to the list: %d, %d, %d\n", num1, num2, num3);
	
	new_node = DlistInsertBefore(new_node, (void *)(long)num1);
	new_node = DlistInsertBefore(new_node, (void *)(long)num2);
	new_node = DlistInsertBefore(new_node, (void *)(long)num3);
	
	printf(ANSI_COLOR_CYAN "\nList's size is(AFTER 3 INSERT): %lu\n" ANSI_COLOR_RESET, DlistSize(dlist));
}
/******************************************************************************/
static status_ty PrintList(void *data, void *param)
{
	printf(ANSI_COLOR_CYAN "PRINTLIST FUNCTION" ANSI_COLOR_RESET);
	UNUSED(param);
	printf(ANSI_COLOR_CYAN "PRINTLIST FUNCTION" ANSI_COLOR_RESET);
	if (NULL == data || NULL == param)
	{
		return(FAILURE);
	}
	
	printf("%d ", (int)(long)data);
	return(SUCCESS);
}

/******************************************************************************/
static boolean_ty IsMatch(const void *data, void *param)
{	
	return(((int)(long)data == (int)(long)param));
}
/******************************************************************************/
static void DlistForEachTest(dlist_ty *dlist)
{
	int x = 3;
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
	int x = 3;
	dlist_iter_ty new_node = DlistFind(DlistIteratorBegin(dlist),
							DlistIteratorEnd(dlist), IsMatch, (void *)(long)x);
	printf("Dlist Find Test: ");
	new_node == DlistIteratorEnd(dlist) ? PRINT_FAILURE : PRINT_SUCCESS;
}


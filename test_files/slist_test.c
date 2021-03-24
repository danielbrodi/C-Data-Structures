/**********************************FILE-HEADER*********************************\
* File: slist_test.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 22/03/2021							   								
* Version: 2.0 (After Review)							   								
* Reviewer: Olga							   								
* Description: Single Linked List API's Functions Testings.		 
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stddef.h>	/* size_t */
#include <stdio.h>	/* printf, fprintf */
#include <stdlib.h> /* rand, srand */
#include <string.h> /* strcmp */
#include <time.h>	/* time */

#include "utils.h" /* status_ty, bolean_ty, ANSI_COLOR_*/
#include "slist.h"

/***************************** Macros Definitions *****************************/
/* prints colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 0 to 99 */
#define RANDOM_NUM rand() % 100

#define UNUSED(x) (void)(x)
/****************************Forward Declarations******************************/
static void SlistCreateTest(slist_ty *slist);
static void SlistDestroyTest(slist_ty *slist);
static void SlistIteratorBeginTest(slist_ty *slist);
static void SlistInsertTest(slist_ty *slist);
static void SlistRemoveTest(slist_ty *slist);
static void SlistIsEmptyTest(slist_ty *slist);
static void SlistSetDataTest(slist_ty *slist);
static status_ty PrintList(void *data, void *param);
static boolean_ty IsMatch(void *data, void *param);
static void InsertIntToList(slist_ty *slist);
static void SlistForEachTest(slist_ty *slist);
static void SlistFindTest(slist_ty *slist);
/******************************************************************************/
/********************************Main Function*********************************/
int main()	
{
	/* Intializes new singly linked list */
	slist_ty *new_list = SlistCreate();
	
	/* Intializes random number generator */
	srand(time(0));
	
	SlistCreateTest(new_list);
	SlistIteratorBeginTest(new_list);
	SlistInsertTest(new_list);
	SlistRemoveTest(new_list);
	SlistIsEmptyTest(new_list);
	SlistSetDataTest(new_list);
	InsertIntToList(new_list);
	SlistForEachTest(new_list);
	SlistFindTest(new_list);
	SlistDestroyTest(new_list);
	
	return(0);
}
/******************************************************************************/
/************************Test Functions Implementations************************/
/******************************************************************************/
static void SlistCreateTest(slist_ty *slist)
{
	printf("\nLinked List Creatation Test: ");
	NULL == slist ? PRINT_FAILURE : PRINT_SUCCESS;
}

/******************************************************************************/
static void SlistDestroyTest(slist_ty *slist)
{
	SlistDestroy(slist);
	printf (ANSI_COLOR_CYAN "\nThe List has been deleted\n\n" ANSI_COLOR_RESET);
}
/******************************************************************************/
static void SlistIteratorBeginTest(slist_ty *slist)
{
	printf("Iter To Begin/End + Next Test: ");
	SlistIteratorEnd(slist) == SlistIteratorNext(SlistIteratorBegin(slist)) ?
	 											  PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void SlistInsertTest(slist_ty *slist)
{	
	slist_iter_ty new_node = SlistIteratorBegin(slist);
	
	printf("Slist Insert Test: ");
	
	new_node = SlistInsert(new_node, "Messi");
	
	strcmp(SlistGetData(new_node), "Messi") ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
static void SlistRemoveTest(slist_ty *slist)
{
	size_t original_size = SlistSize(slist);
	printf("Remove & Size Test: ");
	SlistRemove(SlistIteratorBegin(slist));
	SlistSize(slist) == (original_size - 1) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void SlistIsEmptyTest(slist_ty *slist)
{
	printf("Slist IsEmpty Test: ");
	TRUE == SlistIsEmpty(slist) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void SlistSetDataTest(slist_ty *slist)
{
	slist_iter_ty new_node = SlistIteratorBegin(slist);
	
	printf("Slist Set+Get Data Test: ");
	
	new_node = SlistInsert(new_node, "Messi");
	
	if(strcmp(SlistGetData(new_node), "Messi"))
	{
		PRINT_FAILURE;
	}
	
	SlistSetData(new_node, "Ronaldo");

	strcmp(SlistGetData(new_node), "Ronaldo") ? PRINT_FAILURE : PRINT_SUCCESS;
	
	SlistRemove(new_node);
}
/******************************************************************************/
static void InsertIntToList(slist_ty *slist)
{	
	slist_iter_ty new_node = SlistIteratorBegin(slist);
	
	int num1 = RANDOM_NUM, num2 = 3, num3 = RANDOM_NUM;
	
	printf("\nInserting to the list: %d, %d, %d\n", num1, num2, num3);
	
	new_node = SlistInsert(new_node, (void *)(long)num1);
	new_node = SlistInsert(new_node, (void *)(long)num2);
	new_node = SlistInsert(new_node, (void *)(long)num3);
}
/******************************************************************************/
static status_ty PrintList(void *data, void *param)
{
	UNUSED(param);
	
	if (NULL == data || NULL == param)
	{
		return(FAILURE);
	}
	
	printf("%d ", (int)(long)data);
	
	return(SUCCESS);
}

/******************************************************************************/
static boolean_ty IsMatch(void *data, void *param)
{	
	return(((int)(long)data == (int)(long)param));
}
/******************************************************************************/
static void SlistForEachTest(slist_ty *slist)
{
	int x = 3;
	status_ty result = SUCCESS;
	printf("Printing List: ");
	result = SlistForEach(SlistIteratorBegin(slist), SlistIteratorEnd(slist), 
													PrintList, (void *)(long)x);
	printf("\nForEach Test(PrintList): ");
	(SUCCESS == result) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void SlistFindTest(slist_ty *slist)
{
	int x = 3;
	slist_iter_ty new_node = SlistFind(SlistIteratorBegin(slist),
							SlistIteratorEnd(slist), IsMatch, (void *)(long)x);
	printf("Slist Find Test: ");
	new_node == SlistIteratorEnd(slist) ? PRINT_FAILURE : PRINT_SUCCESS;
}

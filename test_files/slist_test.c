/**********************************FILE-HEADER*********************************\
* File: list_test.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 21/03/2021							   								
* Version: 2.0 (Before Review)							   								
* Reviewer: Olga							   								
* Description: Single Linked List API's Functions Testings.		 
\******************************************************************************/

/********************************** Inclusions ********************************/

#include <stdio.h>	/* printf, fprintf */
#include <stdlib.h> /* rand, srand */
#include <time.h>	/* time */
#include <string.h> /* strcmp */

#include "list.h"

/***************************** Macros Definitions *****************************/

/* escape keys for printf to color output for StdOut */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 0 to 99 */
#define RANDOM_NUM rand() % 100

#define UNUSED(x) (void)(x)
/****************************Forward Declarations******************************/
void SlistCreateTest(slist_ty *slist);
void SlistDestroyTest(slist_ty *slist);
void SlistIteratorBeginTest(slist_ty *slist);
void SlistInsertTest(slist_ty *slist);
void SlistRemoveTest(slist_ty *slist);
void SlistIsEmptyTest(slist_ty *slist);
void SlistSetDataTest(slist_ty *slist);
status_ty PrintList(void *data, void *param);
boolean_ty IsMatch(void *data, void *param);
void InsertIntToList(slist_ty *slist);
void SlistForEachTest(slist_ty *slist);
void SlistFindTest(slist_ty *slist);
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
void SlistCreateTest(slist_ty *slist)
{
	printf("\nLinked List Creatation Test: ");
	NULL == slist ? PRINT_FAILURE : PRINT_SUCCESS;
}

/******************************************************************************/
void SlistDestroyTest(slist_ty *slist)
{
	SlistDestroy(slist);
	printf (ANSI_COLOR_CYAN "\nThe List has been deleted\n\n" ANSI_COLOR_RESET);
}
/******************************************************************************/
void SlistIteratorBeginTest(slist_ty *slist)
{
	printf("Iter To Begin/End + Next Test: ");
	SlistIteratorEnd(slist) == SlistIteratorNext(SlistIteratorBegin(slist)) ?
	 											  PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
void SlistInsertTest(slist_ty *slist)
{	
	slist_iter_ty new_node = SlistIteratorBegin(slist);
	
	printf("Slist Insert Test: ");
	
	new_node = SlistInsert(new_node, "Messi");
	
	strcmp(SlistGetData(new_node), "Messi") ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
void SlistRemoveTest(slist_ty *slist)
{
	size_t original_size = SlistSize(slist);
	printf("Remove & Size Test: ");
	SlistRemove(SlistIteratorBegin(slist));
	SlistSize(slist) == (original_size - 1) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
void SlistIsEmptyTest(slist_ty *slist)
{
	printf("Slist IsEmpty Test: ");
	TRUE == SlistIsEmpty(slist) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
void SlistSetDataTest(slist_ty *slist)
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
void InsertIntToList(slist_ty *slist)
{	
	slist_iter_ty new_node = SlistIteratorBegin(slist);
	
	int num1 = RANDOM_NUM, num2 = 3, num3 = RANDOM_NUM;
	
	printf("\nInserting to the list: %d, %d, %d\n", num1, num2, num3);
	
	new_node = SlistInsert(new_node, (void *)(long)num1);
	new_node = SlistInsert(new_node, (void *)(long)num2);
	new_node = SlistInsert(new_node, (void *)(long)num3);
}
/******************************************************************************/
status_ty PrintList(void *data, void *param)
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
boolean_ty IsMatch(void *data, void *param)
{	
	return(((int)(long)data == (int)(long)param));
}
/******************************************************************************/
void SlistForEachTest(slist_ty *slist)
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
void SlistFindTest(slist_ty *slist)
{
	int x = 3;
	slist_iter_ty new_node = SlistFind(SlistIteratorBegin(slist),
							SlistIteratorEnd(slist), IsMatch, (void *)(long)x);
	printf("Slist Find Test: ");
	new_node == SlistIteratorEnd(slist) ? PRINT_FAILURE : PRINT_SUCCESS;
}

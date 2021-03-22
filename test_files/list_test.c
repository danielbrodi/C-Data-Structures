/**********************************FILE-HEADER*********************************\
* File: list_test.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 21/03/2021							   								
* Version: 1.0 (Before Review)							   								
* Reviewer: Olga							   								
* Description: Single Linked List API's Functions Testings.		 
\******************************************************************************/

/********************************** Inclusions ********************************/

#include <stdio.h> /* printf, fprintf */
#include <string.h> /* strcmp */

#include "../include/list.h"

/***************************** Macros Definitions *****************************/

/* escape keys for printf to color output for StdOut */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/****************************Forward Declarations******************************/
void SlistCreateTest(slist_ty *slist);
void SlistDestroyTest(slist_ty *slist);
void SlistIteratorBeginTest(slist_ty *slist);
void SlistInsertTest(slist_ty *slist);
void SlistRemoveTest(slist_ty *slist);
void SlistIsEmptyTest(slist_ty *slist);
void SlistSetDataTest(slist_ty *slist);
/******************************************************************************/
/********************************Main Function*********************************/
int main()	
{
	slist_ty *new_list = SlistCreate();
	
	SlistCreateTest(new_list);
	SlistIteratorBeginTest(new_list);
	SlistInsertTest(new_list);
	SlistRemoveTest(new_list);
	SlistIsEmptyTest(new_list);
	SlistSetDataTest(new_list);
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
	printf("Iter To Begin/End Test: ");
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
	0 == original_size - 1 ? PRINT_SUCCESS : PRINT_FAILURE;
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
}
/******************************************************************************/

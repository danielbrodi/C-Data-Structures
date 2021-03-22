/**********************************FILE-HEADER*********************************\
* File: list_test.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 21/03/2021							   								
* Version: Beta (Before Review)							   								
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

#define PRINT_SUCCESS printf Test(ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf Test(ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/**********************Forward Declarations************************************/

void SlistCreateTest(slist_ty *slist);
void SlistDestroyTest(slist_ty *slist);
void SlistIteratorBeginTest(const slist_ty *slist);
void SlistIteratorEndTest(const slist_ty *slist);
void SlistIteratorNextTest(const slist_iter_ty iter);
void SlistIteratorIsEqualTest(const slist_iter_ty iter_a, 
											const slist_iter_ty iter_b);
void SlistGetDataTest(const slist_iter_ty iter);
void SlistSetDataTest(slist_iter_ty iter, void *data);
void SlistInsertTest(slist_iter_ty iter, void *data);
void SlistRemoveTest(slist_iter_ty iter);
void SlistIsEmptyTest(const slist_ty *slist);
void SlistSize(const slist_ty *slist);
void SlistFindTest(const slist_iter_ty from_iter, 
	const slist_iter_ty to_iter, IsMatch_Func,
	void *param);
void SlistForEachTest(const slist_iter_ty from_iter,
const slist_iter_ty to_iter, Action_Func);

/******************************************************************************/

/********************************Main Function*********************************/

int main()	
{
	slist_ty *new_list = SlistCreate();
	
	SlistCreateTest(new_list);
	SlistIteratorBeginTest(new_list);
	SlistInsertTest(new_list);
	
	SlistDestroy(new_list);
	
	return(0);
}

/************************Test Functions Implementations************************/

/******************************************************************************/
void *SlistCreateTest(slist_ty *slist)
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
void SlistIteratorBeginTest(const slist_ty *slist)
{
	printf("SlistIteratorBeginTest: ");
	NULL == SlistIteratorBegin(slist) ? PRINT_SUCCESS : PRINT_FAILURE;
}

/******************************************************************************/
void SlistIteratorEndTest(const slist_ty *slist)
{
	printf("SlistIteratorEndTest: ");
	NULL == (SlistIteratorEndTest(slist)->data) ? PRINT_SUCCESS : PRINT_FAILURE;
}

/******************************************************************************/
void SlistIteratorNextTest(const slist_iter_ty iter)
{
	printf("SlistIteratorBeginTest: ");
}

/******************************************************************************/
void SlistIteratorIsEqualTest(const slist_iter_ty iter_a, 
											const slist_iter_ty iter_b)
{
	printf("SlistIteratorBeginTest: ");
}

/******************************************************************************/
void SlistGetDataTest(const slist_iter_ty iter)
{
	printf("SlistIteratorBeginTest: ");
}

/******************************************************************************/
void SlistSetDataTest(slist_iter_ty iter, void *data)
{
	printf("SlistIteratorBeginTest: ");
}

/******************************************************************************/
void SlistInsertTest(slist_ty *slist)
{	
	slist_iter_ty new_node = SlistIteratorBegin;
	
	assert(slist);
	
	printf("SlistInsertTest: ");
	
	new_node = SlistInsert(new_node, "Messi");
	
	strcmp(SlistGetData(new_node), "Messi") ? PRINT_FAILURE : PRINT_SUCCESS;
}

/******************************************************************************/
void SlistRemoveTest(slist_iter_ty iter)
{
	printf("SlistIteratorBeginTest: ");
}

/******************************************************************************/
void SlistIsEmptyTest(const slist_ty *slist)
{
	printf("SlistIteratorBeginTest: ");
}

/******************************************************************************/
void SlistSizeTest(const slist_ty *slist)
{
	printf("SlistIteratorBeginTest: ");
}

/******************************************************************************/
void SlistFindTest(const slist_iter_ty from_iter, 
	const slist_iter_ty to_iter, IsMatch_Func,
	void *param)
{
	printf("SlistIteratorBeginTest: ");
}

/******************************************************************************/
void SlistForEachTest(const slist_iter_ty from_iter,
const slist_iter_ty to_iter, Action_Func)
{
	printf("SlistIteratorBeginTest: ");
}

/******************************************************************************/


/*********************************FILE__HEADER*********************************\
* File:	pqueue_test.c						 		  								
* Author:	Daniel Brodsky					  								
* Date:	08/04/2021							   								
* Version:	1.0	(Pre Review)						
* Reviewer:	Eran							   								
* Description:	Priority Queue implementation tests.		 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>	/*	assert	*/
#include <stddef.h>	/*	size_t	*/
#include <stdio.h>	/* printf, NULL */
#include <stdlib.h> /* rand, srand */
#include <string.h> /* strcmp */
#include <time.h>	/* time */

#include "utils.h" /* status_ty, boolean_ty, ANSI_COLOR_*/
#include "pqueue.h"

/***************************** Macros Definitions *****************************/
/* print colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 1 to 100 */
#define RANDOM_NUM ((rand() % 100) + 1)

#define UNUSED(x) (void)(x)
/**************************** Forward Declarations ****************************/
int SortElements(const void *data1, const void *data2);
static void PqueueCreateTest(p_queue_ty *p_queue);
static void PqueueDestroyTest(p_queue_ty *p_queue);
/*static void PqueueIteratorBeginTest(p_queue_ty *p_queue);*/
/*static void PqueueInsertTest(p_queue_ty *p_queue);*/
/*static void PqueueRemoveTest(p_queue_ty *p_queue);*/
/*static void PqueueIsEmptyTest(p_queue_ty *p_queue);*/
/*static void PqueuePopFrontTest(p_queue_ty *p_queue);*/
/*static void PqueuePopBackTest(p_queue_ty *p_queue);*/
/*static void PqueueFindTest(p_queue_ty *p_queue);*/
/*static void PqueueFindIfTest(p_queue_ty *p_queue);*/
/*static boolean_ty IsMatch(const void *data, void *param);*/
/*static boolean_ty IsDividedBy(const void *data, const void *param);*/
/*static void PqueueForEachTest(p_queue_ty *p_queue);*/
/*static status_ty PrintList(void *data, const void *param);*/
/******************************************************************************/
/******************************* Main__Function *******************************/
int main()	
{
	/* Intializes two empty new sorted lists */
	p_queue_ty *new_p_queue = PqueueCreate(SortElements);
	
	/* Intializes random number generator */
	srand(time(0));
	PqueueCreateTest(new_p_queue);
/*	PqueueIteratorBeginTest(new_p_queue);*/
/*	PqueueInsertTest(new_p_queue);*/
/*	PqueueRemoveTest(new_p_queue);*/
/*	PqueueIsEmptyTest(new_p_queue);*/
/*	PqueuePopFrontTest(new_p_queue);*/
/*	PqueuePopBackTest(new_p_queue);*/
/*	PqueueFindTest(new_p_queue);*/
/*	PqueueFindIfTest(new_p_queue);*/
/*	PqueueForEachTest(new_p_queue);*/
/*	PqueueMergeTest(new_p_queue, src_list);*/
	PqueueDestroyTest(new_p_queue);
	
	return (0);
}
/******************************************************************************/
/************************Test Functions Implementations************************/
/******************************************************************************/
static void PqueueCreateTest(p_queue_ty *p_queue)
{
	
	printf("\nSorted List Creation Test: ");
	NULL == p_queue ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
static void PqueueDestroyTest(p_queue_ty *p_queue)
{
	PqueueDestroy(p_queue);
	printf (ANSI_COLOR_CYAN "\nThe queue has been successfully deleted\n\n" 
															ANSI_COLOR_RESET);
}
/******************************************************************************/
int SortElements(const void *data1, const void *data2)
{	
	return ((int)(long)(data2) - (int)(long)(data1));
}
/******************************************************************************/

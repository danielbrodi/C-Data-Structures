/*********************************FILE__HEADER*********************************\
* File:	pqueue_test.c						 		  								
* Author:	Daniel Brodsky					  								
* Date:	08/04/2021							   								
* Version:	1.0	(Reviewed)						
* Reviewer:	Eran							   								
* Description:	Priority Queue implementation tests.		 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <stddef.h>	/*	size_t			*/
#include <stdio.h>	/*	printf, NULL	*/
#include <stdlib.h>	/*	rand, srand		*/
#include <time.h>	/*	time			*/

#include "utils.h"	/*	status_ty, boolean_ty, ANSI_COLOR_	*/
#include "pqueue.h"

/***************************** Macros Definitions *****************************/
/* print colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 1 to 100 */
#define RANDOM_NUM ((rand() % 100) + 1)

#define INT_TO_VOID_PTR(int_x) (void *)(long)(int_x)
#define VOID_PTR_TO_INT(void_ptr) (int)(long)(void_ptr)
/**************************** Forward Declarations ****************************/
int SortElements(const void *data1, const void *data2);
static void PqueueCreateTest(p_queue_ty *p_queue);
static void PqueueDestroyTest(p_queue_ty *p_queue);
static void PqueueSortingTest(p_queue_ty *p_queue);
static void PqueueEraseTest(p_queue_ty *p_queue);
static boolean_ty IsMatch(const void *data, const void *param);
static void PqueueClearTest(p_queue_ty *p_queue);
/******************************************************************************/
/******************************* Main__Function *******************************/
int main()	
{
	/*	Intializes a new empty priority queue	*/
	p_queue_ty *new_p_queue = PqueueCreate(SortElements);
	
	/*	Intializes a random number generator	*/
	srand(time(0));
	
	PqueueCreateTest(new_p_queue);
	PqueueSortingTest(new_p_queue);
	PqueueClearTest(new_p_queue);
	PqueueEraseTest(new_p_queue);
	PqueueDestroyTest(new_p_queue);
	
	return (0);
}
/******************************************************************************/
/************************Test Functions Implementations************************/
/******************************************************************************/
static void PqueueCreateTest(p_queue_ty *p_queue)
{
	
	printf("\nPriority Queue Creation Test: ");
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
static void PqueueSortingTest(p_queue_ty *p_queue)
{
	boolean_ty is_working = TRUE;
	size_t num_of_inserts = 10, i = 0;
	void *data1 = NULL, *data2 = NULL;
	
	size_t original_size = PqueueSize(p_queue);
	
	printf("Enqueue & Dequeue & Peek & Size Tests: ");
	
	for(i = 0; i < num_of_inserts; ++i)
	{
		is_working *= !(PqueueEnqueue(p_queue, INT_TO_VOID_PTR(RANDOM_NUM)));
		is_working *= (PqueueSize(p_queue) == original_size + 1 + i);
	}

	/* check if the list is sorted as needed by its criteria */
	while (PqueueSize(p_queue) != 1 && TRUE == is_working)
	{
		data1 = PqueueDequeue(p_queue);
		data2 = PqueuePeek(p_queue);
		
		is_working *= (SortElements(data1, data2) >= 0);
	}
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void PqueueClearTest(p_queue_ty *p_queue)
{
	boolean_ty is_working = TRUE;
	size_t num_of_inserts = 10, i = 0;
	
	printf("Priority Queue Clear & IsEmpty Tests: ");
	
	if(!PqueueIsEmpty(p_queue))
	{
		PqueueClear(p_queue);
	}
	
	is_working *= PqueueIsEmpty(p_queue);
	
	for(i = 0; i < num_of_inserts; ++i)
	{
		is_working *= !(PqueueEnqueue(p_queue, INT_TO_VOID_PTR(RANDOM_NUM)));
	}
	
	PqueueClear(p_queue);
	
	is_working *= PqueueIsEmpty(p_queue);
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void PqueueEraseTest(p_queue_ty *p_queue)
{
	boolean_ty is_working = TRUE;
	
	size_t num_of_inserts = 10, i = 0;
	int nums_to_cmp[10] = {0};
	int *num_to_cmp = nums_to_cmp;
	
	printf("Priority Queue Erase Test: ");
	
	for(i = 0; i < num_of_inserts; ++i)
	{
		nums_to_cmp[i] = RANDOM_NUM;
		is_working *= !(PqueueEnqueue(p_queue, 
											INT_TO_VOID_PTR(nums_to_cmp[i])));
	}
	
	while(!PqueueIsEmpty(p_queue) && is_working)
	{
		is_working *= IsMatch(
								 INT_TO_VOID_PTR(*num_to_cmp),
					 			PqueueErase(p_queue, IsMatch,
					 						 INT_TO_VOID_PTR(*num_to_cmp)));
		++num_to_cmp;
	}
	
	is_working *= PqueueIsEmpty(p_queue);
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
int SortElements(const void *data1, const void *data2)
{	
	return (VOID_PTR_TO_INT(data2) - VOID_PTR_TO_INT(data1));
}
/******************************************************************************/
static boolean_ty IsMatch(const void *data, const void *param)
{	
	return (VOID_PTR_TO_INT(data) == VOID_PTR_TO_INT(param));
}
/******************************************************************************/

/**********************************FILE-HEADER*********************************\
* File: queue_test.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 29/03/2021							   								
* Version: 1.0 (After Review)					   								
* Reviewer: Ariel							   								
* Description: Queue implementation tests.			 
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stddef.h>	/* size_t, NULL */
#include <stdio.h>	/* printf */
#include <stdlib.h> /* rand, srand */
#include <time.h>	/* time */

#include "utils.h" /* status_ty, bolean_ty, ANSI_COLOR_*/
#include "queue.h"

/***************************** Macros Definitions *****************************/
/* prints colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 1 to 100 */
#define RANDOM_NUM (rand() % 100 + 1)

#define UNUSED(x) (void)(x)
/****************************Forward Declarations******************************/
static void QueueCreateTest(queue_ty *queue);
static void QueueDestroyTest(queue_ty *queue, queue_ty *second_queue);
static void QueueEnqueueTest(queue_ty *queue);
static void QueueDequeueTest(queue_ty *queue);
static void QueueIsEmptyTest(queue_ty *queue);
static void QueuePeekTest(queue_ty *queue);
static void QueueAppendTest(queue_ty *queue, queue_ty *other_queue);
/******************************************************************************/
/********************************Main Function*********************************/
int main()	
{
	/* Intializes two empty queues */
	queue_ty *new_queue = QueueCreate();
	queue_ty *second_queue = QueueCreate();
	
	/* Intializes random number generator */
	srand(time(0));
	
	QueueCreateTest(new_queue);
	QueueEnqueueTest(new_queue);
	QueuePeekTest(new_queue);
	QueueDequeueTest(new_queue);
	QueueIsEmptyTest(new_queue);
	QueueAppendTest(new_queue, second_queue);
	QueueDestroyTest(new_queue, second_queue);
	
	return(0);
}
/******************************************************************************/
/************************Test Functions Implementations************************/
/******************************************************************************/
void QueueCreateTest(queue_ty *queue)
{
	printf("\nQueue Creatation Test: ");
	NULL == queue ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
void QueueDestroyTest(queue_ty *queue, queue_ty *second_queue)
{
	QueueDestroy(queue);
	QueueDestroy(second_queue);
	printf (ANSI_COLOR_CYAN "\nThe queues have been deleted\n"
															 ANSI_COLOR_RESET);
}
/******************************************************************************/
void QueueEnqueueTest(queue_ty *queue)
{	
	size_t original_size = QueueSize(queue);
	int num1 = RANDOM_NUM, num2 = 3, num3 = RANDOM_NUM;
	
	printf("Enqueue & Size Test: ");
	
	Enqueue(queue, (void *)(long)num1);
	Enqueue(queue, (void *)(long)num2);
	Enqueue(queue, (void *)(long)num3);
	
	QueueSize(queue) == (original_size + 3) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
void QueuePeekTest(queue_ty *queue)
{
	printf("Queue Peek Test: ");
	
	Dequeue(queue);
	
	3 == (int)(long)QueuePeek(queue) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
void QueueDequeueTest(queue_ty *queue)
{
	size_t original_size = QueueSize(queue);
	
	printf("Dequeue & Size Test: ");
	
	Dequeue(queue);
	Dequeue(queue);
	
	QueueSize(queue) == (original_size - 2) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
void QueueIsEmptyTest(queue_ty *queue)
{
	printf("Queue IsEmpty Test: ");
	
	TRUE == QueueIsEmpty(queue) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
void QueueAppendTest(queue_ty *queue, queue_ty *other_queue)
{
	
	int num1 = RANDOM_NUM, num2 = 3, num3 = RANDOM_NUM;
	int num4 = RANDOM_NUM, num5 = 3, num6 = RANDOM_NUM;
	size_t status = 1;
	size_t original_size = 0;
	size_t original_other_size = 0;
	
	printf("Queue Append Test: ");
	
	/* filling up first queue */
	Enqueue(queue, (void *)(long)num1);
	Enqueue(queue, (void *)(long)num2);
	Enqueue(queue, (void *)(long)num3);
	/* filling up second queue */
	Enqueue(other_queue, (void *)(long)num4);
	Enqueue(other_queue, (void *)(long)num5);
	Enqueue(other_queue, (void *)(long)num6);
	
	original_size = QueueSize(queue);
	original_other_size = QueueSize(other_queue);
	
	QueueAppend(queue, other_queue);
	
	status *= (original_size + original_other_size == QueueSize(queue)) ? 1 : 0;
	
	status *= (num1 == (int)(long)QueuePeek(queue)) ? 1 : 0;
	Dequeue(queue);
	status *= (num2 == (int)(long)QueuePeek(queue)) ? 1 : 0;
	Dequeue(queue);
	status *= (num3 == (int)(long)QueuePeek(queue)) ? 1 : 0;
	Dequeue(queue);
	status *= (num4 == (int)(long)QueuePeek(queue)) ? 1 : 0;
	Dequeue(queue);
	status *= (num5 == (int)(long)QueuePeek(queue)) ? 1 : 0;
	Dequeue(queue);
	status *= (num6 == (int)(long)QueuePeek(queue)) ? 1 : 0;
	Dequeue(queue);
	
	status *= (QueueIsEmpty(queue)) ? 1 : 0;
	
	(status) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/

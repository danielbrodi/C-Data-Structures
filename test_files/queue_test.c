/**********************************FILE-HEADER*********************************\
* File: queue_test.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 29/03/2021							   								
* Version: 1.0 (Before Review)					   								
* Reviewer: Ariel							   								
* Description: Queue implementation tests.			 
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stddef.h>	/* size_t */
#include <stdio.h>	/* printf, fprintf */
#include <stdlib.h> /* rand, srand */
#include <string.h> /* strcmp */
#include <time.h>	/* time */

#include "../include/utils.h" /* status_ty, bolean_ty, ANSI_COLOR_*/
#include "../include/queue.h"

/***************************** Macros Definitions *****************************/
/* prints colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 0 to 99 */
#define RANDOM_NUM rand() % 100

#define UNUSED(x) (void)(x)
/****************************Forward Declarations******************************/
static void QueueCreateTest(queue_ty *queue);
static void QueueDestroyTest(queue_ty *queue);
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
	queue_ty *other_queue = QueueCreate();
	
	/* Intializes random number generator */
	srand(time(0));
	
	QueueCreateTest(new_queue);
	QueueEnqueueTest(new_queue);
	QueuePeekTest(new_queue);
	QueueDequeueTest(new_queue);
	QueueIsEmptyTest(new_queue);
	QueueAppendTest(new_queue, other_queue);
	QueueDestroyTest(new_queue);
	QueueDestroyTest(other_queue);
	
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
void QueueDestroyTest(queue_ty *queue)
{
	QueueDestroy(queue);
	printf (ANSI_COLOR_CYAN "\nThe queue has been deleted\n\n"
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
	
	printf("\n\nQueue Append Test:\n");
	
	printf("SIZE: %lu", QueueSize(queue));
	/* queue filling */
	printf("\nQueue A:\n");
	printf("Inserts element:");
	SUCCESS == Enqueue(queue, (void *)(long)num1) ? PRINT_SUCCESS : PRINT_FAILURE;
	printf("Inserts element:");
	SUCCESS == Enqueue(queue, (void *)(long)num2) ? PRINT_SUCCESS : PRINT_FAILURE;
	printf("Inserts element:");
	SUCCESS == Enqueue(queue, (void *)(long)num3) ? PRINT_SUCCESS : PRINT_FAILURE;
	printf("\nList:\n");
	printf("SIZE: %lu", QueueSize(queue));
	PrintQueue(queue);
	
	/* other_queue filling */
	printf("\nQueue B:\n");
	printf("Inserts element:");
	SUCCESS == Enqueue(other_queue, (void *)(long)num4) ? PRINT_SUCCESS : PRINT_FAILURE;
	printf("Inserts element:");
	SUCCESS == Enqueue(other_queue, (void *)(long)num5) ? PRINT_SUCCESS : PRINT_FAILURE;
	printf("Inserts element:");
	SUCCESS == Enqueue(other_queue, (void *)(long)num6) ? PRINT_SUCCESS : PRINT_FAILURE;
	printf("\nList:\n");
	PrintQueue(other_queue);
	
	printf (ANSI_COLOR_CYAN "\nAfter Merge:\n\n" ANSI_COLOR_RESET);
	QueueAppend(queue, other_queue);
	
	printf("Queue A:\n");
	PrintQueue(queue);
	
	printf("Queue B:\n");
	PrintQueue(other_queue);
}

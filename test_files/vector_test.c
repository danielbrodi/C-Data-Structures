/****************************** File Header ***********************************\
* File Name: vector_test.c
* Author: Daniel Brodsky
* Description: Dynamic Vector use and functions tests.
* Date: 17/03/2021
* Version: 1.0 (Before Review)
* Reviewer: Rostik
\******************************************************************************/

/********************************** Inclusions ********************************/

#include <stdio.h> /* printf, fprintf */
#include <string.h> /* strcmp */

#include "vector.h"

/***************************** Macros Definitions *****************************/

/* escape keys for printf to color output for StdOut */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/**********************Forward Declarations************************************/

void VectorCreateTest(vector_ty *vector);
void VectorSizeTest(vector_ty *vector);
void VectorCapacityTest(vector_ty *vector);
void VectorPushBackTest(vector_ty *vector);
void VectorPopBackTest(vector_ty *vector);
void VectorGetElementTest(vector_ty *vector);
void VectorSetElementTest(vector_ty *vector);
void VectorReserveTest(vector_ty *vector);
void VectorShrinkToFitTest(vector_ty *vector);
void VectorDestroyTest(vector_ty *vector);

/***************************Main Function**************************************/

int main()	
{
	vector_ty *new_vector = VectorCreate(5);
	if (NULL == new_vector)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return(FAILURE);
	}
	
	VectorCreateTest(new_vector);
	VectorSizeTest(new_vector);
	VectorCapacityTest(new_vector);
	VectorPushBackTest(new_vector);
	VectorPopBackTest(new_vector);
	VectorGetElementTest(new_vector);
	VectorSetElementTest(new_vector);
	VectorReserveTest(new_vector);
	VectorShrinkToFitTest(new_vector);
	VectorDestroyTest(new_vector);
	
	return(SUCCESS);
}

/************************Test Functions Implementations************************/

/******************************************************************************/
void VectorCreateTest(vector_ty *vector)
{
	printf("\nVector Creatation Test: ");
	if(NULL == vector)
	{
		PRINT_FAILURE;
	}
	else
	{
	PRINT_SUCCESS;
	}
}
/******************************************************************************/
void VectorDestroyTest(vector_ty *vector)
{
	VectorDestroy(vector);
	printf (ANSI_COLOR_CYAN "\nVector has been freed\n\n" ANSI_COLOR_RESET);
}
/******************************************************************************/
void VectorSizeTest(vector_ty *new_vector)
{
	printf("Vector Size Test: ");
	VectorPushBack(new_vector, "0.Yosi");
	VectorPushBack(new_vector, "1.Daniel");
	VectorPushBack(new_vector, "2.Eli");
	VectorPushBack(new_vector, "3.Rocky");
	VectorPushBack(new_vector, "4.Ken");
	VectorPushBack(new_vector, "5.Ted");
	VectorPushBack(new_vector, "6.Ben");
	if (7 != VectorSize(new_vector))
	{
		PRINT_FAILURE;
	}
	else
	{
	PRINT_SUCCESS;
	}
}
/******************************************************************************/
void VectorReserveTest(vector_ty *vector)
{
	printf("Vector Reserve Test: ");
	VectorReserve(vector,8);
	8 != VectorCapacity(vector) ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
void VectorShrinkToFitTest(vector_ty *vector)
{
	printf("Vector ShrinkToFit Test: ");
	VectorShrinkToFit(vector);
	VectorSize(vector) == VectorCapacity(vector) ? PRINT_SUCCESS : PRINT_FAILURE; 
														   
}
/******************************************************************************/
void VectorCapacityTest(vector_ty *vector)
{
	printf("Vector Capacity Test: ");
	10 != VectorCapacity(vector) ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
void VectorPushBackTest(vector_ty *vector)
{
	printf("Vector PushBack Test: ");
   	VectorPushBack(vector, "7.Alon") ? PRINT_FAILURE : PRINT_SUCCESS;
   	                                                       
}
/******************************************************************************/
void VectorPopBackTest(vector_ty *vector)
{
	printf("Vector PopBack Test: ");
	VectorPopBack(vector) ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
void VectorGetElementTest(vector_ty *vector)
{
	char *element = (char *)VectorGetElement(vector, 2);
	printf("Vector GetElement Test: ");
	!strcmp(element,"2.Eli") ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
void VectorSetElementTest(vector_ty *vector)
{
	char *element = NULL;
	printf("Vector SetElement Test: ");
	VectorSetElement(vector, 0, "Messi");
	element = (char *)VectorGetElement(vector, 0);
	!strcmp(element,"Messi") ? PRINT_SUCCESS : PRINT_FAILURE;
}

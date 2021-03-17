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

#include "vector.h"


/**********************Forward Declarations************************************/

void VectorCreateTest(vector_ty *vector);
void VectorSizeTest(vector_ty *vector);
void VectorCapacityTest(vector_ty *vector);
void VectorPushBackTest(vector_ty *vector);
void VectorPopBackTest(vector_ty *vector);
void VectorGetElementTest(vector_ty *vector);
void VectorSetElementTest(vector_ty *vector);
void VectorDestroyTest(vector_ty *vector);
void VectorReserveTest(vector_ty *vector);
void VectorShrinkToFitTest(vector_ty *vector);

/************************************Main Function*****************************/


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
	
	return(0);
}

/************************Test Functions Implementations************************/

/******************************************************************************/
void VectorCreateTest(vector_ty *vector)
{
	printf("\nVector Creatation Test: ");
	if(NULL == vector)
	{
		printf ("FAILURE");
	}
	printf("SUCCESS");
	printf("\n");
}

/******************************************************************************/
void VectorDestroyTest(vector_ty *vector)
{
	VectorDestroy(vector);
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
		printf("FAILURE");
	}
	
	printf("SUCCESS");
	printf("\n");
}

/******************************************************************************/
void VectorReserveTest(vector_ty *vector)
{
	printf("Vector Reserve Test: ");
	VectorReserve(vector,8);
	8 != VectorCapacity(vector) ? printf("FAILURE\n") : printf("SUCCESS\n");
}


/******************************************************************************/
void VectorShrinkToFitTest(vector_ty *vector)
{
	printf("Vector ShrinkToFit Test: ");
	VectorShrinkToFit(vector);
	VectorSize(vector) == VectorCapacity(vector) ? printf("SUCCESS\n") :
														   printf("FAILURE\n"); 
}

/******************************************************************************/
void VectorCapacityTest(vector_ty *vector)
{
	printf("Vector Capacity Test: ");
	10 != VectorCapacity(vector) ? printf("FAILURE\n") : printf("SUCCESS\n");
}

/******************************************************************************/
void VectorPushBackTest(vector_ty *vector)
{
	printf("Vector PushBack Test: ");
   	VectorPushBack(vector, "7.Alon") ? printf("FAILURE\n") :
   	                                                       printf("SUCCESS\n");
}

/******************************************************************************/
void VectorPopBackTest(vector_ty *vector)
{
	printf("Vector PopBack Test: ");
	VectorPopBack(vector) ? printf("FAILURE\n") : printf("SUCCESS\n");
}

/******************************************************************************/
void VectorGetElementTest(vector_ty *vector)
{
	char *element = (char *)VectorGetElement(vector, 2);
	printf("Vector GetElement Test: ");
	"2.Eli" == element ? printf("SUCCESS\n") : printf("FAILURE\n");
	/* strcmp */
}

/******************************************************************************/
void VectorSetElementTest(vector_ty *vector)
{
	char *element = NULL;
	printf("Vector SetElement Test: ");
	VectorSetElement(vector, 0, "Messi");
	element = (char *)VectorGetElement(vector, 0);
	"Messi" == element ? printf("SUCCESS\n") : printf("FAILURE\n");
	/* strcmp */
}




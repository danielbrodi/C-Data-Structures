/****************************** File Header ***********************************\
* File Name: vector_test.c
* Author: Daniel Brodsky
* Description: Dynamic Vector use and functions tests.
* Date: 17/03/2021
* Version: 1.0 (Before Review)
* Reviewer: Rostik
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "vector.h"


/******************************************************************************/

void VectorCreateTest(vector_ty *vector);
void VectorSizeTest(vector_ty *vector);
void VectorCapacityTest(vector_ty *vector);
void VectorPushBackTest(vector_ty *vector);
void VectorPopBackTest(vector_ty *vector);
void VectorGetElementTest(vector_ty *vector);
void VectorSetElementTest(vector_ty *vector);
void VectorDestroyTest(vector_ty *vector);
void VectorReserveTest(vector_ty *vector);

/************************************Main Function*****************************/


int main()	
{
	vector_ty *new_vector = VectorCreate(5);
	if (NULL == new_vector)
	{
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
	VectorDestroyTest(new_vector);
	
	return(0);
}

/* Creates a new vector of size initial_size */
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

/* Deletes entire Vector */
void VectorDestroyTest(vector_ty *vector)
{
	VectorDestroy(vector);
}

/* Returns the current number of elements in the vector */
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

/* Resizes the vector to new_size */
/* Returns SUCCESS upon successful resizing */
/* Note: shrinking the vector may delete previous elements */
void VectorReserveTest(vector_ty *vector)
{
	printf("Vector Reserve Test: ");
	VectorReserve(vector,8);
	8 != VectorCapacity(vector) ? printf("FAILURE\n") : printf("SUCCESS\n");
}


/* Resizes the vector to the current vector size */
/* Returns SUCCESS upon successful shrinking */
void VectorShrinkToFitTest(vector_ty *vector)
{}

/* Returns the current capacity Test(max size) of the vector */
void VectorCapacityTest(vector_ty *vector)
{
	printf("Vector Capacity Test: ");
	10 != VectorCapacity(vector) ? printf("FAILURE\n") : printf("SUCCESS\n");
}

/* Adds element to end of vector */
/* Returns SUCCESS upon successful addition */
void VectorPushBackTest(vector_ty *vector)
{
	printf("Vector PushBack Test: ");
   VectorPushBack(vector, "7.Alon") ? printf("FAILURE\n") : printf("SUCCESS\n");
}

/* Deletes the last element */
/* Returns SUCCESS upon successful deletion */
void VectorPopBackTest(vector_ty *vector)
{
	printf("Vector PopBack Test: ");
	VectorPopBack(vector) ? printf("FAILURE\n") : printf("SUCCESS\n");
}

/* Returns element at selected index */
/* Behavior is undefined for out of bounds indeces */
void VectorGetElementTest(vector_ty *vector)
{
	char *element = (char *)VectorGetElement(vector, 2);
	char eli[] = "2.Eli";
	printf("Vector GetElement Test: ");
	eli == element ? printf("FAILURE\n") : printf("SUCCESS\n");
}

/* Sets an element */
/* Behavior is undefined for out of bounds indeces */
void VectorSetElementTest(vector_ty *vector)
{
	size_t i = 0;
	char messi[] = "Messi";
	char *element = NULL;
	printf("Vector SetElement Test: ");
	VectorSetElement(vector, 0, "Messi");
	element = (char *)VectorGetElement(vector, 0);
	messi == element ? printf("FAILURE\n") : printf("SUCCESS\n");
}




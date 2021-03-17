/****************************** File Header ***********************************\
* File Name: vector_test.c
* Author: Daniel Brodsky
* Description: Dynamic Vector use and functions tests.
* Date: 17/03/2021
* Version: Beta
* Reviewer: Rostik
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "../include/vector.h"

/************************************Main Function*****************************/

int main()	
{
	size_t i = 0;
	vector_ty *new_vector = VectorCreate(5);
	
	printf("Initial - num_elements: %ld, capacity: %ld\n", VectorSize(new_vector), VectorCapacity(new_vector));

	VectorPushBack(new_vector, "0.Yosi");
	VectorPushBack(new_vector, "1.Daniel");
	VectorPushBack(new_vector, "2.Eli");
	VectorPushBack(new_vector, "3.Rocky");
	VectorPushBack(new_vector, "4.Ken");
	VectorPushBack(new_vector, "5.Ted");
	VectorPushBack(new_vector, "6.Ben");

	printf("After Add*7 - num_elements: %ld, capacity: %ld\n", VectorSize(new_vector), VectorCapacity(new_vector));

	VectorPopBack(new_vector);
	VectorPopBack(new_vector);
	VectorPopBack(new_vector);
	VectorPopBack(new_vector);
	VectorPopBack(new_vector);
	printf("After 5*PopBack - num_elements: %ld, capacity: %ld\n", VectorSize(new_vector), VectorCapacity(new_vector));
	VectorSetElement(new_vector, 1, "SetElementCheck");
	VectorShrinkToFit(new_vector);

	printf("After ShrinkToFit+SetElement - num_elements: %ld, capacity: %ld\n", VectorSize(new_vector), VectorCapacity(new_vector));
	
	VectorReserve(new_vector,8);
	
	printf("After Reserve->8 - num_elements: %ld, capacity: %ld\n", VectorSize(new_vector), VectorCapacity(new_vector));

	printf("\nvector data:\n\n");

	for (i = 0; i < VectorSize(new_vector); ++i)
	{
		printf("%s\n\n", (char*)VectorGetElement(new_vector,i));
	}

	VectorDestroy(new_vector);

	return 0;
}

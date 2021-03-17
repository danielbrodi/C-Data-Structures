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


/******************************************************************************/

void VectorCreateTest();
void VectorDestroyTest();
void VectorSizeTest();
void VectorCapacityTest();
void VectorPushBackTest();
void VectorGetElementTest();
void VectorSetElementTest();

/************************************Main Function*****************************/

/* Creates a new vector of size initial_size */
void VectorCreateTest()
{}

/* Deletes entire Vector */
void VectorDestroyTest()

/* Resizes the vector to new_size */
/* Returns SUCCESS upon successful resizing */
/* Note: shrinking the vector may delete previous elements */
void VectorReserveTest()
{}

/* Resizes the vector to the current vector size */
/* Returns SUCCESS upon successful shrinking */
void VectorShrinkToFitTest()
{}

/* Returns the current capacity Test(max size) of the vector */
void VectorCapacityTest()
{}

/* Adds element to end of vector */
/* Returns SUCCESS upon successful addition */
void VectorPushBackTest()
{}

/* Deletes the last element */
/* Returns SUCCESS upon successful deletion */
void VectorPopBackTest()
{}

/* Returns element at selected index */
/* Behavior is undefined for out of bounds indeces */
void VectorGetElementTest()
{}

/* Sets an element */
/* Behavior is undefined for out of bounds indeces */
void VectorSetElementTest()
{}

int main()	
{

}


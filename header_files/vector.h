#ifndef	__VECTOR_H__
#define	__VECTOR_H__

/****************************** File Header ***********************************\
* File Name: vector.h
* Author: Daniel Brodsky
* Description: Dynamic Vector data structure API overview.
* Date: 17/03/2021
* Version: 1.0
* Reviewer: Rostik
\******************************************************************************/

#include <stddef.h>	/* size_t */
#include "utils.h"	/* status_ty, bolean_ty	*/

typedef struct vector vector_ty;

/* Creates a new vector of size initial_size */
vector_ty *VectorCreate(size_t initial_size);

/* Deletes entire Vector */
void VectorDestroy(vector_ty *vector);

/* Resizes the vector to new_size */
/* Returns SUCCESS upon successful resizing */
/* Note: shrinking the vector may delete previous elements */
status_ty VectorReserve(vector_ty *vector, size_t new_size);

/* Resizes the vector to the current vector size */
/* Returns SUCCESS upon successful shrinking */
status_ty VectorShrinkToFit(vector_ty *vector);

/* Returns the current number of elements in the vector */
size_t VectorSize(const vector_ty *vector);

/* Returns the current capacity (max size) of the vector */
size_t VectorCapacity(const vector_ty *vector);

/* Adds element to end of vector */
/* Returns SUCCESS upon successful addition */
status_ty VectorPushBack(vector_ty *vector, void *element);

/* Deletes the last element */
/* Returns SUCCESS upon successful deletion */
status_ty VectorPopBack(vector_ty *vector);

/* Returns element at selected index */
/* Behavior is undefined for out of bounds indeces */
void *VectorGetElement(const vector_ty *vector, size_t index);

/* Sets an element */
/* Behavior is undefined for out of bounds indeces */
void VectorSetElement(vector_ty *vector, size_t index, void *element);

/*	Returns the actual array that included in the vector	*/
void** VectorGetActualArray(vector_ty*);

#endif	/* __VECTOR_H__ */

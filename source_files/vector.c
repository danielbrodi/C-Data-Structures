/****************************** File Header ***********************************\
* File Name: vector.c
* Author: Daniel Brodsky
* Description: Dynamic Vector API's functions implementations.
* Date: 17/03/2021
* Version: 3.0 (After group review)
* Reviewer: Rostik
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, realloc, free */
#include <assert.h> /* assert */

#include "utils.h"
#include "vector.h"

/******************************* Global Definitions ***************************/
struct vector
{
	void **items;
	size_t capacity;      
	size_t min_capacity;
	size_t size;
};

/************************Functions Implementations*****************************/

/******************************************************************************/
/* Creates a new vector of size initial_capacity */
vector_ty *VectorCreate(size_t initial_capacity)
{   
    vector_ty *new_vector = (vector_ty *)malloc(sizeof(vector_ty));
	if (NULL == new_vector)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return(NULL);
	}
	
	new_vector->capacity = initial_capacity;
	new_vector->min_capacity = initial_capacity;
	new_vector->size = 0;
	
	new_vector->items = malloc(sizeof(void *) * initial_capacity);
	if (NULL == new_vector->items)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		free(new_vector);
		return(NULL);
	}

	return(new_vector);
}
/******************************************************************************/
/* Deletes entire Vector */
void VectorDestroy(vector_ty *vector)
{
	assert(vector);	
	
	free(vector->items);
	vector->items = NULL;
	
	free(vector);
	vector = NULL;
}
/******************************************************************************/
/* Returns the current number of elements in the vector */
size_t VectorSize(const vector_ty *vector)
{
	assert(vector);
	
	return(vector->size);
}
/******************************************************************************/
/* Returns the current capacity (max size) of the vector */
size_t VectorCapacity(const vector_ty *vector)
{
	assert(vector);
	
	return(vector->capacity);
}
/******************************************************************************/
/* Resizes the vector to new_capacity */
/* Returns SUCCESS upon successful resizing */
/* Note: shrinking the vector may delete previous elements */
status_ty VectorReserve(vector_ty *vector, size_t new_capacity)
{
	void **resized_items = NULL;
	status_ty status = FAILURE;
	
	assert(vector);
	
	resized_items = realloc(vector->items, sizeof(void *) * new_capacity);
	if (NULL != resized_items)
	{
		vector->items = resized_items;
		resized_items = NULL;
		
		vector->capacity = new_capacity;
		vector->min_capacity = new_capacity;
		
		if(vector->capacity < vector->size)
		{
			vector->size = vector->capacity;
		}
		
		status = SUCCESS;
	}

	return(status);
}
/******************************************************************************/
/* Returns element at selected index */
/* Behavior is undefined for out of bounds indeces */
void *VectorGetElement(const vector_ty *vector, size_t index)
{
	assert(vector);
	assert(index < vector->size);
	
	return(vector->items[index]);
}
/******************************************************************************/
/* Adds element to end of vector */
/* Returns SUCCESS upon successful addition */
status_ty VectorPushBack(vector_ty *vector, void *element)
{
	status_ty status = SUCCESS;
	size_t original_min_capacity = 0;
	
	assert(vector);
	assert(element);
	
	if (vector->capacity == vector->size)
	{
		original_min_capacity = vector->min_capacity;
		status = VectorReserve(vector, vector->capacity * 2);
		vector->min_capacity = original_min_capacity;	
	}
	
	if (SUCCESS == status)
	{
		vector->items[vector->size] = element;
		++(vector->size);
	}
	
	return(status);
}
/******************************************************************************/
/* Resizes the vector to the current vector size */
/* Returns SUCCESS upon successful shrinking */
status_ty VectorShrinkToFit(vector_ty *vector)
{
	status_ty status = FAILURE;
	void **shrinked_items = NULL;
	
	assert(vector);
	
	shrinked_items = realloc(vector->items, 
									sizeof(void *) * vector->size);
	
	if (NULL != shrinked_items)
	{
		vector->items = shrinked_items;
		shrinked_items = NULL;
		
		vector->capacity = vector->size;
		
		status = SUCCESS;
	}
	
	return(status);
}
/******************************************************************************/
/* Deletes the last element */
/* Returns SUCCESS upon successful deletion */
status_ty VectorPopBack(vector_ty *vector)
{
	status_ty status = FAILURE;
	size_t original_min_capacity = 0;
	
	assert(vector);
	
	if(vector->size > 0)
	{
		--(vector->size);
		status = SUCCESS;
		
		if(vector->size * 4 <= vector->capacity && 
									vector->min_capacity * 2 < vector->capacity)
		{
			original_min_capacity = vector->min_capacity;
			status = VectorReserve(vector, vector->capacity / 2);
			vector->min_capacity = original_min_capacity;
		}
	}
	return(status);
}
/******************************************************************************/
/* Sets an element */
/* Behavior is undefined for out of bounds indeces */
void VectorSetElement(vector_ty *vector, size_t index, void *element)
{
	assert(vector);
	assert(index < vector->size);
	assert(element);
	
	vector->items[index] = element;
}
/******************************************************************************/
void** VectorGetActualArray(vector_ty *vector)
{
	assert(vector);
	
	return (vector->items);
}
/******************************************************************************/

/****************************** File Header ***********************************\
* File Name:  vector.h
* Author: Daniel Brodsky
* Description: Dynamic Vector API's functions implementations.
* Date: 16/03/2021
* Version: Beta
* Reviewer: Rostik
\******************************************************************************/
/********************************** Inclusions ********************************/
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "../include/vector.h"
/******************************* Globals & Statics ****************************/
struct vector
{
	void **items;
	size_t capacity;      
	size_t num_of_elements;
};
/************************Functions Implementations*****************************/

/*******************************************************************************
/* Creates a new vector of size initial_size */
vector_ty *VectorCreate(size_t initial_size)
{   
    vector_ty *new_vector = (vector_ty *)malloc(sizeof(stack_ty));
	if (NULL == new_vector)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return (NULL);
	}
	
	assert(initial_size >= 0);
	
	new_vector->capacity = initial_size;
	new_vector->num_of_elements = 0;
	
	new_vector->items = malloc(sizeof(void *) * initial_size);
	if (NULL == new_vector->items)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		free(new_vector);
		return (NULL);
	}

	return (new_vector);
}
/*******************************************************************************
/* Deletes entire Vector */
void VectorDestroy(vector_ty *vector)
{
	assert(vector);
	free(vector->items);
	free(vector);
	vector->items = NULL;
	vector = NULL;
}
/*******************************************************************************
/* Returns the current number of elements in the vector */
size_t VectorSize(const vector_ty *vector)
{
	assert(vector);
	
	return (vector->num_of_elements);
}
/*******************************************************************************
/* Returns the current capacity (max size) of the vector */
size_t VectorCapacity(const vector_ty *vector)
{
	assert(vector);
	
	return (vector->capacity);
}
/*******************************************************************************
/* Resizes the vector to new_size */
/* Returns SUCCESS upon successful resizing */
/* Note: shrinking the vector may delete previous elements */
status_ty VectorReserve(vector_ty *vector, size_t new_size)
{
	void **resized_items = NULL;
	status_ty status = FAILURE;
	
	assert(vector);
	assert(new_size >= 0);
	
	resized_items = realloc(vector->items, sizeof(void *) * new_size);
	if (resized_items != NULL)
	{
		vector->items = resized_items;
		vector->capacity = new_size;
		status = SUCCESS;
	}

	return (status);
}
/*******************************************************************************
/* Returns element at selected index */
/* Behavior is undefined for out of bounds indeces */
void *VectorGetElement(const vector_ty *vector, size_t index)
{
	assert(vector);
	assert(0 <= index < vector->num_of_elements);
	
	return (vector->items[index]);
}
/*******************************************************************************
/* Adds element to end of vector */
/* Returns SUCCESS upon successful addition */
status_ty VectorPushBack(vector_ty *vector, void *element)
{
	status_ty status = FAILURE;
	
	assert(vector);
	assert(element);
	
	if (vector->capacity == vector->num_of_elements)
	{
		status = VectorReserve(vector, vector->capacity * 2);
		if(status != FAILURE)
		{
		    vector->items[vector->num_of_elements + 1] = element;
		    status = SUCCESS;
		}
	}
	else
	{
		vector->items[vector->num_of_elements + 1] = element;
		status = SUCCESS;
	}
	
	return (status);
}
/*******************************************************************************
/* Resizes the vector to the current vector size */
/* Returns SUCCESS upon successful shrinking */
status_ty VectorShrinkToFit(vector_ty *vector)
{
	status_ty status = FAILURE;
	void **shrinked_items = NULL;
	
	assert(vector);
	
	shrinked_items = realloc(vector->items, 
									sizeof(void *) * vector->num_of_elements);
	
	if (shrinked_items != NULL)
	{
		vector->items = shrinked_items;
		vector->capacity = vector->num_of_elements;
		status = SUCCESS;
	}
	
	return (status);
}
/*******************************************************************************
/* Deletes the last element */
/* Returns SUCCESS upon successful deletion */
status_ty VectorPopBack(vector_ty *vector)
{
	status_ty status = FAILURE;
	
	assert(vector);
	
	if(vector->num_of_elements > 0)
	{
		vector->items[vector->num_of_elements - 1] = NULL;
		vector->items --;
		status = SUCCESS;
		
		if(vector->num_of_elements * 4 < vector->capacity)
		{
			status = VectorReserve(vector, vector->capacity / 2);
		}

	return (status);
}
/*******************************************************************************
/* Sets an element */
/* Behavior is undefined for out of bounds indeces */
void VectorSetElement(vector_ty *vector, size_t index, void *element)
{
	assert(vector);
	assert(0 <= index < vector->num_of_elements);
	assert(element);
	
	vector->items[index] = element;

}

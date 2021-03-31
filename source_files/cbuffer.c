/**********************************FILE-HEADER*********************************\
* File: cbuffer.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 30/03/2021							   								
* Version: Beta				   								
* Reviewer: Kobi							   								
* Description: Circular Buffer functions implementations.			 
\******************************************************************************/

#define BUFFER_CAPACITY (cbuf->capacity)
#define ARR_END_INDEX (cbuf->arr+cbuf->capacity)

/****************************** Inclusions ************************************/

#include <assert.h> /* assert */
#include <stddef.h>	/* size_t, NULL */
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, free */

#include "../include/utils.h" /* status_ty, bolean_ty */
#include "../include/cbuffer.h"

/************************** Global Definitions ********************************/

struct cbuffer
{
	char *read;
	char *write;
	size_t capacity;
	char arr[1];
};

/************************Functions Implementations*****************************/
/******************************************************************************/

cbuffer_ty *CBufferCreate(size_t capacity)
{
	cbuffer_ty *new_cbuffer = (cbuffer_ty *)malloc(sizeof(cbuffer_ty) + 
													sizeof(char * capacity));
	if(NULL == new_cbuffer)
	{
		fprintf("Memory allocation for a new cbuffer has been failed");
		return(NULL);
	}
	
	new_cbuffer->read = new_cbuffer->arr;
	new_cbuffer->write = new_cbuffer->arr;
	new_cbuffer->capacity = capacity;
	
	return(new_cbuffer);
}
/******************************************************************************/
void CBufferDestroy(cbuffer_ty *cbuf)
{
	assert(cbuf);
	
	free(cbuf);
	cbuf = NULL;
}
/******************************************************************************/
ssize_t CBufferWriteTo(cbuffer_ty *cbuf, const void *src, size_t count)
{
	size_t bytes_counter = 0
	;
	assert(cbuf);
	assert(src);
	
	while(*src && bytes_counter < count)
	{
	
		if (0 == CBufferFreeSpace(cbuf))
		{
			return(-1); /*buffer is full */
		}

		*write = *src;
		write = cbuf->arr + ((ARR_END_INDEX + (++write)) % BUFFER_CAPACITY);
		++src;
		++bytes_counter;
	}
	return(bytes_counter);
}
/******************************************************************************/
size_t CBufferFreeSpace(const cbuffer_ty *cbuf)
{
	assert(cbuf);
	
	if (cbuf->write >= cbuf->read)
	{
		return((cbuf->capacity) - (cbuf->write - cbuf->read));
	}
	else
	{
		return(cbuf->read - cbuf->write - 1);
	}
}
/******************************************************************************/
boolean_ty CBufferIsEmpty(const cbuffer_ty *cbuf)
{
	assert(cbuf);
	
	return(CBufferFreeSpace(cbuf) == cbuf->capacity);
}
/******************************************************************************/
size_t CBufferSize(const cbuffer_ty *cbuf)
{
	assert(cbuf);
	
	return(cbuf->capacity - CBufferFreeSpace(cbuf));
}

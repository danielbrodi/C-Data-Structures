/**********************************FILE-HEADER*********************************\
* File: cbuffer.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 30/03/2021							   								
* Version: Beta				   								
* Reviewer: Kobi							   								
* Description: Circular Buffer functions implementations.			 
\******************************************************************************/

#define BUFFER_CAPACITY (cbuf->capacity-1)
#define ARR_END_INDEX (cbuf->arr+cbuf->capacity)

/****************************** Inclusions ************************************/

#include <assert.h> /* assert */
#include <stddef.h>	/* size_t, NULL */
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, free */

#include "utils.h" /* status_ty, bolean_ty */
#include "cbuffer.h"

/************************** Global Definitions ********************************/

struct cbuffer
{
	char *read;
	char *(cbuf->write);
	size_t capacity;
	char arr[1];
};

/************************Functions Implementations*****************************/
/******************************************************************************/

cbuffer_ty *CBufferCreate(size_t capacity)
{
	cbuffer_ty *new_cbuffer = (cbuffer_ty *)malloc(sizeof(cbuffer_ty) + 
												(sizeof(char) * capacity+1));
	if(NULL == new_cbuffer)
	{
		fprintf("Memory allocation for a new cbuffer has been failed");
		return(NULL);
	}
	
	new_cbuffer->read = new_cbuffer->arr;
	new_cbuffer->cbuf->write = new_cbuffer->arr;
	/* One byte is used for detecting if the buffer is full. */
	new_cbuffer->capacity = capacity + 1; 
	
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
	size_t bytes_counter = 0;
	
	assert(cbuf);
	assert(src);
	
	if (0 == CBufferFreeSpace(cbuf))
		{
			return(-1); /*buffer is full */
		}
	
	if(count > CBufferFreeSpace(cbuf))
	{
		count = CBufferFreeSpace(cbuf);
	}
	
	while(*src && bytes_counter < count)
	{
		*(cbuf->write) = *src;
		cbuf->write = cbuf->arr + ((ARR_END_INDEX + (++cbuf->write)) 
															% BUFFER_CAPACITY);
		++src;
		++bytes_counter;
	}
	
	return(bytes_counter);
}
/******************************************************************************/
ssize_t CBufferReadFrom(cbuffer_ty *cbuf, void *dest, size_t count)
{
	size_t bytes_counter = 0;
	
	assert(cbuf);
	assert(dest);
	
	if (CBufferIsEmpty(cbuf))
		{
			return(-1); /*buffer is empty, nothing to read */
		}
	
	if(count > BUFFER_CAPACITY)
	{
		count = BUFFER_CAPACITY;
	}
	
	while(*dest && bytes_counter < count)
	{
		*dest = *(cbuf->read);
		cbuf->read = cbuf->arr + ((ARR_END_INDEX + (++cbuf->read))
															 % BUFFER_CAPACITY);
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
		return((cbuf->capacity) - 1 - (cbuf->write - cbuf->read));
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
	
	return(CBufferFreeSpace(cbuf) == cbuf->capacity - 1);
}
/******************************************************************************/
size_t CBufferSize(const cbuffer_ty *cbuf)
{
	assert(cbuf);
	
	return(cbuf->capacity - 1 - CBufferFreeSpace(cbuf));
}

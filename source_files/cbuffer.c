/**********************************FILE-HEADER*********************************\
* File: cbuffer.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 30/03/2021							   								
* Version: 1.0 (Before Review)		   								
* Reviewer: Kobi							   								
* Description: Circular Buffer functions implementations.			 
\******************************************************************************/

/****************************** Inclusions ************************************/

#include <assert.h>	/* assert */
#include <stddef.h>	/* size_t, NULL */
#include <stdio.h>	/* fprintf */
#include <stdlib.h>	/* malloc, free */

#include "cbuffer.h"
#include "utils.h"	/* status_ty, bolean_ty */

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
												(sizeof(char) * capacity + 1));
	if(NULL == new_cbuffer)
	{
		fprintf(stderr, "Failed to allocate memory for a new queue\n");
		return(NULL);
	}
	
	new_cbuffer->read = new_cbuffer->arr;
	new_cbuffer->write = new_cbuffer->arr;
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
	char *src_runner = NULL;
	
	assert(cbuf);
	assert(src);
	
	src_runner = (char *)src;
	
	if (0 == CBufferFreeSpace(cbuf))
		{
			return(-1); /*buffer is full */
		}
	
	while(0 != CBufferFreeSpace(cbuf) && bytes_counter < count)
	{
		*(cbuf->write) = *src_runner;
		
		cbuf->write = (cbuf->write) == (cbuf->arr + cbuf->capacity - 1) ? 
													cbuf->arr : cbuf->write + 1;
		++src_runner;
		++bytes_counter;
	}
	
	return(bytes_counter);
}
/******************************************************************************/
ssize_t CBufferReadFrom(cbuffer_ty *cbuf, void *dest, size_t count)
{
	char *dest_runner = NULL;
	size_t bytes_counter = 0;
	
	assert(cbuf);
	assert(dest);
	
	dest_runner = (char *)dest;
	
	if (CBufferIsEmpty(cbuf))
		{
			return(-1); /*buffer is empty, nothing to read */
		}
	
	while(!CBufferIsEmpty(cbuf) && bytes_counter < count)
	{
		*dest_runner = *(cbuf->read);
		cbuf->read = (cbuf->read) == (cbuf->arr + cbuf->capacity - 1) ?
													 cbuf->arr : cbuf->read + 1;
		++dest_runner;
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

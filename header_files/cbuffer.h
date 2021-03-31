/****************************** File Header ***********************************\
* File: 		cbuffer.h					   
* Date: 		29/03/2021					   
* Version: 		1.1  						   
* Description: 	Circular Buffer API			    
\******************************************************************************/

#ifndef	__CBUFFER_H__
#define	__CBUFFER_H__

#include <stddef.h>	/* size_t */
#include <sys/types.h> /* ssize_t */

#include "../include/utils.h" /* bolean_ty */

typedef struct cbuffer cbuffer_ty;

/* Creates an empty cbuffer with capacity available bytes */
/* Returns a pointer to a cbuffer handler, or NULL on failure */
/* Complexity: O(1) */
cbuffer_ty *CBufferCreate(size_t capacity);

/* Frees entire cbuffer */
/* Complexity: O(1) */
void CBufferDestroy(cbuffer_ty *cbuf);

/* Writes count bytes from src into cbuf */
/* Returns number of bytes written, or -1 on error or cbuf is full */
/* May return a value smaller than count if not enough space in cbuf */
/* SSIZE_MAX is the largest possible count */
/* Undefined behavior if cbuf and/or src is NULL */
/* Complexity: O(n) */
ssize_t CBufferWriteTo(cbuffer_ty *cbuf, const void *src, size_t count);

/* Reads count bytes from cbuf into dest */
/* Returns number of bytes read, or -1 on error or if cbuf is empty */
/* May return a value smaller than count if fewer than count bytes in cbuf */
/* SSIZE_MAX is the largest possible count */
/* Undefined behavior if cbuf and/or dest is NULL */
/* Complexity: O(n) */
ssize_t CBufferReadFrom(cbuffer_ty *cbuf, void *dest, size_t count);

/* Returns number of occupied bytes in cbuf */
/* Undefined behavior if cbuf is NULL */
/* Complexity: O(1) */
size_t CBufferSize(const cbuffer_ty *cbuf);

/* Returns number of free bytes in cbuf */
/* Undefined behavior if cbuf is NULL */
/* Complexity: O(1) */
size_t CBufferFreeSpace(const cbuffer_ty *cbuf);

/* Returns TRUE if cbuf is empty or FALSE otherwise */
/* Undefined behavior if cbuf is NULL */
/* Complexity: O(1) */
boolean_ty CBufferIsEmpty(const cbuffer_ty *cbuf);

#endif	/* __CBUFFER_H__ */

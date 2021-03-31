/**********************************FILE-HEADER*********************************\
*	File: cbuffer_pseudo.c					 		  								
*	Author: Daniel Brodsky					  								
*	Date: 31/03/2021							   														   								
*	Description: Pseudocode for circular buffer's functions implementations.	 
\******************************************************************************/

struct cbuffer
{
	char *read;
	char *write;
	size_t capacity;
	char arr[1];
};

/******************************************************************************/
/* Creates an empty cbuffer with capacity available bytes */
/* Returns a pointer to a cbuffer handler, or NULL on failure */
/* Complexity: O(1) */

cbuffer_ty *CBufferCreate(size_t capacity)
{
	/*
	memory allocation for a new cbuffer ptr: 
	size of cbuffer struct + (sizeof(char) * (capacity + 1))
	Extra one byte is used for detecting if the buffer is full. 
	
	Reset write and read pointers to the beginning of the buffer:
	assign the address of arr to the write pointer
	assign the address of arr to the read pointer
	
	set cbuffer->capacity as capacity + 1 (due to the extra one byte);
	*/
}
/******************************************************************************/
/* Frees entire cbuffer */
/* Complexity: O(1) */

void CBufferDestroy(cbuffer_ty *cbuf)
{
	/*
	free cbuf - free the whole memory sequence that was allocated
	to the struct handler and to the array.
	*/
}
/******************************************************************************/
/* Writes count bytes from src into cbuf */
/* Returns number of bytes written, or -1 on error or cbuf is full */
/* May return a value smaller than count if not enough space in cbuf */
/* SSIZE_MAX is the largest possible count */
/* Undefined behavior if cbuf and/or src is NULL */
/* Complexity: O(n) */

ssize_t CBufferWriteTo(cbuffer_ty *cbuf, const void *src, size_t count)
{
	/*
	check if the buffer is full and return -1 if it does.
	
	set counter that will count the amount of bytes which have been written.
	
	if count > FreeSpace:
		set count as the amount of the available bytes in the buffer.
		
	loop over src till the end or till count is 0:
		insert data from src to the array using the write pointer
		promote both src and write pointers and incremenet the counter by one.
		
		check if write pointer is out of bounds of the array using the modulo
		operator and set the new address which is pointed by the write pointer
		as: 
			( 
			
			array_start_index address + 
			array_end_index address + 
			promoted_write_address
			
			%
			
			cbuf->capacity - 1
			
			)
			
			this will insure that the write pointer will point to addresses
			that wrapped in the array.
			
			return the value of the bytes counter.
	*/
}
/******************************************************************************/
/* Reads count bytes from cbuf into dest */
/* Returns number of bytes read, or -1 on error or if cbuf is empty */
/* May return a value smaller than count if fewer than count bytes in cbuf */
/* SSIZE_MAX is the largest possible count */
/* Undefined behavior if cbuf and/or dest is NULL */
/* Complexity: O(n) */

ssize_t CBufferReadFrom(cbuffer_ty *cbuf, void *dest, size_t count)
{
	/*
	check if the buffer is empty and return -1 if it does.
	
	if count > buffer size:
		set count as the max size available which is the buffer/array size.
		
	set counter that will count the amount of bytes which have been readed.
		
	loop till count is 0:
		insert data from buffer to dest using the read pointer
		promote both dest and read pointers and incremenet the counter by one.
		
		check if read pointer is out of bounds of the array using the modulo
		operator and set the new address which is pointed by the read pointer
		as: 
			( 
			
			array_start_index address + 
			array_end_index address + 
			promoted_read_address
			
			%
			
			cbuf->capacity - 1
			
			)
			
			this will insure that the read pointer will point to addresses
			that wrapped in the array.
			
			return the value of the bytes counter.
	*/
}
/******************************************************************************/
/* Returns number of occupied bytes in cbuf */
/* Undefined behavior if cbuf is NULL */
/* Complexity: O(1) */

size_t CBufferSize(const cbuffer_ty *cbuf)
{
	/*
	return(Capacity - FreeSpace)
	*/
}
/******************************************************************************/
/* Returns number of free bytes in cbuf */
/* Undefined behavior if cbuf is NULL */
/* Complexity: O(1) */

size_t CBufferFreeSpace(const cbuffer_ty *cbuf);
/******************************************************************************/
/* Returns TRUE if cbuf is empty or FALSE otherwise */
/* Undefined behavior if cbuf is NULL */
/* Complexity: O(1) */

boolean_ty CBufferIsEmpty(const cbuffer_ty *cbuf)
{
	/*
	return read == write
	*/
}
/******************************************************************************/

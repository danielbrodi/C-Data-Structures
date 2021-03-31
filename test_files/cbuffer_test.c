/**********************************FILE-HEADER*********************************\
* File: cbuffer_test.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 30/03/2021							   								
* Version: 1.0 (Before Review)					   								
* Reviewer: Kobi							   								
* Description: Circular Buffer implementation tests.			 
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stddef.h>	/* size_t, NULL */
#include <stdio.h>	/* printf */
#include <string.h> /* strlen */

#include "cbuffer.h"
#include "utils.h"	/* status_ty, boolean_ty, ANSI_COLOR_*/

/***************************** Macros Definitions *****************************/
/* prints colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/****************************Forward Declarations******************************/
static void CBufferCreateTest(cbuffer_ty *cbuf);
static void CBufferDestroyTest(cbuffer_ty *cbuf);
static void CBufferWriteToTest(cbuffer_ty *cbuf);
static void CBufferReadFromTest(cbuffer_ty *cbuf);
static void CBufferIsEmptyTest(cbuffer_ty *cbuf);
static void CBufferSizeTest(cbuffer_ty *cbuf);
static void CBufferFreeSpaceTest(cbuffer_ty *cbuf);
/******************************************************************************/
/********************************Main Function*********************************/
int main()	
{
	/* Intializes an empty CBuffer with 10 bytes capacity */
	cbuffer_ty *new_CBuffer = CBufferCreate(10);
	
	CBufferCreateTest(new_CBuffer);
	CBufferWriteToTest(new_CBuffer);
	CBufferReadFromTest(new_CBuffer);
	CBufferIsEmptyTest(new_CBuffer);
	CBufferSizeTest(new_CBuffer);
	CBufferFreeSpaceTest(new_CBuffer);
	CBufferDestroyTest(new_CBuffer);
	
	return(0);
}
/******************************************************************************/
/************************Test Functions Implementations************************/
/******************************************************************************/
static void CBufferCreateTest(cbuffer_ty *cbuf)
{
	printf("\nCBuffer Creation Test: ");
	NULL == cbuf ? PRINT_FAILURE : PRINT_SUCCESS;
}
/******************************************************************************/
static void CBufferDestroyTest(cbuffer_ty *cbuf)
{
	CBufferDestroy(cbuf);
	printf (ANSI_COLOR_CYAN "\nThe buffer has been deleted\n\n"
	 														ANSI_COLOR_RESET);
}
/******************************************************************************/
static void CBufferWriteToTest(cbuffer_ty *cbuf)
{
	boolean_ty is_works = TRUE;
	
	char dest[10] = {0};
	
	char *str = "HelloDaniel";
	ssize_t bytes_to_write = strlen(str);
	
	printf("CBuffer WriteTo Test: ");
	
	/* fully fill up the buffer */
	is_works *= CBufferWriteTo(cbuf, str, bytes_to_write) == bytes_to_write - 1;
	
	/* writing sholdn't be allowed because the buffer is full */
	is_works *= CBufferWriteTo(cbuf, str, bytes_to_write) == -1;
	
	/* empty the buffer */
	is_works *= CBufferReadFrom(cbuf, dest, bytes_to_write) == bytes_to_write-1;
	
	TRUE == is_works ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void CBufferReadFromTest(cbuffer_ty *cbuf)
{
	boolean_ty is_works = TRUE;
	
	char dest[10] = {"\0"};
	
	char *is_match = NULL;
	char *str = "1234567890";
	size_t i = 0;
	
	printf("CBuffer ReadFrom Test: ");
	
	/* list should be empty */
	is_works *= CBufferReadFrom(cbuf, dest, 4) == -1; 
	
	/* write 1-5 */
	is_works *= CBufferWriteTo(cbuf, str, 5) == 5;
	
	/* read 1,2,3 and copy to the array and remove from the buffer
		array should be: 1,2,3 buffer should be: 4,5 */
	is_works *= CBufferReadFrom(cbuf, dest, 3) == 3;
	
	/* write 1,2,3,4,5 again to the buffer
		buffer should be: 4,5,1,2,3,4,5 */
	is_works *= CBufferWriteTo(cbuf, str, 5) == 5;
	
	/* read next 3 elemenets from the buffer which should be: 4,5,1. 
		Copy to the array and remove from the buffer */
	is_works *= CBufferReadFrom(cbuf, dest, 3) == 3;

	is_match = "451";
	
	while(*is_match)
	{
		is_works *= dest[i] == *is_match;
		++is_match;
		++i;
	}
	
	TRUE == is_works ? PRINT_SUCCESS : PRINT_FAILURE;
	
	/* buffer should contain: 2,3,4,5 */
	/* empty the buffer */
	CBufferReadFrom(cbuf, dest, CBufferSize(cbuf));
}
/******************************************************************************/
static void CBufferIsEmptyTest(cbuffer_ty *cbuf)
{
	/* received buffer should be empty */
	printf("CBuffer IsEmpty Test: ");
	
	TRUE == CBufferIsEmpty(cbuf) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void CBufferSizeTest(cbuffer_ty *cbuf)
{
	/* received buffer should be empty */
	
	boolean_ty is_works = TRUE;
	size_t size_should_be = 1;
	
	char *src = "12345";
	
	printf("CBuffer Size Test: ");
	
	/* fill up the buffer and check each time the size of it */
	while(*src)
	{
		CBufferWriteTo(cbuf, src, 1);
		is_works *= CBufferSize(cbuf) == size_should_be;
		++src;
		++size_should_be;
	}
	
	TRUE == is_works ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void CBufferFreeSpaceTest(cbuffer_ty *cbuf)
{
	/* received buffer should be 1,2,3,4,5 */
	
	boolean_ty is_works = TRUE;
	size_t size_should_be = 4;
	
	char *src = "12345";
	
	printf("CBuffer FreeSpace Test: ");
	
	/* fill up the buffer and check each time the Free Space */
	while(*src)
	{
		CBufferWriteTo(cbuf, src, 1);
		is_works *= CBufferFreeSpace(cbuf) == size_should_be;
		++src;
		--size_should_be;
	}
	
	TRUE == is_works ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/

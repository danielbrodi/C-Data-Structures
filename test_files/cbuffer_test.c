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
#include <stdlib.h> /* rand, srand */
#include <time.h>	/* time */

#include "utils.h" /* status_ty, bolean_ty, ANSI_COLOR_*/
#include "cbuffer.h"

/***************************** Macros Definitions *****************************/
/* prints colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 1 to 100 */
#define RANDOM_NUM (rand() % 100 + 1)

#define UNUSED(x) (void)(x)
/****************************Forward Declarations******************************/
static void CBufferCreateTest(cbuffer_ty *cbuf);
/*static void CBufferDestroyTest(cbuffer_ty *cbuf);*/
/*static void CBufferWriteToTest(cbuffer_ty *cbuf);*/
/*static void CBufferReadFromTest(cbuffer_ty *cbuf);*/
/*static void CBufferIsEmptyTest(cbuffer_ty *cbuf);*/
/*static void CBufferSizeTest(cbuffer_ty *cbuf);*/
/*static void CBufferFreeSpaceTest(cbuffer_ty *cbuf);*/
/******************************************************************************/
/********************************Main Function*********************************/
int main()	
{
	/* Intializes an empty CBuffer with 10 bytes capacity */
	cbuffer_ty *new_CBuffer = CBufferCreate(10);
	
	/* Intializes random number generator */
	srand(time(0));
	
	CBufferCreateTest(new_CBuffer);
/*	CBufferEnCBufferTest(new_CBuffer);*/
/*	CBufferPeekTest(new_CBuffer);*/
/*	CBufferDeCBufferTest(new_CBuffer);*/
/*	CBufferIsEmptyTest(new_CBuffer);*/
/*	CBufferAppendTest(new_CBuffer, second_CBuffer);*/
/*	CBufferDestroyTest(new_CBuffer, second_CBuffer);*/
	
	return(0);
}
/******************************************************************************/
/************************Test Functions Implementations************************/
/******************************************************************************/
static void CBufferCreateTest(cbuffer_ty *cbuf)
{
	printf("\nCBuffer Creatation Test: ");
	NULL == cbuf ? PRINT_FAILURE : PRINT_SUCCESS;
}

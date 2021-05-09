/*********************************FILE__HEADER*********************************\
* File:				assert_imp.c						 		  								
* Author:			Daniel Brodsky					  								
* Date:				06/05/2021						   								
* Version:			1.0		
* Code Reviewer:	Omer						   								
* Description:		Implementation of an assert macro.		 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <stdio.h>		/*	fprintf, printf, null	*/		
#include <stdlib.h>		/*	abort					*/	

/***************************** Macros Definitions *****************************/
#define ASSERT(expr)                                                        \
    ((expr) ?                                                               \
        (void) 0 :                                                          \
        (void) (fprintf(stderr, "%s:%d: Assertion `%s` failed.\n",      	\
                        __FILE__, __LINE__, #expr), abort()))

/******************************************************************************/
int main()
{
	void *null_ptr = NULL;
	
	ASSERT(NULL != null_ptr);
	
	printf("ALL WORKS");
	
	return (0);
}

/******************************************************************************/

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
#include <stdlib.h>		/*	exit					*/	

/***************************** Macros Definitions *****************************/
#define ASSERT(expr) \
    if (!(expr)){ \
        fprintf(stderr, "%s:%d: Assertion `%s` failed.\n" \
        		,__FILE__, __LINE__, #expr); exit(1); }

/******************************************************************************/
int main()
{
	void *null_ptr = NULL;
	
	ASSERT(NULL != null_ptr);
	
	printf("ALL WORKS");
	
	return (0);
}

/******************************************************************************/

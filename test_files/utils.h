/***********************************************
* File: utils.h								   *
* Author: Rostik Angelevich					   *
* Date: 16/03/2021							   *
* Version: 1.0  							   *
* Description: Utility code					   * 
************************************************/
#ifndef	__UTILS_H__
#define	__UTILS_H__

#ifndef NDEBUG 
	#include <stdio.h>
#endif /* NDEBUG */

#define RED   "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define VOID_PTR_TO_INT(x) ((int)(long)(x))
#define INT_TO_VOID_PTR(x) ((void *)(long)(x))
#define LEN_OF_LOCAL_ARR(arr) (sizeof(arr)/sizeof(arr[0]))

#define WRITE_PASSED (printf(GREEN "Passed.\n" RESET))
#define WRITE_FAILED (printf(RED "Failed at line %d.\n" RESET, __LINE__))

#define UNUSED(X) (void)X;

typedef enum boolean
{
	FALSE,
	TRUE
} boolean_ty;

typedef enum status
{
	SUCCESS,
	FAILURE
} status_ty;

#endif	/* __UTILS_H__ */



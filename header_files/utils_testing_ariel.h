#ifndef	__UTILS_TESTING_H__
#define	__UTILS_TESTING_H__

#include <stdio.h>	/* fprintf */

#include "ANSI-color-codes.h"

typedef enum
{
	FALSE,
	TRUE
} boolean_ty;

/******************************************************************************/

typedef enum
{
	SUCCESS,
	FAILURE
} status_ty;

/* escape keys for printf to color output for StdOut */
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define YELLOW	"\x1b[33m"
#define RESET   "\x1b[0m"


#define PRINT_CREATE_FAIL	fprintf(stderr, RED "Failed to create data structure\n" RESET);
#define PRINT_TEST_CASE(message)	fprintf(stdout, YELLOW message RESET);
#define PRINT_SUCCESS(status)	\
						if (status == SUCCESS)	\
						{	\
							fprintf(stdout, GREEN "Test successful!\n" RESET); \
						}	\
						status = SUCCESS;


/* Testing macros, comparing function output and a test */
#define CREATE_TEST(object)	\
	if (NULL == object)	\
	{	\
		PRINT_CREATE_FAIL	\
		return (-1);	\
	}	

/* Output is a printed message */
#define PRINT_TEST(func, object, test, message)	\
	if (test != func(object)) \
	{	\
		fprintf(stderr, RED "%s failed at line %d\n" RESET, message, __LINE__); \
	}	\
	else	\
	{	\
		fprintf(stdout, GREEN "%s succeeded\n" RESET, message);\
	}

#define PRINT_TEST_2PARAM(func, object, item, test, message)	\
	if (test != func(object, item)) \
	{	\
		fprintf(stderr, RED "%s failed at line %d\n" RESET, message, __LINE__); \
	}	\
	else	\
	{	\
		fprintf(stdout, GREEN "%s succeeded\n" RESET, message);\
	}

/* On error, stderr message printed and a status variable is set to FAILURE */
#define STRUCT_STATUS_TEST(element, func, param1, test, message)	\
	if (test != (func(param1))->element) \
	{	\
		fprintf(stderr, RED "%s failed at line %d\n" RESET, message, __LINE__); \
		status = FAILURE;	\
	}

#define STATUS_TEST(func, param1, test, message)	\
	if (test != func(param1)) \
	{	\
		fprintf(stderr, RED "%s failed at line %d\n" RESET, message, __LINE__); \
		status = FAILURE;	\
	}

#define STATUS_TEST_2PARAM(func, param1, param2, test, message)	\
	if (test != func(param1, param2)) \
	{	\
		fprintf(stderr, RED "%s failed at line %d\n" RESET, message, __LINE__); \
		status = FAILURE;	\
	}

#define STATUS_TEST_3PARAM(func, param1, param2, param3, test, message)	\
	if (test != func(param1, param2, param3)) \
	{	\
		fprintf(stderr, RED "%s failed at line %d\n" RESET, message, __LINE__); \
		status = FAILURE;	\
	}

#endif	/* __UTILS_TESTING_H__ */

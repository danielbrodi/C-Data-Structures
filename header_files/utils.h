/****************************** File Header ***********************************\
* File Name: utils.h
* Author: Daniel Brodsky
* Description: Utilities for different API's.
\******************************************************************************/
#ifndef	__UTILS_H__
#define	__UTILS_H__
/******************************************************************************/
#include <stdio.h>
#include <assert.h>

/* escape keys for printf to color output for StdOut */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

/* print colored output of SUCCESS and FAILURE */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

#define PRINT_RED printf(ANSI_COLOR_RED)
#define PRINT_GREEN printf(ANSI_COLOR_GREEN)
#define PRINT_CYAN printf(ANSI_COLOR_CYAN)
#define RESET_PRINT_COLOR printf(ANSI_COLOR_RESET)
/******************************************************************************/

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
/******************************************************************************/
#endif	/* __UTILS_H__ */

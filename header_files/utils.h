/****************************** File Header ***********************************\
* File Name: utils.h
* Author: Daniel Brodsky
* Description: Utilities for different API's.
\******************************************************************************/
#ifndef	__UTILS_H__
#define	__UTILS_H__
/******************************************************************************/
/* escape keys for printf to color output for StdOut */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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

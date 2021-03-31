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

#include "../include/utils.h" /* status_ty, bolean_ty, ANSI_COLOR_*/
#include "../include/cbuffer.h"

/***************************** Macros Definitions *****************************/
/* prints colored output */
#define PRINT_SUCCESS printf (ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET)
#define PRINT_FAILURE printf (ANSI_COLOR_RED "FAILURE\n" ANSI_COLOR_RESET)

/* generates random number from 1 to 100 */
#define RANDOM_NUM (rand() % 100 + 1)

#define UNUSED(x) (void)(x)
/****************************Forward Declarations******************************/

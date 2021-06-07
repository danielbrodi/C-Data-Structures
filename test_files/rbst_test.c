/*********************************FILE__HEADER*********************************\
* File:				rbst.c						 		  								
* Author:			Daniel Brodsky					  								
* Date:				06-06-2021			   								
* Version:			1.0					   								
* Description:		Recursive Binary Tree implementation tests file.		 
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <stddef.h>	/*	size_t						*/
#include <stdio.h>	/*	printf						*/
#include <stdlib.h>	/*	rand, srand					*/
#include <time.h>	/*	time						*/

#include "utils.h"	/*	PRINT_COLOR, COLOR			*/
#include "rbst.h"

/***************************** Macros Definitions *****************************/

/* generates random number from 1 to 100 			*/
#define RANDOM_NUM ((rand() % 100) + 1)	

/**************************** Structs  Definitions ****************************/

typedef struct student
{
	char *name;
	size_t id;
	size_t grade;
}element_ty;

/**************************** Forward Declarations ****************************/
static void RBSTCreateTest();


/******************************************************************************/
/******************************* Main__Function *******************************/

int main()
{
	/*	Intializes a random number generator		*/
	srand(time(0));
	
	return (0);
}

/******************************************************************************/
static void RBSTCreateTest()
{
	
}
/******************************************************************************/


/******************************************************************************/

/*********************************FILE__HEADER*********************************\
* File:				rbst.c						 		  								
* Author:			Daniel Brodsky					  								
* Date:				06-06-2021			   								
* Version:			1.0					   								
* Description:		Recursive Binary Tree implementation tests file.		 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>	/*	assert						*/
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
int CompareGrades(const void *student1, const void *student2, const void *param);

static void RBSTCreateTest(rbst_ty *tree);

static void RBSTDestroyTest(rbst_ty *tree);

/******************************************************************************/
/******************************* Main__Function *******************************/

int main()
{
	/*	creates a binary search tree based on CompareGrades criteria	*/
	rbst_ty *tree = RBSTCreate(CompareGrades, 0);
	
	/*	Intializes a random number generator							*/
	srand(time(0));


	/*	Runs tests														*/
	RBSTCreateTest(tree);
	RBSTDestroyTest(tree);
	
	return (0);
}

/******************************************************************************/
static void RBSTCreateTest(rbst_ty *tree)
{
	tree ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void RBSTDestroyTest(rbst_ty *tree)
{
	RBSTDestroy(tree);
}
/******************************************************************************/
int CompareGrades(const void *student1, const void *student2, const void *param)
{

	int grade1 = -1, grade2 = -1;
	
	assert(student1);
	assert(student2);
	
	grade1 = ((element_ty *)student1)->grade;	
	grade2 = ((element_ty *)student2)->grade;
	
	return (grade1 - grade2);
}
/******************************************************************************/

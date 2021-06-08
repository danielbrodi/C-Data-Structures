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

/* generates random number from 1 to 1000 			*/
#define RANDOM_NUM ((rand() % 1000) + 1)	

/**************************** Structs  Definitions ****************************/

typedef struct student
{
	char *name;
	size_t id;
	size_t grade;
}element_ty;

/**************************** Forward Declarations ****************************/
int CompareGrades(const void *student1, const void *student2, const void *param);

static void RBSTFindTest(const rbst_ty *tree);

static void RBSTCreateTest(rbst_ty *tree);

static void RBSTDestroyTest(rbst_ty *tree);

static void FillUpArray(element_ty *arr, size_t size);

static void RBSTInsertTest(rbst_ty *tree, element_ty *arr, size_t arr_size);

static void PrintArray(element_ty arr[], size_t size);

static void RBSTIsEmptyTest(rbst_ty *tree);

int PrintTree(void *student, void *param);

static void RBSTRemoveTest(rbst_ty *tree);
/******************************************************************************/
/******************************* Main__Function *******************************/

int main()
{
	element_ty students[5] = {0};
	
	/*	creates a binary search tree based on CompareGrades criteria	*/
	rbst_ty *tree = RBSTCreate(CompareGrades, 0);
	
	size_t size = sizeof(students)/sizeof(element_ty);
	
	/*	Intializes a random number generator							*/
	srand(time(0));
	
	FillUpArray(students, size);
	PrintArray(students, size);
	
	/*	Runs tests														*/
	RBSTFindTest(tree);
	RBSTCreateTest(tree);
	RBSTIsEmptyTest(tree);
	RBSTInsertTest(tree, students, size);
	RBSTFindTest(tree);
	RBSTRemoveTest(tree);
	RBSTFindTest(tree);
	
	RBSTDestroyTest(tree);
	
	return (0);
}
/******************************************************************************/
static void RBSTCreateTest(rbst_ty *tree)
{
	tree ? printf(GREEN "Tree was successfuly created.\n\n" RESET_COLOR) :
						printf(RED "Failed to create a tree.\n" RESET_COLOR);
}
/******************************************************************************/
static void RBSTDestroyTest(rbst_ty *tree)
{
	RBSTDestroy(tree);
}
/******************************************************************************/
static void RBSTInsertTest(rbst_ty *tree, element_ty *arr, size_t arr_size)
{
	size_t num_of_elements = arr_size, i = 0;
	int status = 0;
	
	for (i = 0; i < num_of_elements; ++i)
	{
		printf("SIZE OF TREE: %ld, Height: %d\n\n", RBSTSize(tree), RBSTHeight(tree));
		status = RBSTInsert(tree, &arr[i]);
		
		printf("STATUS: %d for student: %s\n", status, arr[i].name);
	}
	printf("SIZE OF TREE: %ld, Height: %d\n\n", RBSTSize(tree), RBSTHeight(tree));
	RBSTForEach(tree, PrintTree, 0);
}
/******************************************************************************/
static void RBSTFindTest(const rbst_ty *tree)
{
	element_ty FindMe = {"", 0, 10};
	element_ty *student = (element_ty *)RBSTFind(tree, &FindMe);
	
	if (student)
	{
	printf("Found! Name: %s, ID: %ld, Grade: %ld\n", student->name, student->id,
																student->grade);	
	}
	else
	{
		printf("NOT FOUND\n");
	}
	
	RBSTIsEmpty(tree) ? printf("TREE IS EMPTY!\n'") : printf("TREE IS NOT EMPTY\n");
}
/******************************************************************************/
static void RBSTIsEmptyTest(rbst_ty *tree)
{
	printf(CYAN "IsEmpty Test: " RESET_COLOR);
	
	RBSTIsEmpty(tree) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void RBSTRemoveTest(rbst_ty *tree)
{
	element_ty RemoveMe0 = {"", 0, 10};
	element_ty RemoveMe1 = {"", 0, 20};
	element_ty RemoveMe2 = {"", 0, 30};
	element_ty RemoveMe3 = {"", 0, 40};
	element_ty RemoveMe4 = {"", 0, 50};
	
	printf(RED "REMOVED 10:\n" RESET_COLOR);
	RBSTRemove(tree, &RemoveMe0);
	printf("SIZE OF TREE: %ld\n\n", RBSTSize(tree));
	
	printf(CYAN "\n\nTREE:\n\n" RESET_COLOR);
	RBSTForEach(tree, PrintTree, 0);
	
	printf(RED "REMOVED 20:\n" RESET_COLOR);
	RBSTRemove(tree, &RemoveMe1);
	printf("SIZE OF TREE: %ld\n\n", RBSTSize(tree));
	
	printf(CYAN "\n\nTREE:\n\n" RESET_COLOR);
	RBSTForEach(tree, PrintTree, 0);
	
	printf(RED "REMOVED 30:\n" RESET_COLOR);
	RBSTRemove(tree, &RemoveMe2);
	printf("SIZE OF TREE: %ld\n\n", RBSTSize(tree));
	
	printf(CYAN "\n\nTREE:\n\n" RESET_COLOR);
	RBSTForEach(tree, PrintTree, 0);
	
	printf(RED "REMOVED 40:\n" RESET_COLOR);
	RBSTRemove(tree, &RemoveMe3);
	printf("SIZE OF TREE: %ld\n\n", RBSTSize(tree));
	
	printf(CYAN "\n\nTREE:\n\n" RESET_COLOR);
	RBSTForEach(tree, PrintTree, 0);
	
	printf(RED "REMOVED 50:\n" RESET_COLOR);
	RBSTRemove(tree, &RemoveMe4);
	printf("SIZE OF TREE: %ld\n\n", RBSTSize(tree));
	
	printf(CYAN "\n\nTREE:\n\n" RESET_COLOR);
	RBSTForEach(tree, PrintTree, 0);
}
/******************************************************************************/
int CompareGrades(const void *student1, const void *student2, const void *param)
{
	int grade1 = -1, grade2 = -1;
	
	(void)param;
	
	assert(student1);
	assert(student2);
	
	grade1 = ((element_ty *)student1)->grade;	
	grade2 = ((element_ty *)student2)->grade;
	
	return (grade1 - grade2);
}
/******************************************************************************/
int PrintTree(void *student, void *param)
{
	int grade = -1;
	
	(void)param;
	
	assert(student);
	
	grade = ((element_ty *)student)->grade;
	
	printf("Name: %s, Grade: %d\n", ((element_ty *)student)->name, grade);
	
	return (0);
}
/******************************************************************************/
static void FillUpArray(element_ty *arr, size_t size) 
{
	size_t i = 0;
	char *names[5] = {"Peter Parker", "Uncle Ben", "Mary Jane", "Aunt May",
																"Harry Osborn"};
	for (i = 0; i < size; ++i)
	{
		arr[i].name = names[i];
		arr[i].id = RANDOM_NUM;
		arr[i].grade = (i+1) * 10;
	}
}
/******************************************************************************/
static void PrintArray(element_ty arr[], size_t size)
{
	size_t i = 0;
		
	printf(GREEN "Students that will be inserted into the tree:\n\n");
	
	for (i = 0; i < size; ++i)
	{
		printf(CYAN "Order: " RESET_COLOR "%ld\n\
				"PURPLE "Name: " RESET_COLOR "%s\n\
				"BLUE "ID: " RESET_COLOR  "%ld\n\
				"YELLOW "Grade: " RESET_COLOR  "%ld\n\
				\n", i+1, arr[i].name, arr[i].id, arr[i].grade);
	}
	
	printf("\n");
}
/******************************************************************************/


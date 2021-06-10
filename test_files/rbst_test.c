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

static void RBSTRemoveTest(rbst_ty *tree, element_ty *arr, size_t arr_size);

int SaveGrades(void *student, void *param);

static void ForEachTest(rbst_ty *tree, size_t arr_size);
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
	RBSTCreateTest(tree);
	RBSTInsertTest(tree, students, size);
	RBSTFindTest(tree);
	ForEachTest(tree, size);
	RBSTRemoveTest(tree, students, size);
	
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
	size_t num_of_elements = arr_size, i = 0, tree_size = 0;
	int is_working_insert = 1, is_working_size = 1;
	
	for (i = 0; i < num_of_elements; ++i)
	{
		is_working_insert *= (RBSTSize(tree) == tree_size);
		if (RBSTInsert(tree, &arr[i]))
		{
			is_working_insert = 0;
			printf(RED "STATUS: FAILED for student: %s\n" RESET_COLOR, arr[i].name);
		}
		++tree_size;
	}
	
	is_working_size *= (RBSTSize(tree) == tree_size);
	
	printf(CYAN "RBST Insert Test: " RESET_COLOR);
	
	is_working_insert ? PRINT_SUCCESS : PRINT_FAILURE;
	
	printf(CYAN "RBST Size Test: " RESET_COLOR);
	
	is_working_size ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void RBSTFindTest(const rbst_ty *tree)
{
	element_ty FindMe = {"", 0, 300};
	element_ty *student = (element_ty *)RBSTFind(tree, &FindMe);
	
	int is_working = 1;
	
	if (student)
	{
/*	printf("Found! Name: %s, ID: %ld, Grade: %ld\n", student->name, student->id,*/
/*																student->grade);*/
	is_working *= (student->grade == FindMe.grade);
		
	}
	else
	{
		is_working = 0;
	}
	
	printf(CYAN "RBST Find Test: " RESET_COLOR);
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void RBSTIsEmptyTest(rbst_ty *tree)
{
	printf(CYAN "RBST IsEmpty Test: " RESET_COLOR);
	
	RBSTIsEmpty(tree) ? PRINT_SUCCESS : PRINT_FAILURE;
}
/******************************************************************************/
static void RBSTRemoveTest(rbst_ty *tree, element_ty *arr, size_t arr_size)
{
	size_t i = 0, num_of_elements = arr_size, is_working = 1, tree_size = 0;
	
	element_ty RemoveMe = {"", 0, 0};
	
	tree_size = RBSTSize(tree);
	
	for (i = 0; i < num_of_elements; ++i)
	{
		RemoveMe.grade = arr[i].grade;
		RBSTRemove(tree, &RemoveMe);;
		--tree_size;
		
		is_working *= (tree_size == RBSTSize(tree));
	}
	
	printf(CYAN "RBST Remove Test: " RESET_COLOR);
	
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
	
	RBSTIsEmptyTest(tree);
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
int SaveGrades(void *student, void *output)
{
	
	static int index = 0;
	
	int grade = -1;
	
	assert(student);
	
	grade = ((element_ty *)student)->grade;
	
	*((int *)output + index) = grade;
	
	++index;
	
	return (0);
}
/******************************************************************************/
static void ForEachTest(rbst_ty *tree, size_t arr_size)
{
	int *grades = (int *)malloc(sizeof(int) * arr_size);
	
	size_t i = 0, is_working = 1;
	
	printf(CYAN "RBST ForEach Test: " RESET_COLOR);
	
	if (!grades)
	{
		PRINT_FAILURE;
	}
	
	RBSTForEach(tree, SaveGrades, grades);
	
	for (i = 1; i < arr_size; ++i)
	{
		is_working *= (grades[i-1] < grades[i]);
	}
		
	is_working ? PRINT_SUCCESS : PRINT_FAILURE;
	
	free(grades);
}
/******************************************************************************/
static void FillUpArray(element_ty *arr, size_t size) 
{
	int i = 0;
	char *names[5] = {"Peter Parker", "Uncle Ben", "Mary Jane", "Aunt May",
														"Harry Osborn"};
	int random_student = rand() % 5;
	for (i = 0; i < (int)size; ++i)
	{
		arr[i].name = names[i];
		arr[i].id = RANDOM_NUM;
		arr[i].grade = (random_student == i)  ? 300 : RANDOM_NUM;
	}
}
/******************************************************************************/
static void PrintArray(element_ty arr[], size_t size)
{
	size_t i = 0;
		
	printf(GREEN "\nStudents that will be inserted into the tree:\n\n");
	
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


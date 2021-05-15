/*********************************FILE__HEADER*********************************\
* File:				bs_tree.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				13/05/2021
* Code Reviewer:	Rostik						   								
* Version:			1.0						   								
* Description:		Binary Search Tree implementation Pseudocode. 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>				/*	assert			*/
#include <stddef.h>				/*	size_t			*/

#include "bs_tree.h"


/*************************** Functions  Pseudocodes ***************************/

typedef int (*Cmp_Func_ty)(const void *data1, const void *data2, 
															const void *param)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


typedef int (*Action_Func_ty)(void *data, void *param)
{
	/*
	
	
	
	*/
}
/******************************************************************************/

bst_ty *BSTCreate(Cmp_Func_ty sorting_func, const void *param)
{
	/*
	
	
	
	*/
}
/******************************************************************************/

void BSTDestroy(bst_ty *bst)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


size_t BSTSize(const bst_ty *bst)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


int BSTIsEmpty(const bst_ty *bst)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


bst_iter_ty BSTInsert(bst_ty *bst, void *data)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterBegin(const bst_ty *bst)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterEnd(const bst_ty *bst)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterPrev(bst_iter_ty iter)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterNext(bst_iter_ty iter)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


int BSTIterIsEqual(bst_iter_ty iter1, bst_iter_ty iter2)
{
	/*
	
	
	
	*/
}
/******************************************************************************/

void *BSTGetData(bst_iter_ty iter)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


bst_iter_ty BSTFind(bst_ty *bst, void *to_find)
{
	/*
	
	
	
	*/
}
/******************************************************************************/


int BSTForEach(bst_iter_ty from_iter, bst_iter_ty to_iter, 
									Action_Func_ty action_func, void *param)
{
	/*
	
	
	
	*/
}
/******************************************************************************/

/*	BST's iterator definition								*/
typedef struct bst_node bst_node_ty;

typedef struct bst_iter
{
	bst_node_ty *node;
	DEBUG_ONLY(size_t version;)
} bst_iter_ty;

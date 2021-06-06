/*********************************FILE__HEADER*********************************\
* File:				rbst.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				06-06-2021
* Code Reviewer:	Kobi
* Pseudo Reviewer: 						   								
* Version:			1.0   								
* Description:		Recursive Binary Tree implementation pseudo-code.
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>			/*	assert			*/
#include <stddef.h>			/*	size_t, NULL	*/
#include <stdlib.h>			/*	malloc, free	*/

#include "rbst.h"

/******************************* Macros & enums *******************************/

/*	from which direction the child node connected to its parent node	*/
typedef enum
{
	LEFT = 0,
	RIGHT = 1
}sides_ty;


/**************************** Structs  Definitions ****************************/

/*	handler struct of each node in a binary search tree					*/
typedef struct rbst_node
{
	rbst_node_ty *children[2];	/*	left and right child nodes	
								 *	left = 0, right = 1					*/
	void *data;					/*	data which is stored in the node	*/	
}rbst_node_ty;

/*	struct handler of a recursive binary search tree					*/
struct rbst
{
	Cmp_Func_ty compare_func;	/*	helps to sort the nodes by
								 *	comparing them by its criteria		*/
	
	/* bst_node_ty root; 			TODO maybe needed 					*/
								/*	a stub that indicates on 
								 *	the root of the tree					*/
								 
	const void *param;			/*	a param which is given by the user	*/
};

/**************************** Forward Declarations ****************************/



/************************* Functions  Implementations *************************/
rbst_ty *RBSTCreate(Cmp_Func_ty cmp_func, const void *param)
{
	/*assert cmp_func because a binary tree without a cmp func is meaningless*/

	/*allocate memory for tree's struct handler, handle errors if any*/

	/*assign received param to tree's param*/
	/*assign cmp_func to tree's cmp_func*/

	/*return the created tree*/
}
/******************************************************************************/
void RBSTDestroy(rbst_ty *rbst)
{
	/*assert*/

/*	RBSTDestroyNodesIMP(rbst_node->root)*/
/*	*/
/*	memset to 0 / nullify tree's struct ptrs*/
	
	/*if tree is empty:*/
		/*free tree*/
}

/*static void RBSTDestroyNodesIMP(rbst_node_ty *node)*/
/*{*/
/*	if node is null:*/
/*		return;*/
/*			*/
/*	RBSTDestroyNodesIMP(node->left);*/
/*	RBSTDestroyNodesIMP(node->right);*/
/*	*/
/*	if node is a leaf:*/
/*		free node*/
}
/******************************************************************************/
void RBSTRemove(rbst_ty *rbst, const void *data)
{
	/*asserts*/
	
	/* #CASE A#: */
	/*if data was found inside :*/
	
		/*#CASE A.1#*/
		/* if node has no children nodes: 
										- free node
										- return 						*/
		
		/*#CASE A.2#*/
		/* if node has only left child:
										- copy child's data into node
										- link child's childring to node
										- free child node				*/
		
		/* if node has only right child:
										- copy successor's data into node
										- if successor has right child:
												- set the left child of
													node's right child as
													successor's right child.
										- free successor				*/
										
		/*#CASE A.3#*/
		/* if node has 2 child nodes:
										- copy successor's data into node
										- determine the side of the successor 
											as a child node by scanning the
											tree for its parent.
										- make successor's parent to point to
											successor's right subtree.
										- free successor.				*/
	/* end CASE A */
	
	/* CASE B: */
	/*if node with the same data wasn't found*/
		/*do nothing: return*/
	/* end CASE B	*/
	
	/*pre order remove:*/
	/*remove(root)*/

	/*if tree's cmp_func shows that data is on the left sub tree:*/
		/*remove(root->left)*/
	/*else*/
		/*remove(root->right)*/
	
}
/******************************************************************************/
int RBSTInsert(rbst_ty *rbst, void *data)
{
	/*if tree is empty or node is null:*/
		/*create and insert a node with the received data from the user*/

	/*in order insert:*/
		/*insert(rbst->root)*/

	/*if tree's cmp_func shows that data is on the left sub tree:*/
		/*insert(root->left)*/
	/*else*/
		/*insert(root->right)*/
}
/******************************************************************************/
size_t RBSTHeight(const rbst_ty *rbst)
{
/*	asserts*/
/*	*/
/*	return RBSTHeightIMP(root);*/
}

static size_t RBSTHeightIMP(rbst_node_ty *node)
{
/*	Base case: node has no children */
    if (node has no children)
        return (0);
 
/*	recur for left and right subtree and find longest path from root to the deepest nodedepth */

    /* return 1 + max(RBSTHeightIMP(node->left), height(node->right)); */

}
/******************************************************************************/
size_t RBSTSize(const rbst_ty *rbst)
{
	/*if tree is empty:*/
		/*return 0*/

	/*scan left subtree and return its size*/
	/*add one because of the root*/
	/*scan right subtree and add its size*/
	
	/*return the sum of the sizes*/
}
/******************************************************************************/
int RBSTIsEmpty(const rbst_ty *rbst)
{
	/*	return boolean if root of the tree is null	*/
}
/******************************************************************************/
void *RBSTFind(const rbst_ty *rbst, const void *data_to_find)
{
	/*in order search:*/
		/*return RBSTFindDataIMP(root, data_to_find)*/
}

static rbst_node_ty *RBSTFindDataIMP(rbst_node_ty *node, const void *data_to_find)
{	
/*	if (node's data equals data to find):*/
/*		return node.*/
/*	*/
/*	if node is null*/
/*		return null*/

	/*if tree's cmp_func shows that data is on the left sub tree:*/
		/*RBSTFindDataIMP(node->left)*/
	/*else*/
		/*RBSTFindDataIMP(node->right)*/
}
/******************************************************************************/
int RBSTForEach(rbst_ty *rbst, Action_Func_ty action_func, void *param)
{
/*	assert*/
/* set counter to 0	*/
/*	return RBSTForEachIMP(root, action_func, param, &counter);*/
}

static int RBSTForEachIMP(rbst_node_ty *node, Action_Func_ty action_func, void *param, size_t *counter)
{
/*	IN ORDER:*/
/*	*/
/*	if(node->left && !counter)*/
/*        RBSTForEachIMP(node->left, action_func, param, counter);*/

/*    if(action_func && !counter)*/
/*        *counter += action_func(nodes data, param);*/

/*   if(node->right && !counter)*/
/*        RBSTForEachIMP(node->left, action_func, param, counter);*/
/*        */
/*	return(*counter);*/
}
/******************************************************************************/

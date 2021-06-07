/*********************************FILE__HEADER*********************************\
* File:				rbst.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				06-06-2021
* Code Reviewer:	Kobi
* Pseudo Reviewer:	Eran						   								
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

/*	status indication of a finished operation							*/
enum
{
	SUCCESS = 0
};

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
	
	rbst_node_ty *root;			/*	first node & the root of the tree	*/ 
								 
	const void *param;			/*	a param which is given by the user	*/
};

/*	return type for a potential location of a node						*/
typedef struct rbst_location
{
	rbst_node_ty *parent;		/*	parent node of the found location	*/
	sides_ty direction;			/*	0 if its the left child,
								 *	1 if its the right child			*/		
} rbst_location_ty;
/**************************** Forward Declarations ****************************/

static rbst_location_ty SearchLocationIMP(bst_ty *bst, void *data);

/************************* Functions  Implementations *************************/
rbst_ty *RBSTCreate(Cmp_Func_ty cmp_func, const void *param)
{
	rbst_ty *new_tree = NULL;
	
	/*	assert cmp_func: a binary tree without a cmp func is meaningless	*/
	assert(cmp_func);
	
	/*	allocate memory for tree's struct handler, handle errors if any		*/
	new_tree = (rbst_ty *)malloc(rbst_ty);
	if (!new_tree)
	{
		return (NULL);
	}
	
	/*	set the received `cmp_func` as the comparing func of the tree.		*/
	new_tree->compare_func = cmp_func;
	
	/*	set the received `param` as the param of the tree.					*/
	new_tree->param = param;
	
	/*	return a pointer to the created tree.								*/
	return (new_tree);
}
/******************************************************************************/
void RBSTDestroy(rbst_ty *rbst)
{
	assert(rbst);

	/*	DestroyNodesIMP(root)*/
	DestroyNodesIMP(rbst->root)
	
	/*	memset to 0 / nullify tree's struct ptrs*/
	rbst->root = NULL;
	rbst->cmp_func = NULL;
	rbst->param = NULL;
	
	/*free tree handler*/
	free(rbst);
	rbst = NULL;
}
/*----------------------------------------------------------------------------*/
static void DestroyNodesIMP(rbst_node_ty *node)
{
	/*	if node is null: return 								*/
	if (!node)
	{
		return;
	}
	
	/*	recursivly scan the left subtree and destroy it			*/
	DestroyNodesIMP(node->children[LEFT]);
	/*	recursivly scan the right subtree and destroy it		*/
	DestroyNodesIMP(node->children[RIGHT]);
	
	/*	if node is a leaf: free node							*/
	if (!node->children[RIGHT] && !node->children[LEFT])
	{
		free(node);
	}
}
/******************************************************************************/
void RBSTRemove(rbst_ty *rbst, const void *data)
{
	/*asserts*/
	

/*	use findIMP func to receive node with the needed data if exists*/
/* TODO create FindIMP(could return both succ and parent), FindSucc, FindParent */

	/* CASE A: */
	/*if node with the same data wasn't found*/
		/*do nothing: return*/
	/* end CASE A	*/

	/* #CASE B#: */
	/*if data was found inside :*/
	
		/*#CASE B.1#*/
		/* if node has no children nodes: 
										- free node
										- return 						*/
		
		/*#CASE B.2#*/
		/* if node has only left child:
										- copy child's data into node
										- link child's children to node
										- free child node				*/
		
		/* if node has only right child:
										- copy successor's data into node
										- if successor has right child:
											- make successor's parent to 
												point to successor's right
												 subtree.
										- free successor				*/
										
		/*#CASE B.3#*/
		/* if node has 2 child nodes:
										- copy successor's data into node
										- determine the side of the successor 
											as a child node by scanning the
											tree for its parent.
										- make successor's parent to point to
											successor's right subtree.
										- free successor.				*/
	/* end CASE B */
}
/******************************************************************************/
int RBSTInsert(rbst_ty *rbst, void *data)
{
	/*if tree is empty or node is null:*/
		/*create and insert a node with the received data from the user*/
		/*set root as created node */

/*	find potential place for the received data by using the FindIMP func*/
/*	*/
/*	if found return error*/
/*	else: create node -> set data -> determine side of child from parent and set
	its																	*/
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
/*    if (node has no children)*/
/*        return (0);*/
 
/*	recur for left and right subtree and find longest path from root to the deepest nodedepth */

    /* return 1 + max(RBSTHeightIMP(node->left), height(node->right)); */
    /* TODO make max macro/func											*/

}
/******************************************************************************/
size_t RBSTSize(const rbst_ty *rbst)
{
	/*if tree is empty:*/
		/*return 0*/

/*	return SizeIMP(root)*/
}

size_t RBSTSizeIMP(rbst_node_ty *root)
{

/*	if node is null*/
/*	return 0;*/

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
	rbst_node_ty *found_location = NULL;
	
	rbst_location_ty potential_location = {0};
	
	assert(rbst);
	assert(data_to_find);
	
	/*	search for a potential location of a node with the given data		*/
	potential_location = SearchLocationIMP(rbst, rbst->root, data_to_find);
	
	/*	If a node with a matching key was found, return its data.
	 *	Otherwise, return NULL 	*/
	found_location = 
			potential_location.parent->children[potential_location.direction];
	if (!found_location)
	{
		return (NULL);
	}
	
	return (found_location->data);
}

static rbst_location_ty SearchLocationIMP(rbst_ty *rbst, rbst_node_ty *node, 
															const void *data);
{
	if (!node)
	{
		return 
	}
/*	if (node's data equals data to find):*/
/*		return node.*/
/*	*/
/*	if node is null*/
/*		return null*/

	/*RBSTFindDataIMP(node->children[result of the cmp func])*/
/*	TODO create location struct*/
}
/******************************************************************************/
int RBSTForEach(rbst_ty *rbst, Action_Func_ty action_func, void *param)
{
	/*	assert*/

	/*	return RBSTForEachIMP(root, action_func, param);*/
}

static int RBSTForEachIMP(rbst_node_ty *node, Action_Func_ty action_func,
																void *param)
{
/*	IN ORDER:*/
/*	*/

/*	if node is null*/
/*		return 0*/


/*        if (RBSTForEachIMP(node->left, action_func, param))
				return 1;							*/

	/*	if action_func(nodes data, param)			*/
/*		return 1									*/

/*        return (RBSTForEachIMP(node->right, action_func, param));	*/
}
/******************************************************************************/

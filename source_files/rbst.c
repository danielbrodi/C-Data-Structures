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

#define MAX(a,b) (((a)>(b))?(a):(b))

/*	from which direction the child node connected to its parent node	*/
typedef enum
{
	LEFT = 0,
	RIGHT = 1
}sides_ty;

/*	status indication of a finished operation							*/
enum
{
	SUCCESS = 0,
	FAILURE = 1
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

static void DestroyNodesIMP(rbst_node_ty *node);

static rbst_node_ty *CreateNodeIMP(void *data);

static int InsertNewNodeIMP(rbst_ty *rbst, rbst_node_ty *node, void *data);

static size_t CalcTreeHeightIMP(rbst_node_ty *root);

size_t GetTreeSizeIMP(rbst_node_ty *root);
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
	rbst_location_ty found_location = {0};
	
	rbst_node_ty *found_node = NULL;
	
	assert(rbst);
	assert(data);

	/*	use searching func to receive node with the needed data if exists	*/
	found_location = SearchLocationIMP(rbst, rbst->root, data);
	
	/*	if a node with a matching data was not found: do nothing			*/
	found_node = found_location.parent->children[found_location.direction];
	if (!found_node)
	{
		return;
	}

	/*#CASE 1#*/
	/* if node has no children nodes: 										*/
	/* TODO maybe create a func that check if leaf & frees the node			*/
	if (!node->children[RIGHT] && !node->children[LEFT])
	{
		/* free node and return											*/							
		free(node);
		return;
	}
	
	/*#CASE 2#*/
	/*	if node has only one child node 									*/
	else if (!node->children[LEFT] || !node->children[RIGHT])
	{
	
		/* 	if node has only right child:								*/
		if (node->children[RIGHT])
		{
			/*
			- copy successor's data into node
			- if successor has right child:
			- make successor's parent to 
				point to successor's right
				subtree.
			- free successor									
			*/
		}
		
		/* 	if node has only left child:								*/
		else
		{
			/*
			- copy child's data into node
			- link child's children to node
			- free child node
			*/
			node->parent->children[child_side] = node->children[LEFT];
			node->children[LEFT]->parent = node->parent;
		}

		/* free the node which was found								*/
		free(node);
		node = NULL;
	}
	
	/*#CASE 3#*/
	/*	if node has 2 subtrees												*/
	else
	{
		/*
		- copy successor's data into node
		- determine the side of the successor 
			as a child node by scanning the
			tree for its parent.
		- make successor's parent to point to
			successor's right subtree.
		- free successor.
		*/
	}
	
	return (successor);
	
}
/******************************************************************************/
int RBSTInsert(rbst_ty *rbst, void *data)
{
	rbst_node_ty *new_node = NULL;
	
	rbst_location_ty potential_location = {0};
	
	assert(rbst);
	assert(data); /*	NULL data isn't accepted in this tree				*/
	
	/*	create a node with the received data								*/
	/*	handle memory allocation errors if any								*/
	new_node = CreateNodeIMP(data);
	if (!new_node)
	{
		return (FAILURE);
	}
	
	/*	if tree is empty													*/
	if (RBSTIsEmpty(rbst))
	{
		/*	set the root of the tree as the created node 	*/
		rbst->root = new_node;
		
		return (SUCCESS);	
	}
	
	/*	if tree is not empty and a new node should be inserted:				*/
	/*	find a potential place for the node by using a location finder func	*/
	potential_location = SearchLocationIMP(rbst, rbst->root, data);
	
	/*	if the location which was returned points to an exsiting node
	 *	it means there is already a node with that data -> crash.			*/
	 assert(!potential_location.parent->children[potential_location.direction]);
	 
	/*	if a valid location to insert node was returned:					*/
	/*	create node -> set data -> set correcly its parent child ptr		*/
	found_location.parent->children[found_location.direction] = new_node;
	
	return(SUCCESS)
}												
/*----------------------------------------------------------------------------*/
static rbst_node_ty *CreateNodeIMP(void *data)
{
	rbst_node_ty *new_node = NULL;
	
	assert(data); /*	NULL data isn't accepted in this tree			*/
	
	/*	creates a new node with the received data						*/
    /* 	allocates memory, checks for allocation errors					*/
	new_node = (rbst_node_ty *)malloc(sizeof(rbst_node_ty));
	if (new_node)
	{
		/*	set data as data 											*/
		/* 	set children pointers as null								*/
		new_node->data = data;
		new_node->children[LEFT] = new_node->children[RIGHT] = NULL;
    }
    
    return (new_node);
}
/******************************************************************************/
size_t RBSTHeight(const rbst_ty *rbst)
{
	assert(rbst);
	
	return (CalcTreeHeightIMP(rbst->root));
}

static size_t CalcTreeHeightIMP(rbst_node_ty *node)
{
	/*	Base case: node has no children 								*/
	/*	if (node has no children) : return 0 							*/
	if (!node->children[RIGHT] && !node->children[LEFT]);
	{
		return (0);
	}s

	/*	recursively traverse the left and right subtrees and find the 
	 *	longest path from root to the deepest node depth 				*/
	return (1 + MAX(CalcTreeHeightIMP(node->left), 
											CalcTreeHeightIMP(node->right))); 
}
/******************************************************************************/
size_t RBSTSize(const rbst_ty *rbst)
{
	assert(rbst);
	
	return (GetTreeSizeIMP(rbst->root));
}
/*----------------------------------------------------------------------------*/
size_t GetTreeSizeIMP(rbst_node_ty *node)
{
	/*	if node doesn't exist, don't count the its  edge				*/
	if (!node)
	{
		return (0);
	}
	
	/*	if node is a leaf, count the edge which connects to it			*/
	if (!node->children[RIGHT] && !node->children[LEFT])
	{
		return (1);
	}

	/*	scan left subtree and return its size							*/
	/*	add one because of the root										*/
	/*	scan right subtree and add its size								*/
	/*	return the sum of the sizes										*/
	return (1 + GetTreeSizeIMP(node->children[LEFT]) + 
				GetTreeSizeIMP(node->children[RIGHT]));
}
/******************************************************************************/
int RBSTIsEmpty(const rbst_ty *rbst)
{
	assert(rbst);
	
	/*	return boolean if root of the tree is null	*/
	return (NULL == rbst->root);
}
/******************************************************************************/
void *RBSTFind(const rbst_ty *rbst, const void *data_to_find)
{
	rbst_node_ty *found_node = NULL;
	
	rbst_location_ty potential_location = {0};
	
	assert(rbst);
	assert(data_to_find);
	
	/*	search for a potential location of a node with the given data		*/
	potential_location = SearchLocationIMP(rbst, rbst->root, data_to_find);
	
	/*	If a node with a matching key was found, return its data.
	 *	Otherwise, return NULL 	*/
	found_node = 
			potential_location.parent->children[potential_location.direction];
		
	if (!found_node)
	{
		return (NULL);
	}
	
	return (found_node->data);
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

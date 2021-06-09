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

/******************************* macros & enums *******************************/

/*	returns the bigger value between 2 given values							*/
#define MAX(a,b) (((a)>(b))?(a):(b))

/*	from which direction the child node connected to its parent node		*/
typedef enum
{
	LEFT = 0,
	RIGHT = 1
}sides_ty;

/*	status indication of a finished operation								*/
enum
{
	SUCCESS = 0,
	FAILURE = 1
};

/**************************** Structs  Definitions ****************************/

typedef struct rbst_node rbst_node_ty;

/*	struct handler of each node in a binary search tree						*/
struct rbst_node
{
	rbst_node_ty *children[2];	/*	left and right child nodes	
								 *	left = 0, right = 1						*/
	void *data;					/*	data which is stored in the node		*/	
};

/*	struct handler of a recursive binary search tree						*/
struct rbst
{
	Cmp_Func_ty compare_func;	/*	helps to sort the nodes by
								 *	comparing them by its criteria			*/
	
	rbst_node_ty *root;			/*	first node and the root of the tree		*/
								/*	will point to NULL when tree is empty	*/
								 
	const void *param;			/*	a param which is given by the user		*/
};

/*	return type for a potential location of a node							*/
typedef struct rbst_location
{
	rbst_node_ty *parent;		/*	parent node of the found location		*/
	sides_ty direction;			/*	0 if its the left child,
								 *	1 if its the right child				*/		
} rbst_location_ty;
/**************************** Forward Declarations ****************************/

static rbst_location_ty SearchLocationIMP(const rbst_ty *rbst, rbst_node_ty *node, 
															const void *data);
															
static void DestroyNodesIMP(rbst_node_ty *node);

static rbst_node_ty *CreateNodeIMP(void *data);

static int CalcTreeHeightIMP(rbst_node_ty *root);

size_t GetTreeSizeIMP(rbst_node_ty *root);

static int IsALeafIMP(rbst_node_ty *node);

static int IsARootIMP(const rbst_ty *rbst, const void *data);

/*	traverse down from a node to find the leftmost or the rightmost node	*/
static rbst_location_ty GetSideMostIMP(rbst_node_ty *node, sides_ty side);

static int RunOperationOnTreeIMP(rbst_node_ty *node, Action_Func_ty action_func,
																void *param);														
/************************* Functions  Implementations *************************/
rbst_ty *RBSTCreate(Cmp_Func_ty cmp_func, const void *param)
{
	rbst_ty *new_tree = NULL;
	
	/*	assert cmp_func: a binary tree without a cmp func is meaningless	*/
	assert(cmp_func);
	
	/*	allocate memory for tree's struct handler, handle errors if any		*/
	new_tree = (rbst_ty *)malloc(sizeof(rbst_ty));
	if (!new_tree)
	{
		return (NULL);
	}
	
	/*	set the root of the tree as null because there is no root yet		*/
	new_tree->root = NULL;
	
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
	
	/*	assure that there are nodes to free in the tree						*/
	if (!RBSTIsEmpty(rbst))
	{
		/*	DestroyNodesIMP(root)											*/
		DestroyNodesIMP(rbst->root);
	}
	
	/*	nullify tree's struct ptrs											*/
	rbst->root = NULL;
	rbst->compare_func = NULL;
	rbst->param = NULL;
	
	/*	free tree handler													*/
	free(rbst);
	rbst = NULL;
}
/*----------------------------------------------------------------------------*/
static void DestroyNodesIMP(rbst_node_ty *node)
{
	/*	if node is null: return 											*/
	if (!node)
	{
		return;
	}
	
	/*	recursivly scan the left subtree and destroy it						*/
	DestroyNodesIMP(node->children[LEFT]);
	/*	recursivly scan the right subtree and destroy it					*/
	DestroyNodesIMP(node->children[RIGHT]);
	
	/*	free reached node because its a leaf								*/
		free(node);
}
/******************************************************************************/
void RBSTRemove(rbst_ty *rbst, const void *data)
{
	rbst_location_ty found_location = {0};
	
	rbst_node_ty *node_to_remove, *successor = NULL, *successor_parent = NULL;
	
	assert(rbst);
	assert(data);
	
	/*	if the data which needs to be removed is located in the root:		*/
	if (IsARootIMP(rbst, data))
	{
		node_to_remove = rbst->root;
		/*	set one of its childs' nodes as the new root of the tree		*/
		rbst->root = node_to_remove->children[RIGHT] ? 
			node_to_remove->children[RIGHT] : node_to_remove->children[LEFT];
		/*	free the node which used to be the root							*/
		free(node_to_remove);
		
		return;
	}
	
	/*	use searching func to receive node with the needed data if exists	*/
	/*	it also finds node's parent											*/
	found_location = SearchLocationIMP(rbst, rbst->root, data);
	
	/*	if a node with a matching data was not found: do nothing			*/
	node_to_remove = found_location.parent->children[found_location.direction];
	if (!node_to_remove)
	{
		return;
	}

	/*#CASE 1#*/
	/* if node has no children nodes: 										*/
	if (IsALeafIMP(node_to_remove))
	{
		/* free node														*/							
		free(node_to_remove);
	}
	
	/*#CASE 2#*/
	/*	if node has only one child node: 									*/											
	else if (!node_to_remove->children[LEFT] || !node_to_remove->children[RIGHT])
	{
	
		/* 	if node has only right child, link it to node's parent			*/
		if (node_to_remove->children[RIGHT])
		{
			found_location.parent->children[found_location.direction] = 
												node_to_remove->children[RIGHT];		
		}
		
		/* 	if node has only left child, link it to node's parent			*/
		else
		{
			found_location.parent->children[found_location.direction] = 
												node_to_remove->children[LEFT];
		}

		/* free the node which was found									*/
		free(node_to_remove);
	}
	
	/*#CASE 3#*/
	/*	if node has 2 subtrees												*/
	else
	{
		/*	find the successor's parent										*/
		/*	a successor of a node is the leftmost node of its right child	*/
		successor_parent = 
				GetSideMostIMP(node_to_remove->children[RIGHT], LEFT).parent;
		/*	check if the successor is the right child or the leftmost node	*/
		if (successor_parent)
		{
			successor = successor_parent->children[LEFT];
			/*	link successor's parent to successor's right subtree	*/
			successor_parent->children[LEFT] = successor->children[RIGHT];
		}
		/*	if the successor is the right child of node_to_remove			*/
		else
		{
			successor = node_to_remove->children[RIGHT];
			/*	link node_to_remove's right subtree 
			 *	to successor's right subtree							*/
			node_to_remove->children[RIGHT] = successor->children[RIGHT];
		}
		
		/*  copy successor's data into node									*/
		node_to_remove->data = successor->data;
		/*	free successor's node											*/
		free(successor);
	}
	
	return;
}
/*----------------------------------------------------------------------------*/
/*	traverse down from a node to find the leftmost or the rightmost node	*/
static rbst_location_ty GetSideMostIMP(rbst_node_ty *node, sides_ty side)
{
	rbst_location_ty found_location = {0};
	
	assert(node);
	assert(RIGHT == side || LEFT == side);
	
	/*	if no subtree in this direction even exists							*/
	if (!node->children[side])
	{
		return (found_location);
	}
	
	/*	while node's child on the received side exists:						*/
	/*	save node as parent and go to that child.							*/
	if (!node->children[side]->children[side])
	{
		found_location.parent = node;
		found_location.direction = side;
		return (found_location);
	}
	
	return (GetSideMostIMP(node->children[side], side));
}
/******************************************************************************/
int RBSTInsert(rbst_ty *rbst, void *data)
{
	rbst_node_ty *new_node = NULL;
	
	rbst_location_ty found_location = {0};
	
	assert(rbst);
	assert(data); /*	NULL data isn't accepted in this tree				*/
	
	/* assure that the data which needs to be inserted is not in the root	*/
	assert(!IsARootIMP(rbst, data));
	
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
		/*	set the root of the tree as the created node 			*/
		rbst->root = new_node;
		
		return (SUCCESS);	
	}
	
	/*	if tree is not empty and a new node should be inserted:				*/
	/*	find a potential place for the node by using a location finder func	*/
	found_location = SearchLocationIMP(rbst, rbst->root, data);
	
	/*	if the location which was returned points to an exsiting node
	 *	it means there is already a node with that data -> crash.			*/
	 assert(!found_location.parent->children[found_location.direction]);
	 
	/*	if a valid location to insert node was returned:					*/
	/*	create node -> set data -> set correcly its parent child ptr		*/
	found_location.parent->children[found_location.direction] = new_node;
	
	return(SUCCESS);
}												
/*----------------------------------------------------------------------------*/
static rbst_node_ty *CreateNodeIMP(void *data)
{
	rbst_node_ty *new_node = NULL;
	
	assert(data); /*	NULL data isn't accepted in this tree				*/
	
	/*	creates a new node with the received data							*/
    /* 	allocates memory, checks for allocation errors						*/
	new_node = (rbst_node_ty *)malloc(sizeof(rbst_node_ty));
	if (new_node)
	{
		/*	set data as data 										*/
		/* 	set children pointers as null							*/
		new_node->data = data;
		new_node->children[LEFT] = new_node->children[RIGHT] = NULL;
    }
    
    return (new_node);
}
/******************************************************************************/
int RBSTHeight(const rbst_ty *rbst)
{	
	assert(rbst);
	
	return (CalcTreeHeightIMP(rbst->root));
}
/*----------------------------------------------------------------------------*/
static int CalcTreeHeightIMP(rbst_node_ty *node)
{
	/*	if node does not exist, return (-1)									*/
	if (!node)
	{
		return (-1);
	}
	
	/*	recursively traverse the left and right subtrees and find the 
	 *	longest path from root to the deepest node depth 					*/
	return (1 + MAX(CalcTreeHeightIMP(node->children[LEFT]), 
									CalcTreeHeightIMP(node->children[RIGHT]))); 
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
	/*	if node doesn't exist, don't count the its  edge					*/
	if (!node)
	{
		return (0);
	}
	
	/*	if node is a leaf, count the edge which connects to it				*/
	if (IsALeafIMP(node))
	{
		return (1);
	}

	/*	scan left subtree and return its size								*/
	/*	add one because of the root											*/
	/*	scan right subtree and add its size									*/
	/*	return the sum of the sizes											*/
	return (1 + GetTreeSizeIMP(node->children[LEFT]) + 
				GetTreeSizeIMP(node->children[RIGHT]));
}
/******************************************************************************/
int RBSTIsEmpty(const rbst_ty *rbst)
{
	assert(rbst);
	
	/*	return boolean if root of the tree is null							*/
	return (!rbst->root);
}
/******************************************************************************/
void *RBSTFind(const rbst_ty *rbst, const void *data_to_find)
{
	rbst_node_ty *found_node = NULL;
	
	rbst_location_ty potential_location = {0};
	
	assert(rbst);
	assert(data_to_find);
	
	/* check if the data which is searched is in the root					*/
	if (IsARootIMP(rbst, data_to_find))
	{
		return (rbst->root->data);	
	}
	
	/*	search for a potential location of a node with the given data		*/
	potential_location = SearchLocationIMP(rbst, rbst->root, data_to_find);
	
	if (potential_location.parent)
	{
		/*	If a node with a matching key was found, return its data.
		 *	Otherwise, return NULL 									*/
		found_node = 
				potential_location.parent->children[potential_location.direction];
	}
	
	return (found_node ? found_node->data : NULL);
}
/*----------------------------------------------------------------------------*/
static rbst_location_ty SearchLocationIMP(const rbst_ty *rbst, rbst_node_ty *node, 
															const void *data)
{
	rbst_location_ty potential_location = {0};
	sides_ty direction_to_go = 0;
	
	assert(rbst);
	assert(data);
	
	if (!node)
	{
		return (potential_location);
	}
		
	/*	determine which direction to go based on the result of cmp_func		*/
	direction_to_go = rbst->compare_func(node->data, data, rbst->param) < 0;
	
	/*	if node doesn't exist or if a node with the needed data was found	*/
	if (!node->children[direction_to_go] ||
		!rbst->compare_func(
					node->children[direction_to_go]->data, data, rbst->param))
	{
		potential_location.parent = node;
		potential_location.direction = direction_to_go;
				
		return (potential_location);
	}
	
	/*	recursively traverse through the tree nodes based on the cmp_func	*/
	return (SearchLocationIMP(rbst, node->children[direction_to_go], data));
}
/******************************************************************************/
int RBSTForEach(rbst_ty *rbst, Action_Func_ty action_func, void *param)
{
	assert(rbst);
	assert(action_func);

	return (RunOperationOnTreeIMP(rbst->root, action_func, param));
}
/*----------------------------------------------------------------------------*/
static int RunOperationOnTreeIMP(rbst_node_ty *node, Action_Func_ty action_func,
																void *param)
{
	/*	if node is null*/
	/*		return 0*/
	if (!node)
	{
		return (SUCCESS);
	}
	
	/*	check if any operation failure occured while traversing the 
	 *	left subtree.
	 *	Returns FAILURE on the first failed attemp.							*/
	if	(RunOperationOnTreeIMP(node->children[LEFT], action_func, param))
	{
		return (FAILURE);
	}						
	
	/*	Returns FAILURE if any operation failure occured while applying
	 *	it to a given node.													*/
	if (action_func(node->data, param))		
	{
		return (FAILURE);
	}									
	
	/*	Traverse the right subtree and apply the operation function to
	 *	each of its nodes													*/
	return (RunOperationOnTreeIMP(node->children[RIGHT], action_func, param));
}
/******************************************************************************/
static int IsALeafIMP(rbst_node_ty *node)
{
	assert(node);
	
	/*	check whether the node has any children								*/
	return (!node->children[RIGHT] && !node->children[LEFT]);
}
/******************************************************************************/
static int IsARootIMP(const rbst_ty *rbst, const void *data)
{	
	if (rbst->root)
	{
		/* check if the given data is located in the root node		*/
		return (!rbst->compare_func(rbst->root->data, data, rbst->param));
	}
	
	return (0);
}
/******************************************************************************/

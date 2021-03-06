/*********************************FILE__HEADER*********************************\
* File:				rbst.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				06-06-2021
* Code Reviewers:	Evald, Kobi
* Pseudo Reviewer:	Eran						   								
* Version:			2.0							
* Description:		Recursive Binary Tree implementation.
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>			/*	assert			*/
#include <stddef.h>			/*	size_t, NULL	*/
#include <stdlib.h>			/*	malloc, free	*/

#include "rbst.h"

/******************************* macros & enums *******************************/

/* DEAD_MEM will be used to define the stub of the tree 					*/
#define DEAD_MEM(type) ((type)0xdeadbeef)

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

/*	struct handler of each node in a binary search tree						*/
typedef struct rbst_node
{
	struct rbst_node *children[2];	/*	left and right child nodes:	
								 	 *	left = 0, right = 1					*/
	void *data;						/*	data which is stored in the node	*/	
}rbst_node_ty;

/*	struct handler of a recursive binary search tree						*/
struct rbst
{
	Cmp_Func_ty compare_func;	/*	helps to sort the nodes by
								 *	comparing them by its criteria			*/
	
	rbst_node_ty stub;			/*	its left child is the root of the tree	*/
								 
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

/* 	recursively searches for the right location in the tree for a given data:
 *	Returns the parent and the direction from it to that found location.
 *	The found location may be NULL if no node with the matching data
 	has been found in the tree												*/
static rbst_location_ty SearchLocationIMP(const rbst_ty *rbst, rbst_node_ty *node, 
															const void *data);
/*	recursively traverses through tree, in a post order way,
 *	and frees every node.													*/												
static void DestroyNodesIMP(rbst_node_ty *node);

/*	creates a new node with the received data.								*/
static rbst_node_ty *CreateNodeIMP(void *data);

/*	recursively traverses the left and right subtrees and finds the 
 *	longest path from the root to the deepest node. 					
 	Returns the longest path between the two.								*/
static int CalcTreeHeightIMP(rbst_node_ty *root);

/*	recursively traverses the tree and counts each node.
 *	Returns the final count.												*/
static size_t GetTreeSizeIMP(rbst_node_ty *root);

/*	checks whether a given node has any children							*/
static int IsALeafIMP(rbst_node_ty *node);

/* check if the given node is the stub of the tree							*/
static int IsAStubIMP(rbst_node_ty *node);

/*	recursively traverses down from a node to find the
 *	leftmost or the rightmost node											*/
static rbst_location_ty GetSideMostIMP(rbst_node_ty *node, sides_ty side);

/*	traverses both subtrees and applys a given operation function to
 *	each the nodes. Returns 0 if succeeded and 1 otherwise. 				*/
static int RunOperationOnTreeIMP(rbst_node_ty *node, Action_Func_ty action_func,
																void *param);

/*	removes a leaf node from the tree 										*/
static void RemoveLeaf(rbst_node_ty *node, rbst_location_ty node_location);							

/*	removes a node with one subtree from the tree							*/
static void RemoveNodeWithOneSubTree(rbst_node_ty *node,
rbst_location_ty node_location);

/*	removes a node with two subtrees from the tree 							*/
static void RemoveNodeWithTwoSubTrees(rbst_node_ty *node);

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
	
	/*	Initialize tree's stub data and right child as DEAD_MEM.			*/
	/*	Initialize stub's left child pointer as null.						*/
	new_tree->stub.data = DEAD_MEM(void *);
	new_tree->stub.children[RIGHT] = DEAD_MEM(rbst_node_ty *);
	new_tree->stub.children[LEFT] = NULL;
	
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
	if (rbst)
	{
	
		/*	assure that there are nodes to free in the tree					*/
		if (!RBSTIsEmpty(rbst))
		{
			/*	DestroyNodesIMP(root)										*/
			DestroyNodesIMP(rbst->stub.children[LEFT]);
		}
		
		/*	nullify tree's struct ptrs										*/
		rbst->stub.children[RIGHT] = rbst->stub.children[LEFT] = NULL;
		rbst->stub.data = NULL;
		rbst->compare_func = NULL;
		rbst->param = NULL;
		
		/*	free tree handler												*/
		free(rbst);
	}
}
/*----------------------------------------------------------------------------*/
static void DestroyNodesIMP(rbst_node_ty *node)
{
	/*	not removing the stub of the tree									*/
	if (IsAStubIMP(node))
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
	
	rbst_node_ty *node_to_remove = NULL;
	
	assert(rbst);
	assert(data);
	
	/*	use searching func to receive node with the needed data if exists	*/
	/*	it also finds node's parent											*/
	found_location = SearchLocationIMP(rbst, &rbst->stub, data);
	
	node_to_remove = found_location.parent->children[found_location.direction];
	
	/*	if a node with a matching data was not found: do nothing			*/
	if (!node_to_remove)
	{
		return;
	}

	/*#CASE 1#*/
	/* if node has no children nodes: 										*/
	if (IsALeafIMP(node_to_remove))
	{
		RemoveLeaf(node_to_remove, found_location);
	}
	
	/*#CASE 2#*/
	/*	if node has only one child node: 									*/
	/*	XOR operator use is possible because the result of each experssion
		is either 0 or 1.													*/
	else if (!node_to_remove->children[LEFT] ^ !node_to_remove->children[RIGHT])
	{
		RemoveNodeWithOneSubTree(node_to_remove, found_location);
	}
	
	/*#CASE 3#*/
	/*	if node has 2 subtrees												*/
	else
	{
		RemoveNodeWithTwoSubTrees(node_to_remove);
	}
	
	return;
}
/*----------------------------------------------------------------------------*/
static void RemoveLeaf(rbst_node_ty *node, rbst_location_ty node_location)
{
	rbst_node_ty *node_to_remove = NULL;
	
	assert(node);
	
	node_to_remove = node;
	
	/*	link parent to null after removing the node						*/
	if(node_location.parent)
	{
		node_location.parent->children[node_location.direction] = NULL;
	}
	/* free node														*/							
	free(node_to_remove);
}
/*----------------------------------------------------------------------------*/
static void RemoveNodeWithOneSubTree(rbst_node_ty *node,
												rbst_location_ty node_location)
{
	rbst_node_ty *node_to_remove = NULL;
	
	sides_ty left_or_right_child = 0;
	
	assert(node);
	
	node_to_remove = node;
	
	/*	LEFT defined to be 0, RIGHT defined to be 1						*/
	/*	If node has a right child, link it to node's parent.
	 *	otherwise, link node's left child.								*/
	left_or_right_child = (!!node_to_remove->children[RIGHT]);
	
	node_location.parent->children[node_location.direction] = 
								node_to_remove->children[left_or_right_child];		

	/* free the node which was found									*/
	free(node_to_remove);
}
/*----------------------------------------------------------------------------*/
static void RemoveNodeWithTwoSubTrees(rbst_node_ty *node)
{
	rbst_node_ty *node_to_remove = NULL, *successor = NULL,
													*successor_parent = NULL;

	assert(node);
	
	node_to_remove = node;
	
		/*	find the successor's parent										*/
		/*	a successor of a node is the leftmost node of its right child	*/
		successor_parent = 
				GetSideMostIMP(node_to_remove->children[RIGHT], LEFT).parent;
		/*	if the successor is the leftmost node of the right child		*/
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
/*----------------------------------------------------------------------------*/
/*	traverse down from a node to find the leftmost or the rightmost node	*/
static rbst_location_ty GetSideMostIMP(rbst_node_ty *node, sides_ty side)
{
	rbst_location_ty found_location = {0};
	
	assert(node);
	assert(RIGHT == side || LEFT == side);
	
	/*	if no subtree in this direction exists								*/
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
	
	/*	create a node with the received data								*/
	/*	handle memory allocation errors if any								*/
	new_node = CreateNodeIMP(data);
	if (!new_node)
	{
		return (FAILURE);
	}
	
	/*	find a potential place for the node by using a location finder func	*/
	found_location = SearchLocationIMP(rbst, &rbst->stub, data);
	
	/*	if the location which was returned points to an exsiting node,
	 *	it means that there is already a node with that data.				*/
	 assert(!found_location.parent->children[found_location.direction] &&
	 						 "A key which already exists was inserted again");
	 
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
	
	/* 	calculate the height of the tree from the root of it, which
		is the left child of the stub of the tree							*/ 
	return (CalcTreeHeightIMP(rbst->stub.children[LEFT]));
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
	
	/* 	starts calculating the size of the tree from the root of it, which
		is the left child of the stub of the tree							*/
	return (GetTreeSizeIMP(rbst->stub.children[LEFT]));
}
/*----------------------------------------------------------------------------*/
static size_t GetTreeSizeIMP(rbst_node_ty *node)
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
	
	/*	return boolean if the root of the does not exist					*/
	return (!rbst->stub.children[LEFT]);
}
/******************************************************************************/
void *RBSTFind(const rbst_ty *rbst, const void *data_to_find)
{
	rbst_node_ty *found_node = NULL;
	
	rbst_ty *tree = NULL;
	
	rbst_location_ty potential_location = {0};
	
	assert(rbst);
	assert(data_to_find);
	
	tree = (rbst_ty *)rbst;
	
	/* start searching for the data from the stub to the rest of the tree	*/
	potential_location = SearchLocationIMP(rbst, &tree->stub, data_to_find);

	if (potential_location.parent)
	{
		/*	If a node with a matching key was found, return its data.
		 *	Otherwise, return NULL 											*/
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
	/*	if the search starts from the stub - move left 						*/
	direction_to_go = IsAStubIMP(node) ? LEFT :
						rbst->compare_func(node->data, data, rbst->param) < 0;
	
	
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

	return (RunOperationOnTreeIMP(rbst->stub.children[LEFT], action_func, param));
}
/*----------------------------------------------------------------------------*/
static int RunOperationOnTreeIMP(rbst_node_ty *node, Action_Func_ty action_func,
																void *param)
{
	/*	if node is null : return 0.											*/
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
static int IsAStubIMP(rbst_node_ty *node)
{	
	/* check if the given node is the stub of the tree						*/
	return (node && DEAD_MEM(void *) == node->data);
}
/******************************************************************************/


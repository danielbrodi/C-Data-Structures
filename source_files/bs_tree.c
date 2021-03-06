/*********************************FILE__HEADER*********************************\
* File:				bs_tree.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				15/05/2021
* Code Reviewer:	Rostik
* Pseudo Reviewer: 	Eran					   								
* Version:			2.2   								
* Description:		Binary Search Tree iterative implementation. 
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>			/*	assert			*/
#include <stddef.h>			/*	size_t, NULL	*/
#include <stdlib.h>			/*	malloc, free	*/

#include "bs_tree.h"

/******************************* Macros & enums *******************************/

#define DEAD_MEM(type) ((type)0xdeadbeef)
#define UNUSED(x) (void)(x)

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

/***************************** Structs Definition *****************************/

/*	handler struct of each node in a binary search tree					*/
struct bst_node
{
	bst_node_ty *parent;		/*	parent node							*/
	bst_node_ty *children[2];	/*	left and right child nodes	
								 *	left = 0, right = 1					*/
	void *data;					/*	data which is stored in the node	*/	
};

/*	handler struct of a binary search tree								*/
struct bst
{
	Cmp_Func_ty compare_func;	/*	helps to sort the nodes by
								 *	comparing them by its criteria		*/
	
	bst_node_ty stub;			/*	a stub that indicates on 
								 *	the end of the tree:
								 *	its left child node is the
								 *	root of the tree					*/
								 
	const void *param;			/*	param which is given by the user	*/
};

/*	return type for a potential location of a node						*/
typedef struct bst_location
{
	bst_node_ty *parent;		/*	parent node of the found location	*/
	sides_ty direction;			/*	0 if its the left child,
								 *	1 if its the right child			*/		
} bst_location_ty;

/**************************** Forward Declarations ****************************/

/*	creates a new node with the received data							*/
static bst_node_ty *CreateNodeIMP(void *data);

/*	loop down from a node to find the leftmost or the rightmost node	*/
static bst_node_ty *GetSideMostIMP(bst_node_ty *node, sides_ty side);

/* 	searches for the right location for a node with a key
	that equals to a given data. 										*/
static bst_location_ty BSTSearchLocationIMP(bst_ty *bst, void *data);

/*	searchs and returns the predecessor or the successor of a key		*/
static bst_node_ty *PrevNextImp(bst_iter_ty iter, sides_ty side);

/*	creates and returns an iterator for a given node 					*/
static bst_iter_ty NodeToIterIMP(bst_node_ty *node);

/*	returns the node which is pointed by a given iterator				*/
static bst_node_ty *IterToNodeIMP(bst_iter_ty iter);

static int NodesCounterIMP(void *counter, void *param);

/************************* Functions  Implementations *************************/

bst_ty *BSTCreate(Cmp_Func_ty sorting_func, const void *param)
{
	bst_ty *new_bst = NULL;
	
	/*	assure that `sorting_func` isn't null because
		a bst without a sorting	definition is meaningless.					*/
	assert(sorting_func);
	
	/*	allocate memory for bst's handler struct and return null if any
		allocation errors occured.											*/
	new_bst = (bst_ty *)malloc(sizeof(bst_ty));
	if (!new_bst)
	{
		return (NULL);
	}
	
	/*	Initialize bst's stub data, right child and parent as DEAD_MEM.		*/
	/*	Initialize stub's left child pointer as null.						*/
	new_bst->stub.data = new_bst->stub.children[RIGHT] = DEAD_MEM(bst_node_ty *);
	new_bst->stub.parent = DEAD_MEM(bst_node_ty *);
	new_bst->stub.children[LEFT] = NULL;
	
	/*	set the received `sorting_func` as the comparing func of the tree.	*/
	new_bst->compare_func = sorting_func;
	
	/*	set the received `param` as the param of the tree.					*/
	new_bst->param = param;
	
	/*	return a pointer to the created bst.								*/
	return (new_bst);
}
/******************************************************************************/
void BSTDestroy(bst_ty *bst)
{
	bst_iter_ty tree_runner = {0};
	bst_iter_ty end_of_tree = {0};
	
	assert(bst);
	
	tree_runner = BSTIterBegin(bst);
	end_of_tree = BSTIterEnd(bst);
	
	/* loop through the whole tree, and delete the nodes 	*/
	while (!BSTIterIsEqual(tree_runner, end_of_tree))
	{
		tree_runner = BSTRemoveIter(tree_runner);
	}
	
	/*	assign NULL to avoid dangling pointers				*/
	bst->stub.parent = bst->stub.data = bst->stub.children[LEFT] = NULL;	
	bst->compare_func = NULL;
	bst->param = NULL;
	
	free(bst);
}
/******************************************************************************/
static int NodesCounterIMP(void *data, void *counter)
{
	assert(counter);
	
	UNUSED(data);
	
	++(*(size_t *)counter);
	
	return (SUCCESS);
}
/******************************************************************************/
size_t BSTSize(const bst_ty *bst)
{
	bst_iter_ty minimum_key = {0};
	bst_iter_ty end_of_tree = {0};
	
	bst_ty *tree = (bst_ty *)bst; /* cheat and cast const to non-const	*/
	
	size_t counter = 0;
	
	assert(bst);
		
	/*	use BSTForEach and loop all over the tree with the counter.		*/
	
	minimum_key = BSTIterBegin(tree);
	end_of_tree = BSTIterEnd(tree);
	
	BSTForEach(minimum_key, end_of_tree, NodesCounterIMP, &counter);
		 									 
	return (counter);
}
/******************************************************************************/
int BSTIsEmpty(const bst_ty *bst)
{
	assert(bst);
	
	/* checks if the root node exists									*/
	return (!bst->stub.children[LEFT]);
}
/******************************************************************************/
static bst_node_ty *CreateNodeIMP(void *data)
{
	bst_node_ty *new_node = NULL;
	
	assert(data); /*	NULL data isn't accepted in this BST			*/
	
	/*	creates a new node with the received data						*/
    /* 	allocates memory, checks for allocation errors					*/
	new_node = (bst_node_ty *)malloc(sizeof(bst_node_ty));
	if (new_node)
	{
		/*	set data as data 											*/
		/* 	set children and parent pointers as null					*/
		new_node->data = data;
		new_node->children[LEFT] = new_node->children[RIGHT] = NULL;
		new_node->parent = NULL;
    }
    
    return (new_node);
}
/******************************************************************************/
bst_iter_ty BSTInsert(bst_ty *bst, void *data)
{
		bst_node_ty *new_node = NULL;
		bst_location_ty found_location = {0};
		
		assert(bst);
		assert(data); /*	NULL data isn't accepted in this BST		*/
		
		new_node = CreateNodeIMP(data);
		
		/*	case 1: if any error occured while creating the node 		*/
		if (!new_node)
		{
			return (NodeToIterIMP(&bst->stub));
		}
			
		/* case 2:	find a potential parent for the created node 		*/
		found_location = BSTSearchLocationIMP(bst, data); 
		
		/* check if data with the same key was found in the tree		*/
		assert (!(found_location.parent->children[found_location.direction])); 
		
		/*	assign new_node's parent as found_location.parent			*/
		new_node->parent = found_location.parent;
		
		/*	assign the new created node in the found location			*/
		found_location.parent->children[found_location.direction] = new_node;
								
		return (NodeToIterIMP(new_node));
}
/******************************************************************************/
bst_iter_ty BSTRemoveIter(bst_iter_ty to_remove)
{
	bst_node_ty *node;
	bst_node_ty *succ_node;
	
	bst_iter_ty successor = {0};
	
	int	child_side = -1, succ_side = -1;
	
	assert(to_remove.node);
	/*	check if to_remove is not end of the tree							*/
	assert(to_remove.node->data != DEAD_MEM(void *)); 
	
	node = IterToNodeIMP(to_remove);
	
	/*	find the successor of to_remove										*/
	successor = BSTIterNext(to_remove);
	succ_node = successor.node;
	
	/* determine the side of the node as a child node of its parent			*/
	child_side = node->parent->children[LEFT] == node ? LEFT : RIGHT;
	
	/*	#case1 - if to_remove is a leaf (no subtrees):						*/
	if (!node->children[LEFT] && !node->children[RIGHT])
	{
		/*	set to_remove's parent child as null.							*/
		node->parent->children[child_side] = NULL;
		
		/*	free node of 'to_remove'										*/
		free(node);
		node = NULL;
	}
	
	/*	#case2 - if only one child:											*/
	else if (!node->children[LEFT] || !node->children[RIGHT])
	{
		/*	link to_remove's parent to to_remove right subtree				*/
		if (node->children[RIGHT])
		{
			node->parent->children[child_side] = node->children[RIGHT];
			node->children[RIGHT]->parent = node->parent;
		}
		
		/*	link to_remove's parent to to_remove left subtree				*/
		else
		{
			node->parent->children[child_side] = node->children[LEFT];
			node->children[LEFT]->parent = node->parent;
		}
		
		/*	free node of 'to_remove'										*/
		free(node);
		node = NULL;
	}
	
	/*	#case3 - to_remove has 2 subtrees:									*/
	else
	{
		/* 	determine the side of the successor as a child node				*/
		succ_side = succ_node->parent->children[LEFT] == succ_node ? LEFT : RIGHT;
		
		/*	Copy successor's data to to_remove.data*/
		node->data = succ_node->data;
		
		/*	make successor's parent to point to successor's right subtree	*/
		succ_node->parent->children[succ_side] = succ_node->children[RIGHT];
		
		/*	if successor has a right child -
		 *	change its parent to the parent of the successor.				*/
		 if (succ_node->children[RIGHT])
		 {
		 	succ_node->children[RIGHT]->parent = succ_node->parent;
		 }
		 
		successor = to_remove;
		
		/*	free successor's node											*/
		free(succ_node);
		succ_node = NULL;
	}
		
	return (successor);
}
/******************************************************************************/
/*	loop down from a node to find the leftmost or the rightmost node	*/
static bst_node_ty *GetSideMostIMP(bst_node_ty *node, sides_ty side)
{
	bst_node_ty *runner = NULL;
	
	assert(node);
	assert(RIGHT == side || LEFT == side);
	
	runner = node;
	
	/*	while node's child on the received side exists:					*/
	/*	go to that child.												*/
	while (runner->children[side])
	{
		runner = runner->children[side];
	}
	
	return (runner);
}
/******************************************************************************/
bst_iter_ty BSTIterBegin(bst_ty *bst)
{
	assert(bst);
	
	/*	loop from the stub on the left sub-tree to find the minimum key	*/
	return (NodeToIterIMP(GetSideMostIMP(&bst->stub, LEFT)));	
}
/******************************************************************************/
bst_iter_ty BSTIterEnd(bst_ty *bst)
{
	assert(bst);
	
	return (NodeToIterIMP(&bst->stub));
}
/******************************************************************************/
static bst_node_ty *PrevNextImp(bst_iter_ty iter, sides_ty side)
{
	bst_node_ty *ret = NULL;
	bst_node_ty *node = (assert(iter.node), iter.node);
	
	assert(RIGHT == side || LEFT == side);
	
	ret = iter.node->parent;
	
	/*	if node's child on the received side exists:				*/
	if (node->children[side])
	{
		/*	the predecessor is the rightmost child of left subtree	*/
		/*	the successor is the leftmost child of right subtree	*/
		ret = GetSideMostIMP(node->children[side], !side);
	}
	
	else
	{
	/*	no left or right (based on needed key) child is available. 
		Thus - we need to climb up each time and verify that we come from
		the correct subtree.
		At the moment that we will come from the other direction, it will 
		mean that the parent is smaller or bigger, 
		which means its the first key that is smaller or bigger 
		than the received node. 									*/

		while (node->parent->children[RIGHT] != DEAD_MEM(bst_node_ty *) &&
		 								node == node->parent->children[side])
		{
			node = node->parent;
			ret = node->parent;
		}
	}
	
	return (ret);
}
/******************************************************************************/
bst_iter_ty BSTIterPrev(bst_iter_ty iter)
{
	assert(iter.node);
	
	return (NodeToIterIMP(PrevNextImp(iter, LEFT)));
}
/******************************************************************************/
bst_iter_ty BSTIterNext(bst_iter_ty iter)
{
	assert(iter.node);
	/* check iter is not BST END */
	assert(iter.node->children[RIGHT] != DEAD_MEM(bst_node_ty *));
	
	return (NodeToIterIMP(PrevNextImp(iter, RIGHT)));
}
/******************************************************************************/
int BSTIterIsEqual(bst_iter_ty iter1, bst_iter_ty iter2)
{
	assert (iter1.node && iter2.node);
		
	return (iter1.node == iter2.node);
}
/******************************************************************************/
void *BSTGetData(bst_iter_ty iter)
{
	assert(iter.node);
	
	return (iter.node->data);	
}
/******************************************************************************/
static bst_location_ty BSTSearchLocationIMP(bst_ty *bst, void *data)
{
	bst_node_ty *runner = NULL;
	
	bst_location_ty found_location = {0};

	sides_ty dir = LEFT;	/*	the runner starts at bst's stub which  
					 		 *	has only a left subtree.					*/	
	
	assert(bst && data);
		
	runner = &bst->stub;	
			
	while (runner->children[dir] &&
						bst->compare_func(data, runner->children[dir]->data, 
																	bst->param))
	{			
		runner = runner->children[dir];
		dir = bst->compare_func(runner->data, data, bst->param) > 0;
	}
		
	found_location.parent = runner;
	found_location.direction = dir;
	
	return (found_location);
}
/******************************************************************************/
bst_iter_ty BSTFind(bst_ty *bst, void *to_find)
{
	bst_iter_ty found_location = {0};
	
	bst_location_ty potential_location = {0};
	
	assert(bst && to_find);
		
	potential_location = BSTSearchLocationIMP(bst, to_find);
	
	found_location = NodeToIterIMP(potential_location.parent->
									children[potential_location.direction]);
	if (!found_location.node)
	{
		found_location = NodeToIterIMP(&bst->stub);
	}	
	
	return (found_location);
}
/******************************************************************************/
int BSTForEach(bst_iter_ty from_iter, bst_iter_ty to_iter, 
									Action_Func_ty action_func, void *param)
{
	bst_iter_ty runner = {0};
	int status = SUCCESS;
	
	assert(from_iter.node);
	assert(to_iter.node);
	assert(action_func);

	runner = from_iter;
	
	while (!BSTIterIsEqual(runner, to_iter) && !status)
	{
		status = action_func(runner.node->data, param);
		runner = BSTIterNext(runner);
	}

	return (status);		
}
/******************************************************************************/
static bst_node_ty *IterToNodeIMP(bst_iter_ty iter)
{
	assert(iter.node);
	
	return (iter.node);
}
/******************************************************************************/
static bst_iter_ty NodeToIterIMP(bst_node_ty *node)
{
	bst_iter_ty new_iter = {0};
	
	new_iter.node = node;
	
	return (new_iter);
}
/******************************************************************************/

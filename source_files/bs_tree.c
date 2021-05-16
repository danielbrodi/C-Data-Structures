/*********************************FILE__HEADER*********************************\
* File:				bs_tree.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				15/05/2021
* Code Reviewer:	Rostik						   								
* Version:			1.5				   								
* Description:		Binary Search Tree iterative implementation Pseudocode. 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>			/*	assert			*/
#include <stddef.h>			/*	size_t, NULL	*/

#include "bs_tree.h"


/***************************** Structs Definition *****************************/
/*	handler struct of a binary search tree								*/
struct bst
{
	Cmp_Func_ty sorting_func;	/*	sorts the nodes by its criteria		*/
	
	bst_node_ty stub;			/*	end dummy node of the tree:
								 *	its left child node is the
								 *	root of the tree					*/
								 
	void *param;				/*	param which is given by the user	*/
};

/*	handler struct of each node in a binary search tree					*/
struct bst_node
{
	bst_node_ty *up;			/*	parent node							*/
	bst_node_ty *right;			/*	right child node					*/
	bst_node_ty *left;			/*	left child node 					*/
	void *data;					/*	data which is stored in the node	*/
};

/**************************** Forward Declarations ****************************/
/*	creates a new node with the received data	*/
static bst_node_ty *CreateNode(void *data);
/*	returns the node that has the lowest key in the sub tree that
	starts at the given node					*/
static bst_node_ty *GetMinKeyNode(bst_node_ty *node);

/*************************** Functions  Pseudocodes ***************************/

bst_ty *BSTCreate(Cmp_Func_ty sorting_func, const void *param)
{
	/*
		assure that `sorting_func` isn't null because a bst without a sorting
		definition is meaningless. (assert)
		
		allocate memory for bst's handler struct and return null if any
		allocation errors.
		
		create an empty node that will be the end dummy node of the tree,
		check for any memory allocation errors and abort the bst creation
		if any.
		Initialize its data, right and left struct members as NULL.
		
		assign the created node to the stub member of the bst struct handler.
		
		set the received `sorting_func` as the sorting func of the tree.
		
		return a pointer to the created bst.
	
	*/
}
/******************************************************************************/
bst_node_ty *GetToBottomNode(bst_node_ty *node)
{
	/*
		while (node->left || node->right)
				{
					if node->left:
						go left.
					else if node->right:
						go right.
				}
	*/
}

void BSTDestroy(bst_ty *bst)
{
	/*
		if received bst pointer is null - do nothing.
		otherwise:
		
		node = bst->stub->left; // include assrt
		
		while node != bst->stub:
		
			node = GetToBottomNode(node);
			
			next_node_to_free = node->up;
			
			if node->data > next_node_to_free->data: // means its the right child
				next_node_to_free->right = NULL;
				
			else // means its the left child
				next_node_to_free->left = NULL;
			
			free(node);
			
			node = next_node_to_free;
			
		free(bst->stub);
		
		assign null to bst's struct handler members (cmp_func, param, stub).
		
		free bst.
		bst = null;
	*/
}
/******************************************************************************/


size_t BSTSize(const bst_ty *bst)
{
	/*
		assert bst.
		
		initialize a size_t counter.
		
		get to the "BSTIterBegin" node of the tree, and loop through all the nodes
		using BSTIterNext and count them till it reaches the `bst->end` node.
		
		return the count.
	*/
}
/******************************************************************************/


int BSTIsEmpty(const bst_ty *bst)
{
	/*
		assert bst.
		
		return value of (bst->root == bst->end).
	*/
}
/******************************************************************************/


bst_node_ty *CreateNode(void *data)
{
/*
    /*	creates a new node with the received data		*/
    /* 	allocates memory, checks for allocation errors	*/
    /*	set data as data, right and left ptrs as null	*/
    /*	return created node								*/
*/
}



bst_iter_ty BSTInsert(bst_ty *bst, void *data)
{
	/*
		assert both bst and data (NULL data isn't accepted in this BST).
		assert (bts->end == BSTFind(bst, data));
		
		new_node = CreateNode(data);
		
		if (NULL == new_node):
			return bst->end;
			
		if (BSTIsEmpty) : 
			set bst->root as new_node
			return new_node.
			
		Loop through the tree nodes from bst->root using a runner:
		
			runner = bst->root;
			is_inserted = 0;
			
			while (!is_inserted):
				if data > runner->data:
					if runner has right child, move to it.
					else: set created node as its right child & update is_inserted to 1.
					
				if data < runner->data:
					if runner has left child, move to it.
					else: set created node as its left child & update is_inserted to 1.
				}
	
		return (new_node);
	*/
}
/******************************************************************************/
bst_node_ty *GetMinValue(bst_node_ty *node)
{
/*
    nodes_runner = node;
    
    if (NULL != nodes_runner)
    {
	 	/*	loop down to find the leftmost leaf	/*
		while (NULL != nodes_runner->left)
		{
		    nodes_runner = nodes_runner->left;
		}
    }
    
    return nodes_runner;
    */
}

bst_iter_ty BSTIterBegin(const bst_ty *bst)
{
	/*
		assert bst
		assert !BSTIsEmpty
		
		loop from bst->root only on the left sub-tree to find the minimum value
		in the tree.
		
		return (GetMinValue->bst->root);
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterEnd(const bst_ty *bst)
{
	/*
		assert bst
		return bst->end;
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterPrev(bst_iter_ty iter)
{
	/*
		
		Needs the `parent` member? or assign `*bst_ty BST to bst->end node as data? 
		Needs the use of the root of the tree?
		*TODO*
	
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterNext(bst_iter_ty iter)
{
	/*
		assert(iter->node);
		assert(NULL != iter->node->right && NULL != iter->node->left); //CHECK THIS IS NOT BST END
		
		return (bst_iter_ty *(GetMinValue(iter->right)));
	*/
}
/******************************************************************************/


int BSTIterIsEqual(bst_iter_ty iter1, bst_iter_ty iter2)
{
	/*
		return iter1->node == iter2->node;
	*/
}
/******************************************************************************/

void *BSTGetData(bst_iter_ty iter)
{
	/*
		assert iter->node;
		
		return (iter->node)->data;
	*/
}
/******************************************************************************/


bst_iter_ty BSTFind(bst_ty *bst, void *to_find)
{
	/*
		assert bst and to_find (null data isn't accepted in this bst).
		
		assert !BSTIsEmpty
		
		curr_node = bst->root;
		
		while curr_node is not NULL && sorting_func(to_find, curr_node->data) != 0 (indicates data is equal)
		{
			if to_find > curr_node->data: move right
			if to find < curr_node->data: move left
		}
	
		check if the loop is over because curr_node is NULL or because data is equal.
		if curr_node is NULL : return BST END.
		
		return curr_node.
	
	*/
}
/******************************************************************************/


int BSTForEach(bst_iter_ty from_iter, bst_iter_ty to_iter, 
									Action_Func_ty action_func, void *param)
{
	/*
		
		assert : from_iter->node, to_iter->node, action_func;

		runner = from_iter;
		
		while (!BSTIterIsEqual(runner, to_iter))
		{
			execute action_func on each node with the given param.
			if action_func return failure: abort.
			else: move to next node using BSTIterNext.
		}

		return (0); // SUCCESS			
	
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

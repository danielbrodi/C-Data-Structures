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
static bst_node_ty *GetMinValue(bst_node_ty *node);

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
		assert bst
		
		next_node = null;
		node = bst->stub->left; // start from the root
		
		if not empty:
			while node != bst->stub:
			{
				next_node = BSTIterNext(node);
				BSTRemove(node);
				node = next_node;
			}
		
		bst->stub = bst->param = bst->sorting_func = null;
		free bst.
		bst = null;
	*/
}
/******************************************************************************/
static int NodesCounter(void *counter, void *param)
{
/*	assert*/
/*	unused param;*/
/*	*(size_t*)counter += 1;*/
	
/*	return 0;*/
}

size_t BSTSize(const bst_ty *bst)
{
	/*
		assert bst.
		
		size_t counter;
		
		if 0 = BSTForEach(root, bst->stub, NodesCounter, &counter);
		return counter.
		
		else
			return 0.
	*/
}
/******************************************************************************/


int BSTIsEmpty(const bst_ty *bst)
{
	/*
		assert bst.
		
		return value of (bst->stub->left == NULL). //root doesn't exist.
	*/
}
/******************************************************************************/
int IsLeftChild(bst, bst_node_ty parent, bst_node_ty child)
{
/*	assert*/

/*	return ((bst->cmp_func(parent->data, child->data) > 0);*/
	
}

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
		
		new_node = CreateNode(data);
		
		if (NULL == new_node):
			return bst->stub;
			
		if (BSTIsEmpty) : 
			set bst->stub->left as new_node
			return new_node.
			
		location = BSTSearchLocation(bst, data);
		
		if (location->data equals data)
		{
			abort(1)
		}
		
		else
		{
			if (IsLeftChild(location, new_node))
				location->left = new_node;
			else
				location->right = new_node;
		}
	
		return (new_node);
	*/
}
/******************************************************************************/
/*	loop down to find the leftmost leaf	*/
bst_node_ty *GetMinKey(bst_node_ty *node)
{
	/*  
    if node isn't null:
    	while node->left exists:
    		go node->left.
    		
    return node.
    */
}

/*	loop down to find the rightmost leaf	*/
bst_node_ty *GetMaxKey(bst_node_ty *node)
{
	/*  
    if node isn't null:
    	while node->right exists:
    		go node->right.
    		
    return node.
    */
}

bst_iter_ty BSTIterBegin(const bst_ty *bst)
{
	/*
		assert bst
		assert !BSTIsEmpty
		
		loop from bst->stub->left only on the left sub-tree to find the minimum value
		in the tree.
		
		return (GetMinValue(bst->stub->left));
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterEnd(const bst_ty *bst)
{
	/*
		assert bst
		return bst->stub;
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterPrev(bst_iter_ty iter)
{
	/*
		assert iter->node
		assert to check if its iter == BSTIterBegin (???) TODO
	
		prev = null;
		
		if node->left isnt null:
			//	the predecessor is the rightmost child of left subtree or
			 	left child itself. //
			 	
			prev = GetMaxKey(node->left);
			
		else: 
		
			// 	no left child is available. thus - we need
				to climb up each time and verify that we come from the left.
				In the moment that we will come from the right, it means the parent
				is smaller, which means its the first key that is smaller than the 
				received node. //
				
			parent = node->up	
			
			while parent && node == parent->left
			{
				node = parent
				parent = parent->up
			}
			prev = parent;
			
			
		return prev;	
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterNext(bst_iter_ty iter)
{
	/*
		assert(iter->node);
		assert(deadbeef != iter->node->right) // check if iter != BST_END
		
		next = null;
		
		if (node->right != null):
		
			// the successor is the leftmost child of right subtree
			or the right child itself. //
			
			next = GetMinKey(node->right);
			
		else: 
		
			// 	no right child is available. thus - we need
				to climb up each time and verify that we come from the right.
				In the moment that we will come from the left, it means the parent
				is bigger, which means its the first key that is bigger than the 
				received node. //
				
			parent = node->up	
			
			while parent && node == parent->right
			{
				node = parent
				parent = parent->up
			}
			next = parent;
			
		return next;
			
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
bst_iter_ty *BSTSearchLocation(bst_ty *bst, void *data)
{
	/*
	Loop through the tree nodes from the root (bst->stub->left) using a runner:
		
		runner = bst->stub->left;
		is_found = 0;

		while (!is_found):

			#option1:
			if data > runner->data: // check using bst->sorting_func > 0:

				if runner has right child, move to it and loop again.

				else: break

			#option2:
			else if data < runner->data:	
				
					if: runner has left child, move to it and loop again.

					else: break;
					
			#option3:	
			else: is_found = 1;
			
		return iter to runner;
	*/
}

bst_iter_ty BSTFind(bst_ty *bst, void *to_find)
{
	/*
		assert
		
		ret_node = BSTSearchLocation(bst, to_find);
		
		if (ret_node->data !equals to_find)
			ret_node = bst->stub;
			
		return ret_node;
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

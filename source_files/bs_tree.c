/*********************************FILE__HEADER*********************************\
* File:				bs_tree.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				15/05/2021
* Code Reviewer:	Rostik						   								
* Version:			1.7			   								
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
	Cmp_Func_ty compare_func;	/*	helps to sort the nodes by
								 *	comparing them by its criteria		*/
	
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

/*	return type for potential location of a node						*/
typedef struct bst_location
{
	bst_node_ty *parent;		/*	parent node of the found location	*/
	int direction;				/*	-1 if this is a right child,
								 *	1 if this is a right child,
								 *	0 if equals to a given data.		*/
} bst_location_ty;

/**************************** Forward Declarations ****************************/
/*	creates a new node with the received data	*/
static bst_node_ty *CreateNode(void *data);

/*	returns the node that has the lowest key in the sub tree that
 *	starts at the given node					*/
static bst_node_ty *GetMinKey(bst_node_ty *node);

/*	returns the node that has the largest key in the sub tree that
 *	starts at the given node					*/
static bst_node_ty *GetMaxKey(bst_node_ty *node);

/* 	returns 1 if a given child is the left child
 *	of a given parent, 0 otherwise.				*/
static int IsLeftChild(bst, bst_node_ty parent, bst_node_ty child);

/* 	searches for the right location for a node with a key
	that equals to a given data. 				*/
static bst_node_ty *BSTSearchLocation(bst_ty *bst, void *data);

static int NodesCounter(void *counter, void *param);
/*************************** Functions  Pseudocodes ***************************/

bst_ty *BSTCreate(Cmp_Func_ty sorting_func, const void *param)
{
	/*
		assure that `sorting_func` isn't null because a bst without a sorting
		definition is meaningless. (assert)
		
		allocate memory for bst's handler struct and return null if any
		allocation errors.
	
		Initialize stub's data, right and up struct members as DEAD_MEM.
		Initialize stub's left child as null.
		
		set the received `compare_func` as the comparing func of the tree.
		
		return a pointer to the created bst.
	
	*/
}
/******************************************************************************/
void BSTDestroy(bst_ty *bst)
{
	/*
		assert bst
		
		while node != BST END:
			node = Remove(node);
		
		free bst end & bst
	*/
}
/******************************************************************************/
static int NodesCounter(void *data, void *counter)
{
/*	assert						*/
/* unused data					*/
/*	*(size_t*)counter += 1;		*/
	
/*	return 0;*/
}

size_t BSTSize(const bst_ty *bst)
{
	/*
		assert bst.
		
		size_t counter;
		
		use BSTForEach and loop all over the tree with the counter.
		
		return count.
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
static int IsLeftChild(bst, bst_node_ty parent, bst_node_ty child)
{

/*	assert*/

/*	return (parent data > child data)	*/
	
}

static bst_node_ty *CreateNode(void *data)
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
		
		case 1: if error while creating node:
			return BST END
			
		case 2: if bst is empty: 
			set root as new_node
			return new_node.
			
		case 3:	
		FoundParent = BSTSearchLocation(bst, data); //find potential parent
		
		assert (FoundParent->data equals data);
		
		IsLeftChild(FoundParent, new_node) ? location->left = new_node : 
													location->right = new_node;
													
		return (new_node);
	*/
}
/******************************************************************************/

bst_iter_ty BSTRemoveIter(bst_iter_ty to_remove)
{
	/*
		assert iter
		assert to_remove->data != deadbeef
		
		#case1: if to_remove is a leaf (no subtrees):
					unlink to_remove from its parent.
					free(to_remove)
		
		#case2: if only one child:
					link to_remove parent to to_remove subtree.
					free (to_remove)
						
		#case3: to_remove has 2 subtrees:
					Find successor of to_remove
					Copy successor's data to to_remove->data
					make successor's parent to point to successor's right subtree.
					
					if successor has right child - change its parent to the parent of the successor.		
					
	*/
}
/******************************************************************************/
/*	loop down to find the leftmost leaf	*/
static bst_node_ty *GetMinKey(bst_node_ty *node)
{
	/*  
	assert
	
    if node isn't null:
    	while node->left exists:
    		go node->left.
    		
    return node.
    */
}

/*	loop down to find the rightmost leaf	*/
static bst_node_ty *GetMaxKey(bst_node_ty *node)
{
	/*  
	assert
	
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
		
		//loop from the root only on the left sub-tree to find the minimum value
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
			
			while parent->right != DEAD_MEM && node == parent->left
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
			
			while parent->right != DEAD_MEM && node == parent->right
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
static bst_location_ty *BSTSearchLocation(bst_ty *bst, void *data)
{
	/*
	Loop through the tree nodes from the root (bst->stub->left) using a runner:
		
		runner = bst->stub->left;

		bst_location_ty found_location;
		
		while (runner != null && runner->data not equal to data):

			parent = runner->up;
			
			runner = IsLeftChild(runner->data, data) ? move left : move right;
			
		found_location->parent = parent;
		found_location->direction = cmp_func(parent->data, data);
	*/
}

bst_iter_ty BSTFind(bst_ty *bst, void *to_find)
{
	/*
		assert
		
		ret_node = BSTSearchLocation(bst, to_find);
		
		if (ret node is null which means not match)
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
		
		status = 1
		
		while (!BSTIterIsEqual(from_iter, to_iter) && status)
		{
			execute action_func on each node with the given param.
			move to next node using BSTIterNext.
		}

		return (status); // SUCCESS			
	
	*/
}
/******************************************************************************/

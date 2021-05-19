/*********************************FILE__HEADER*********************************\
* File:				bs_tree.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				15/05/2021
* Code Reviewer:	Rostik						   								
* Version:			2.0		   								
* Description:		Binary Search Tree iterative implementation Pseudocode. 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>			/*	assert			*/
#include <stddef.h>			/*	size_t, NULL	*/

#include "bs_tree.h"

/******************************* Macros & enums *******************************/
#define DEAD_MEM(type) ((type)0xdeadbeef)

/*	from which direction the child node connected to its parent node	*/
enum side
{
	LEFT = 0,
	RIGHT = 1
};

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
	bst_node_ty *parent;		/*	parent node							*/
	bst_node_ty children[0,1];	/*	left and right child nodes			*/
	void *data;					/*	data which is stored in the node	*/
};

/*	return type for potential location of a node						*/
typedef struct bst_location
{
	bst_node_ty *parent;		/*	parent node of the found location	*/
	int direction;				/*	0 if its a left child,
								 *	1 if its a right child				*/
} bst_location_ty;

/**************************** Forward Declarations ****************************/
/*	creates a new node with the received data	*/
static bst_node_ty *CreateNodeIMP(void *data);

/*	loop down from a node to find the leftmost or the rightmost leaf	*/
static bst_node_ty *GetMaxMinIMP(bst_node_ty *node, int side)


static bst_iter_ty PrevNextImp(bst_iter_ty iter, int side);

/* 	searches for the right location for a node with a key
	that equals to a given data. 				*/
static bst_location_ty *BSTSearchLocationIMP(bst_ty *bst, void *data);

static int NodesCounterIMP(void *counter, void *param);
/*************************** Functions  Pseudocodes ***************************/

bst_ty *BSTCreate(Cmp_Func_ty sorting_func, const void *param)
{
	/*
		assure that `sorting_func` isn't null because a bst without a sorting
		definition is meaningless. (assert)
		
		allocate memory for bst's handler struct and return null if any
		allocation errors.
	
		Initialize stub's data, right child and parent struct members as DEAD_MEM.
		Initialize stub's left child as null.
		
		set the received `sorting_func` as the comparing func of the tree.
		
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
static int NodesCounterIMP(void *data, void *counter)
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
static bst_node_ty *CreateNodeIMP(void *data)
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
		
		new_node = CreateNodeIMP(data);
		
		case 1: if error while creating node:
			return BST END
			
		case 2: if bst is empty: 
			set new_node's parent as the stub
			set stub left child as new_node
			return new_node.
			
		case 3:	
		found_location = BSTSearchLocationIMP(bst, data); //find potential parent
		
		assert (found_location data is equal to received data); 
		
		get to the found_location by the recevied data and assign new_node.
		assign new_node's parent as found_location->parent.
													
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
/*	loop down from a node to find the leftmost or the rightmost leaf	*/
static bst_node_ty *GetMaxMinIMP(bst_node_ty *node, int side)
{
	/*  
	assert
	
    if node isn't null:
    	while node's child on the received side exists:
    		go to that child.
    		
    return the last visited node.
    */
}

bst_iter_ty BSTIterBegin(const bst_ty *bst)
{
	/*
		assert bst
		assert !BSTIsEmpty
		
		//loop from the root only on the left sub-tree to find the minimum value
		in the tree.
		
		return (GetMaxMinIMP(tree root, LEFT));
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
static bst_iter_ty PrevNextImp(bst_iter_ty iter, int side)
{
	/*
		assert iter->node
		
		if node's child on the received side exists:
		
			//	the predecessor is the rightmost child of left subtree or
			 	left child itself.
			 	
			 	the successor is the leftmost child of right subtree
				or the right child itself. //
			
			ret = GetMaxMinIMP(node->child[side], !side);
			
		else:
			
			// 	no left or right (based on needed key) child is available. 
			Thus - we need to climb up each time and verify that we come from
			the right subtree.
			At the moment that we will come from the other direction, it will 
			mean that the parent is smaller or bigger, 
			which means its the first key that is smaller or bigger 
			than the received node. //
			
			while parent->right != DEAD_MEM && node == parent->child[side]
			{
				node = parent
				parent = parent->parent
			}
			
			return parent
	*/
}

bst_iter_ty BSTIterPrev(bst_iter_ty iter)
{
	/*
		assert iter->node
	
		return PrevNextImp(node, LEFT);
	*/
}
/******************************************************************************/


bst_iter_ty BSTIterNext(bst_iter_ty iter)
{
	/*
		assert(iter->node);
		assert(deadbeef != iter->node->right) // check if iter != BST_END
		
		return PrevNextImp(node, RIGHT);
			
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
static bst_location_ty *BSTSearchLocationIMP(bst_ty *bst, void *data)
{
	/*
	Loop through the tree nodes from the root (bst->stub->left) using a runner:
		
		runner = bst->stub->left;

		bst_location_ty found_location;
		
		while runner and runner's data isn't equal:

			parent = runner
			
			runner = move left or right based on runner's data compared with the received data.
			
			dir = the direction we moved.
			
		assign last saved parent to found_location->parent
		assign last saved dir to found_location->direction
		
		return found_location.
	*/
}

bst_iter_ty BSTFind(bst_ty *bst, void *to_find)
{
	/*
		assert
		
		found_location = BSTSearchLocationIMP(bst, to_find);
		
		if (found_location data is equal to 'to_find'):
			set found_location as BST END;
		
		return found_location;
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

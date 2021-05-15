/*********************************FILE__HEADER*********************************\
* File:				bs_tree.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				13/05/2021
* Code Reviewer:	Rostik						   								
* Version:			1.0						   								
* Description:		Binary Search Tree implementation Pseudocode. 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>			/*	assert			*/
#include <stddef.h>			/*	size_t, NULL	*/

#include "bs_tree.h"


/***************************** Structs Definition *****************************/
/*	handler struct of a binary search tree									*/
struct bst
{
	Cmp_Func_ty sorting_func;	/*	will sort the nodes by its criteria		*/
	bst_node_ty *root;			/*	the root node of the tree				*/
	bst_node_ty *end;			/*	the end dummy node of the tree			*/
};

/*	handler struct of each node in a binary search tree						*/
struct bst_node
{
/*	bst_node_ty *up;		/* 	the parent node - do I need it? Maybe for BSTIterPrev?	*/*/
	bst_node_ty *right;		/*	the right child node						*/
	bst_node_ty *left;		/*	the left child node 						*/
	void *data;				/*	the data that is stored in the node			*/
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
		initialize its data, next and previous struct members as NULL.
		
		assign the dummy node to the begin and end pointers of the created bst.
		set the received `sorting_func` as the sorting func of the tree.
		
		return a pointer to the created bst.
	
	*/
}
/******************************************************************************/

void BSTDestroy(bst_ty *bst)
{
	/*
		if received bst pointer is null - do nothing.
		otherwise:
		
		loop through the tree from begin to end using BSTIterNext and free each
		node.
		free the end dummy node.
		
		assign null to bst's struct handler members (cmp_func, begin, end).
		
		free bst.
		assign null to bst ptr to avoid a dangling pointer.
	*/
}
/******************************************************************************/


size_t BSTSize(const bst_ty *bst)
{
	/*
		assert bst.
		
		initialize a size_t counter.
		
		get to the "bst->begin" node of the tree, and loop through all the nodes
		using BSTIterNext and count them till it reaches the `bst->end` node.
		
		return the count.
	*/
}
/******************************************************************************/


int BSTIsEmpty(const bst_ty *bst)
{
	/*
		assert bst.
		
		return value of (bst->begin == bst->end).
	*/
}
/******************************************************************************/


bst_node_ty *CreateNode(void *data)
{
/*
    bst_node_ty *new_node = (bst_node_ty *)malloc(sizeof(bst_node_ty));
    if (NULL == new_node)
    {
    	return (NULL);
    }
    
    new_node->data = data;
    new_node->left = new_node->right = NULL;

    return new_node;
*/
}



bst_iter_ty BSTInsert(bst_ty *bst, void *data)
{
	/*
		assert both bst and data (NULL data isn't accepted in this BST).
		assert (bts->end == BSTFind(bst, data));
		
		bst_node_ty *new_node = CreateNode(data);
		
		if (NULL != CreateNode(data)):
		
			if (1 == BSTIsEmpty) : 
				set bst-> begin & bst->root & bst->begin as new_node.
				set new_node->right & left as NULL.
				return new_node.
				
			else if (data < (bst->begin)->data) : 
				set bst->begin as new_node.
				
			Loop through the tree nodes from bst->root using a runner:
			
				runner = bst->root;
				is_inserted = 0;
				
				while (!is_inserted):
					if (bst->sorting_func(data, runner->data) > 0)
					{
						if (NULL = runner->right)
						{
							new_node = runner->right;
							is_inserted = 1;
						}
						else
						{
							runner = runner->right;
						}
					}		
					else
					{
						if (NULL = runner->left)
						{
							new_node = runner->left;
							is_inserted = 1;
						}
						else
						{
							runner = runner->left;
						}
					}
	
		return (new_node);
	*/
}
/******************************************************************************/
bst_node_ty *GetMinValue(bst_node_ty *node)
{
/*
    bst_node_ty *nodes_runner = node;
    
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
		assert(NULL != iter->node->right && NULL != iter->node->left); //BST END
		
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
		
		bst_node_ty *curr_node = bst->root;
		
		while (curr_node && 0 != bst->sorting_func(to_find, curr_node->data))
		{
			if (bst->sorted_list(to_find, curr_node->data) > 0)
			{
				curr_node = curr_node->right;
			}
			else
			{
				curr_node = curr_node->left;
			}
		}
	
		if (!curr_node) // data not found in tree
		{
			curr_node = bst->end;
		}
		
		return (bst_iter_ty *(curr_node));
	
	*/
}
/******************************************************************************/


int BSTForEach(bst_iter_ty from_iter, bst_iter_ty to_iter, 
									Action_Func_ty action_func, void *param)
{
	/*
	
		bst_iter_ty runner;
		
		void *data_check = NULL;	// check that action_func didnt change
										the keys of the nodes.
		
		assert : from_iter->node, to_iter->node, action_func;

		runner = from_iter;
		
		while (!BSTIterIsEqual(runner, to_iter))
		{
			data_check = BSTGetData(runner);
			
			if (0 != action_func(BSTGetData(runner), param))
			{
				return (1); //action_func returned an error.
			}
			
			else if (data_check != BSTGetData(runner))
			{
				abort.
				//????// how can I check if the data remained the same?
				can't compare void ptrs.
			}
			
			runner = BSTIterNext(runner);
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

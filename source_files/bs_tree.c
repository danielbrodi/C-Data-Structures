/*********************************FILE__HEADER*********************************\
* File:				bs_tree.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				15/05/2021
* Code Reviewer:	Rostik
* Pseudo Reviewer: 	Eran					   								
* Version:			2.0		   								
* Description:		Binary Search Tree iterative implementation. 
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>			/*	assert			*/
#include <stddef.h>			/*	size_t, NULL	*/

#include "bs_tree.h"

/******************************* Macros & enums *******************************/

#define DEAD_MEM(type) ((type)0xdeadbeef)
#define UNUSED(x) (void)(x)

/*	from which direction the child node connected to its parent node	*/
/*	status indication of a finished operation							*/
enum
{
	LEFT = 0,
	RIGHT = 1,
	SUCCESS = 0,
	FAILURE = 1
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
								 
	void *param;				/*	param which is given by the user	
};

/*	handler struct of each node in a binary search tree					*/
struct bst_node
{
	bst_node_ty *parent;		/*	parent node							*/
	bst_node_ty children[2];	/*	left and right child nodes	
								 *	left = 0, right = 1					*/
	void *data;					/*	data which is stored in the node	
};

/*	return type for potential location of a node						*/
typedef struct bst_location
{
	bst_node_ty *parent;		/*	parent node of the found location	*/
	int direction;				/*	0 if its the left child,
								 *	1 if its the right child			
} bst_location_ty;

/**************************** Forward Declarations ****************************/

/*	creates a new node with the received data							*/
static bst_node_ty *CreateNodeIMP(void *data);

/*	loop down from a node to find the leftmost or the rightmost node	*/
static bst_node_ty *GetSideMostIMP(bst_node_ty *node, int side)

/* 	searches for the right location for a node with a key
	that equals to a given data. 										*/
static bst_location_ty BSTSearchLocationIMP(bst_ty *bst, void *data);

static bst_iter_ty PrevNextImp(bst_iter_ty iter, int side);

static int NodesCounterIMP(void *counter, void *param);

/************************* Functions  Implementations *************************/

bst_ty *BSTCreate(Cmp_Func_ty sorting_func, const void *param)
{
	bst_ty *new_bst = NULL;
	bst_node_ty *stub = NULL;
	
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
	stub = new_bst->stub;
	stub->data = stub->children[RIGHT] = stub->parent = DEAD_MEM;
	stub->children[LEFT] = NULL;
	
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
	
	assert(bst);
	
	/*	while node != BST END:		*/
	/*		node = Remove(node);	*/
	
	while()
	
	/*		free bst end & bst		*/
	
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
	bst_iter_ty minimum_key = NULL;
	bst_iter_ty end_of_tree = NULL;
	
	assert(bst);
		
	size_t counter = 0;

	/*	use BSTForEach and loop all over the tree with the counter.		*/
	
	minimum_key = BSTIterBegin(bst);
	end_of_tree = BSTIterEnd(bst);
	
	BSTForEach(minimum_key, end_of_tree, NodesCounterIMP, &counter);
		 									 
	return (counter);
}
/******************************************************************************/
int BSTIsEmpty(const bst_ty *bst)
{
	assert(bst);
	
	return (NULL == bst->stub->left); /* checks if the root node exists	*/
}
/******************************************************************************/
static bst_node_ty *CreateNodeIMP(void *data)
{
	assert(data); /*	NULL data isn't accepted in this BST	*/
	
    /*	creates a new node with the received data				*/
    /* 	allocates memory, checks for allocation errors			*/
    /*	set data as data, right, left and parent ptrs as null	*/
    /*	return created node										*/

}

bst_iter_ty BSTInsert(bst_ty *bst, void *data)
{

		assert both bst and data (NULL data isn't accepted in this BST).
		
		new_node = CreateNodeIMP(data);
		
		case 1: if error while creating node:
			return BST END
			
		case 2:	
		found_location = BSTSearchLocationIMP(bst, data); //find potential parent
		
		assert (found_location data is not equal to received data); 
		
		get to the found_location by the recevied data and assign new_node.
		assign new_node's parent as found_location->parent.
		assign found_location->parent child by the received direction as new_node.
													
		return (new_node);
	
}
/******************************************************************************/

bst_iter_ty BSTRemoveIter(bst_iter_ty to_remove)
{

		assert iter
		assert to_remove->data != deadbeef
		
		ret = next of to_remove;
		
		#case1: if to_remove is a leaf (no subtrees):
					set to_remove's parent child as null.
					free to_remove		
		
		#case2: if only one child:
					link to_remove parent to to_remove subtree.
					free to_remove		
						
		#case3: to_remove has 2 subtrees:
					Find successor of to_remove
					Copy successor's data to to_remove->data
					make successor's parent to point to successor's right subtree.
					
					if successor has a right child - change its parent to the parent of the successor.		
					ret = to_remove;
					free successor

				
		return ret;			
	
}
/******************************************************************************/
/*	loop down from a node to find the leftmost or the rightmost leaf	*/
static bst_node_ty *GetSideMostIMP(bst_node_ty *node, int side)
{
  
	assert
	
    	while node's child on the received side exists:
    		go to that child.
    		
    return the last visited node.
    
}

bst_iter_ty BSTIterBegin(const bst_ty *bst)
{

		assert bst
		
		//loop from the root only on the left sub-tree to find the minimum value
		in the tree.
		
		return (GetSideMostIMP(tree stub, LEFT));
	
}
/******************************************************************************/


bst_iter_ty BSTIterEnd(const bst_ty *bst)
{

		assert bst
		return bst->stub;
	
}
/******************************************************************************/
static bst_iter_ty PrevNextImp(bst_iter_ty iter, int side)
{

		assert iter->node
		
		if node's child on the received side exists:
		
			//	the predecessor is the rightmost child of left subtree.//
			 	
			 	the successor is the leftmost child of right subtree.//
			
			ret = GetSideMostIMP(node->child[side], !side);
			
		else:
			
			// 	no left or right (based on needed key) child is available. 
			Thus - we need to climb up each time and verify that we come from
			the correct subtree.
			At the moment that we will come from the other direction, it will 
			mean that the parent is smaller or bigger, 
			which means its the first key that is smaller or bigger 
			than the received node. //
			
			while parent's right child != DEAD_MEM && node == parent->child[side]
			{
				node = parent
				parent = parent->parent
			}
			
			return parent
	
}
/******************************************************************************/
bst_iter_ty BSTIterPrev(bst_iter_ty iter)
{

		assert iter->node
		TODO assert its not begin
	
		return PrevNextImp(node, LEFT);
	
}
/******************************************************************************/


bst_iter_ty BSTIterNext(bst_iter_ty iter)
{

		assert(iter->node);
		assert(deadbeef != iter->node->right) // check if iter != BST_END
		
		return PrevNextImp(node, RIGHT);
			
	
}
/******************************************************************************/


int BSTIterIsEqual(bst_iter_ty iter1, bst_iter_ty iter2)
{

		assert
		
		return iter1->node == iter2->node;
	
}
/******************************************************************************/

void *BSTGetData(bst_iter_ty iter)
{

		assert iter->node;
		
		return (iter->node)->data;
	
}
/******************************************************************************/
static bst_location_ty *BSTSearchLocationIMP(bst_ty *bst, void *data)
{

	Loop through the tree nodes from the (bst->stub) using a runner:
		
		runner = bst->stub;
	
		bst_location_ty found_location;
		
		dir = LEFT		
				
		while runner->child[dir] isn't null and child[dir]->data isn't equal to param data:
					
			runner = runner->child[dir]
			
			dir = the direction we will move, based on cmp_func result.
			
		assign runner to found_location->parent
		assign dir to found_location->direction
		
		return found_location.
	
}

bst_iter_ty BSTFind(bst_ty *bst, void *to_find)
{

		assert
		
		found_location = BSTSearchLocationIMP(bst, to_find);
		
		if (found_location's child data is null):
			set found_location as BST END;
		
		return found_location's child;
	
}
/******************************************************************************/


int BSTForEach(bst_iter_ty from_iter, bst_iter_ty to_iter, 
									Action_Func_ty action_func, void *param)
{

		
		assert : from_iter->node, to_iter->node, action_func;
		
		status = 0
		
		while (!BSTIterIsEqual(from_iter, to_iter) && !status)
		{
			status = execute action_func on each node with the given param.
			move to next node using BSTIterNext.
		}

		return (status); // SUCCESS			
	
	
}
/******************************************************************************/

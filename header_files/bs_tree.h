/*********************************FILE__HEADER*********************************\
* File:				bs_tree.h				 		  												  								
* Date:				13/05/2021							   								
* Version:			1.0						   								
* Description:		Binary Search Tree implementation API 
\******************************************************************************/

#ifndef __BS_TREE_H__
#define __BS_TREE_H__

#include <stddef.h>		/*	size_t							*/

typedef struct bst bst_ty;

typedef struct bst_iter bst_iter_ty;

/*	Compare Func returns:
 *	0 if data1 equals to data2
 *	Positive value if data2 belongs somewhere after data1
 *	Negative value if data1 belongs somewhere after data2	*/
typedef int (*Cmp_Func_ty)(const void *data1, const void *data2, 
															const void *param);

/* 	Returns 0 on success 									*/
/* 	Should not change the key of the data 					*/
typedef int (*Action_Func_ty)(void *data, void *param);

/* 	Complexity O(1) 										*/
bst_ty *BSTCreate(Cmp_Func_ty sorting_func, const void *param);

/* 	Complexity O(n) - n is tree size 						*/
void BSTDestroy(bst_ty *bst);

/* 	Complexity O(n) - n is tree size 						*/
size_t BSTSize(const bst_ty *bst);

/* 	Complexity O(1) 										*/
int BSTIsEmpty(const bst_ty *bst);

/* 	Returns iterator to the new element 					*/
/* 	On memory allocation failure, returns iterator END 		*/
/*	IMPORTANT: 	Undefined behavior if data with the
 *				same key is already in the tree 			*/
 				
/* 	Complexity O(log (n)) - n is tree size 					*/
bst_iter_ty BSTInsert(bst_ty *bst, void *data);

/* 	Returns iterator to next element 						*/
/* 	Undefined behavior if to_remove is iterator END 		*/
/* 	Complexity O(log (n)) - n is tree size 					*/
bst_iter_ty BSTRemoveIter(bst_iter_ty to_remove);

/* 	Complexity O(log (n)) - n is tree size 					*/
bst_iter_ty BSTIterBegin(bst_ty *bst);

/* 	Complexity O(1) 										*/
bst_iter_ty BSTIterEnd(bst_ty *bst);

/* 	Undefined behavior if iter is BEGIN 					*/
/* 	Complexity O(log (n)) - n is tree size 					*/
bst_iter_ty BSTIterPrev(bst_iter_ty iter);

/* 	Undefined behavior if iter is END 						*/
/* 	Complexity O(log (n)) - n is tree size  				*/
bst_iter_ty BSTIterNext(bst_iter_ty iter);

/* 	Complexity O(1) 										*/
int BSTIterIsEqual(bst_iter_ty iter1, bst_iter_ty iter2);

/* 	Undefined behavior if iter is END 						*/
/* 	Complexity O(1) 										*/
void *BSTGetData(bst_iter_ty iter);

/* 	Returns End if not found 								*/
/* 	Complexity O(log (n)) - n is tree size 					*/
bst_iter_ty BSTFind(bst_ty *bst, void *to_find);

/*	action_func is applied to elements in range [from_iter, to_iter) 	
 *	Stops if action_func fails, and returns its failure status 			
 *	Undefined behavior if action_func changes the keys 		*/				
/*	Complexity O(n*log(n)) - n is tree size 				*/
int BSTForEach(bst_iter_ty from_iter, bst_iter_ty to_iter, 
									Action_Func_ty action_func, void *param);

/*	BST's iterator definition								*/
typedef struct bst_node bst_node_ty;

struct bst_iter
{
	bst_node_ty *node;
/*	DEBUG_ONLY(size_t version;)*/
};

#endif	/* __BS_TREE_H__ */

/*********************************FILE__HEADER*********************************\
* File:				bs_tree.c						 		  								
* Author:			Daniel Brodsky					  								
* Date:				13/05/2021							   								
* Version:			1.0	(After Review)							   								
* Description:		Binary Search Tree implementation API 
\******************************************************************************/

#ifndef	__BS_TREE_H__
#define	__BS_TREE_H__

#include <stddef.h>		/* size_t					*/

#include "utils.h"		/* status_ty, boolean_ty	*/

typedef struct BST BST_ty;

typedef struct BST_node BST_node_ty;

typedef BST_node_ty *BST_iter_ty;

/* Creates an empty binary tree list and returns pointer to handler struct */
/* returns NULL on failure*/
/* Complexity: O(1) */
dlist_ty *BSTCreate(void);

/* Frees entire tree */
/* Immitates Free() if BST is NULL */
/* Complexity: O(n) */
void BSTDestroy(dlist_ty *BST);

/* Returns iterator to root of the tree, the smallest key */
/* If BST is empty returns BST_END */
/* Complexity: O(1) */
BST_iter_ty BSTBegin(const BST_ty *BST);

/* Returns iterator to the end of the tree */
/* Complexity: O(1) */
BST_iter_ty BSTEnd(const BST_ty *BST);

/* Returns iterator to the next node in the tree */
/* Returns BST_END on the last element in the list */
/* Undefined if iter is BST_END */
/* Complexity: O(1) */
BST_iter_ty BSTNext(const BST_iter_ty iter);

/* Returns iterator to the previous node in the tree */
/* Undefined if iter is BST_BEGIN */
/* Complexity: O(1) */
BST_iter_ty BSTPrev(const BST_iter_ty iter);

/* Returns TRUE if both are iterators of the same node, FALSE otherwise */
/* Complexity: O(1) */
boolean_ty BSTIterIsEqual(const BST_iter_ty iter_a, 
													const BST_iter_ty iter_b);

/* Returns the data of the node that is pointed by the iterator */
/* Undefined behaviour if iter is BST_END */
/* Complexity: O(1) */
void *BSTGetData(const BST_iter_ty iter);

/* Inserts the data as a new node in the tree	*/
/* Returns an iterator to the node 				*/
/* On failure returns NULL 						*/
/* Complexity: O(n) 							*/
BST_iter_ty BSTInsert(void *data);

/* Removes the node that points by iter from the tree. 	*/
/* Returns SUCCESS or FAILURE.							*/
/* Undefined behaviour if iter is BST_END 				*/
/* Complexity: O(1) */
status_ty BSTRemove(BST_iter_ty iter);

/* Returns TRUE if the tree is empty or FALSE otherwise */
/* Complexity: O(1) */
boolean_ty BSTIsEmpty(const BST_ty *BST);


size_t BSTSize(const BST_ty *BST);


BST_iter_ty BSTFind(const BST_iter_ty from_iter, 
								const BST_iter_ty to_iter, 
										IsMatch_Func_ty match_func,
												void *param);

			
status_ty BSTForEach
								
							 
#endif	/* __BS_TREE_H__ */

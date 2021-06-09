/*********************************FILE__HEADER*********************************\
* File:				rbst.h						 		  								
* Author:			Daniel Brodsky					  								
* Date:				06-06-2021							   												   								
* Description:		Recursive Binary Tree API.		 
\******************************************************************************/

#ifndef __RBST_H__
#define __RBST_H__

#include <stddef.h>		/*	size_t		*/

typedef struct rbst rbst_ty;

/*	Compare Func returns:
 *	Positive value if data1 comes before data2.
 *	Negative value if data2 comes before data1.
 *	0 if data1 equals to data2.												*/
typedef int (*Cmp_Func_ty)(const void *data1, const void *data2, 
															const void *param);

/*	Returns 0 on success 													*/
/*	Should not change the key of the data 									*/
typedef int (*Action_Func_ty)(void *data, void *param);

/*	returns NULL on failure													*/
/*	Complexity O(1) 														*/
rbst_ty *RBSTCreate(Cmp_Func_ty cmp_func, const void *param);

/*	Complexity O(n) - n is tree size 										*/
void RBSTDestroy(rbst_ty *rbst);

/*	Complexity O(log(n)) - n is tree size									*/
void RBSTRemove(rbst_ty *rbst, const void *data);

/* 	On memory allocation failure, returns non-zero 							*/
/*	IMPORTANT: Undefined behavior if data with the same key is already in the
 *	tree 																	*/
/*	Complexity O(log (n)) - n is tree size 									*/
int RBSTInsert(rbst_ty *rbst, void *data);

/*	returns (-1) if tree is empty											*/
/*	Complexity: O(n) - n is tree size										*/
int RBSTHeight(const rbst_ty *rbst);

/*	Complexity O(n) - n is tree size 										*/
size_t RBSTSize(const rbst_ty *rbst);

/*	Complexity O(1) 														*/
int RBSTIsEmpty(const rbst_ty *rbst);

/*	Returns NULL if not found 												*/
/*	Complexity O(log (n)) - n is tree size 									*/
void *RBSTFind(const rbst_ty *rbst, const void *data_to_find);

/*	action_func is applied to all elements in rbst in in-order				*/
/*	Stops if action_func fails, and returns its failure status 				*/
/*	Undefined behavior if action_func changes the keys 						*/
/*	Complexity O(n*log(n)) - n is tree size 								*/
int RBSTForEach(rbst_ty *rbst, Action_Func_ty action_func, void *param);

#endif 			/*		__RBST_H__		*/

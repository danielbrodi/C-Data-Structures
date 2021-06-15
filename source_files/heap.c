/*********************************FILE__HEADER*********************************\
* File:				heap.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				14-06-2021
* Code Reviewer:	
* Pseudo Reviewer:	Eran					   								
* Version:			1.0							
* Description:		Heap implementation.
\******************************************************************************/

#include <assert.h>
#include <stddef.h>	/* sise_t, NULL	*/

#include "heap.h"

/******************************************************************************/

static int GetParentIndexIMP(int child_index);

static int GetLeftChildIndexIMP(int parent_index);

static int GetRightChildIndexIMP(int parent_index);

static int GetBiggestElemIndexIMP(void **base, size_t num_of_elements, 
	Heap_Cmp_Func_ty compare, int left_child_index, int right_child_index,
														int parent_index);

void HeapifyDownRecIMP(void **base, size_t num_of_elements, 
								Heap_Cmp_Func_ty compare, int root_index);
								
static void SwapElementsIMP(void **elem1, void **elem2);												
/******************************************************************************/
/*void HeapSort(void **base, size_t num_of_elements, Heap_Cmp_Func_ty compare)*/
/*{*/
	/*	asserts*/

	/*	start with size of 1 */
	/*	iterate as many elements as they are.*/
	/*	for each iteration:*/
	/*		HeapifyUp(base, size, compare)*/
	/*		increment size by one.*/

	/*	run from start to size of the array:*/
	/*		for each iteration:*/
	/*			swap first & last element*/
	/*			decrement size by one*/
	/*			HeapifyDown on the sub-array  */
/*}*/
/******************************************************************************/
void HeapifyUp(void **base, size_t size, Heap_Cmp_Func_ty compare)
{
	int parent_index = 0, curr_elem_index = 0;
	
		/*	asserts*/
	assert(base);
	assert(size);
	assert(compare);
	
	curr_elem_index = size;
	parent_index = GetParentIndexIMP(curr_elem_index);
	
	/*	till reach a node without a parent (the "root") or parent is bigger*/
	if (1 == size || compare(base[parent_index], base[curr_elem_index]) > 0)
	{
		return;
	}
	
	/*	recursivly scan each node to check if its bigger than its parent*/
	/*	if it does: swap them*/
	SwapElementsIMP(base + parent_index, base + curr_elem_index);
	
	HeapifyUp(base, size / 2, compare);
}
/******************************************************************************/
void HeapifyDown(void **base, size_t size, Heap_Cmp_Func_ty compare)
{
	/*	assert*/
	assert(base);
	assert(size);
	assert(compare);

	/*	recursivly traverse the array from the root and switch each node with its
	 *	bigger child node (if any)		*/
	 HeapifyDownRecIMP(base, size, compare, 0);
}									 
/*----------------------------------------------------------------------------*/														 
void HeapifyDownRecIMP(void **base, size_t num_of_elements, 
									Heap_Cmp_Func_ty compare, int root_index)
{
	int parent_index = 0, left_child_index = 0, right_child_index = 0;
	int biggest_element_index = 0;
	
	/*	assert*/
	assert(compare);
	
	parent_index = root_index;
	left_child_index = GetLeftChildIndexIMP(parent_index);
	right_child_index = GetRightChildIndexIMP(parent_index);
	
	/* compare root index with both of its childs to find if there is 
		a bigger child. If yes - swap them. 	*/
	biggest_element_index = GetBiggestElemIndexIMP(base, num_of_elements, compare, 
							left_child_index, right_child_index, parent_index);
	
	if (parent_index != biggest_element_index)
	{
		SwapElementsIMP(base + parent_index, base + biggest_element_index);
		
		HeapifyDownRecIMP(base, num_of_elements - 1, compare, biggest_element_index);
	}
}												
/******************************************************************************/
static int GetBiggestElemIndexIMP(void **base, size_t num_of_elements, 
	Heap_Cmp_Func_ty compare, int left_child_index, int right_child_index,
	int parent_index)
{
	int biggest_element_index = parent_index;
	
	assert(base);
	assert(compare);
	
	/* check if the index is in the range of the array and  bigger than parent*/
	if (left_child_index < (int)num_of_elements && 
								base[left_child_index] > base[parent_index]) 
	{
		biggest_element_index = left_child_index;
	}
	
	/* check if the index is in the range of the array and  bigger than parent*/
	if (left_child_index < (int)num_of_elements && 
								base[right_child_index] > base[parent_index]) 
	{
		biggest_element_index = right_child_index;
	}
	
	/*	return the index of biggest element of the tree */
	return (biggest_element_index);
}
/******************************************************************************/
static int GetParentIndexIMP(int child_index)
{	
	return (child_index < 2 ? -1 : (child_index - 1) / 2);
}
/******************************************************************************/
static int GetLeftChildIndexIMP(int parent_index)
{	
	return (parent_index < 1 ? -1 : (parent_index * 2 + 1));
}
/******************************************************************************/
static int GetRightChildIndexIMP(int parent_index)
{	
	return (parent_index < 1 ? -1 : (parent_index * 2 + 2));
}
/******************************************************************************/
static void SwapElementsIMP(void **elem1, void **elem2)
{
	void *temp = (assert(elem1), *elem1);
	
	assert(elem2);
	
	*elem1 = *elem2;
	
	*elem2 = temp;
}
/******************************************************************************/

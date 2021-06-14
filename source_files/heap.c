/*********************************FILE__HEADER*********************************\
* File:				heap.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				14-06-2021
* Code Reviewer:	
* Pseudo Reviewer:	Eran					   								
* Version:			1.0							
* Description:		Heap implementation.
\******************************************************************************/


/******************************************************************************/
void HeapifyUp(void **base, size_t size, Heap_Cmp_Func_ty compare)
{
	void *parent = NULL, *curr_elem = NULL;
	
	/*	asserts*/
	assert(base);
	assert(size);
	assert(compare);
	
	parent = GetParentIMP(base, size - 1);
	curr_elem = base[size - 1];
	
	/*	till reach a node without a parent (the "root") or parent is bigger*/
	if (1 == size || compare(parent, curr_elem) > 0)
	{
		return;
	}
	
	/*	recursivly scan each node to check if its bigger than its parent*/
	/*	if it does: switch them*/
	SwitchElementsIMP(parent, curr_elem);
	
	return (HeapifyUp(base, size / 2, compare));
}
/******************************************************************************/
void HeapifyDown(void **root, size_t size, Heap_Cmp_Func_ty compare)
{
	/*	assert*/
	assert(root);
	assert(size);
	assert(compare);

	/*	till reach a node without children or if no child node is biger	*/
	bigger_child = GetBiggerChildIMP(root, 0)
	curr_elem = base[size - 1];

	/*	recursivly traverse the array and switch each root with its
															 bigger child node*/
															 
															 
}
/******************************************************************************/
static void *GetBiggerChildIMP(void **parent, size_t parent_index)
{
	size_t bigger_child_index = 0, right_child_index = 0, left_child_index = 0;
	
}


static void *GetParentIMP(void **base, size_t child_index)
{
	size_t parent_index = 0;
	
	assert(base);
	assert(child_index);
	
	parent_index = child_index / 2;
	
	return (base[parent_index]);
}
/******************************************************************************/

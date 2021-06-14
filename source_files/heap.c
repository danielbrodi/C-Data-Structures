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
	/*	asserts*/

	/*	recursivly scan each node to check if its bigger than its parent*/
	/*	if it does: switch them*/

	/*	till reach a node without a parent (the "root") or parent is bigger*/
}
/******************************************************************************/
void HeapifyDown(void **base, size_t size, Heap_Cmp_Func_ty compare)
{
	/*	assert*/

	/*	recursivly traverse the array and switch each root with its bigger child node*/

	/*	till reach a node without children or if no child node is biger	*/
}
/******************************************************************************/

void** VectorGetActualArray(vector_ty*);

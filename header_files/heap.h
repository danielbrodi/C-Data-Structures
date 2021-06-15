/*********************************FILE__HEADER*********************************\
* File:				heap.h												  								
* Date:				13-06-2021					   								
* Version:			1.0							
* Description:		Heap API.
\******************************************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>	/*	size_t	*/

/* Compare Func returns negative if data2 belongs somewhere after */
/* data1 in the heap */
/* Returns 0 if the keys are equal */
/* Returns positive otherwise */
typedef int (*Heap_Cmp_Func_ty)(const void *data1, const void *data2);

/* Operation to fix heap after insertion*/
/* Complexity: O(log(size))*/
void HeapifyUp(void **base, size_t size, Heap_Cmp_Func_ty compare);

/* Operation to fix heap after removal*/
/* Complexity: O(log(size))*/
void HeapifyDown(void **base, size_t size, Heap_Cmp_Func_ty compare);

#endif	/*	__HEAP_H__	*/

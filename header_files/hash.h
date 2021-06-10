/*********************************FILE__HEADER*********************************\
* File:				hash.h						 		  								
* Author:			Daniel Brodsky					  								
* Date:				09-06-2021							   												   								
* Description:		Hash Map API.		 
\******************************************************************************/

#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h>		/*	size_t	*/

typedef struct hash_table ht_ty;

typedef struct statistics
{
	size_t longest_list;
	size_t median_list;
	float std;
}statistics_ty;

typedef size_t (*hash_func_ty)(const void *data, const void *param);

typedef int (*is_same_key_func_ty)(const void *data1, const void *data2);

/*Complexity: O(capacity)*/
/*Returns NULL of memory failure*/
ht_ty *HTCreate(size_t capacity, hash_func_ty hash_func, const void *hash_param,
												is_same_key_ty is_same_func);

/*Doesn't release user's data*/
/*Complexity: O(1)*/
void HTDestroy(ht_ty *hash_table);

/*Complexity: O(1)*/
int HTInsert(ht_ty *hash_table, void *data);

/*Returns the number of elements in the table*/
/*Complexity: O(n)*/
size_t HTSize(const ht_ty *hash_table);

/*Returns NULL if key not found*/
/*Complexity: O(1)*/
void *HTFind(ht_ty *hash_table, const void *key);

/*Note: removing non-existing data is ignored*/
/*Complexity: O(1)*/
void HTRemove(ht_ty *hash_table, const void *key);

/*Complexity: O(n)*/ /*Phase 2*/
statistics_ty HTGetStatistics(const ht_ty *hash_table);
/*longest list, median list, and standard deviation as a struct*/

#endif /*__HASH_H__*/

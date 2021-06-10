/*********************************FILE__HEADER*********************************\
* File:				hash.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				09-06-2021
* Code Reviewer:	
* Pseudo Reviewer: 						   								
* Version:			1.0   								
* Description:		Hash Map implementation pseudo-code.
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>			/*	assert			*/
#include <stddef.h>			/*	size_t, NULL	*/
#include <stdlib.h>			/*	malloc, free	*/

#include "dlist.h"
#include "hash.h"


/******************************* Macros & enums *******************************/



/**************************** Structs  Definitions ****************************/

struct hash_table
{
	dlist_ty **items;
	hash_func_ty hash_func;
	size_t capacity;
	is_same_key_ty is_same;
};

/**************************** Forward Declarations ****************************/



/************************* Functions  Implementations *************************/
ht_ty *HTCreate(size_t capacity, hash_func_ty hash_func, const void *hash_param,
													is_same_key_ty is_same_func)
{
	ht_ty *new_hash_table = NULL;
	size_t i = 0;
	/*	asserts for parameters*/
	assert(capacity);
	assert(hash_func);
	assert(is_same_func);
	/*	allocate memory for hash map structure & handle memory errors if any*/
	new_hash_table = (ht_ty *)malloc(sizeof(ht_ty) + (capacity)*sizeof(dlist_ty));
	if (!new_hash_table)
	{
		return (NULL);
	}
	/*	create and allocate memory for an array of */
	/*	dlists of size of capacity,*/
	/*	and assign to the struct member, handle memory errors if any.*/
	/* loop on the array and create dlist at each index				*/
	for (i = 0; i < capacity; ++i)
	{
		*items = DlistCreate();
		if (!items)
		{
			while (i > 0)
			{
				--i;
				free(items - i)
			}
			
			free(new_hash_table);
			return (NULL);
		}
	}
	
	/*	assign rest of the parameters to the corrosponding struct members*/
	new_hash_table->items = new_hash_table; /*	first member in the struct 	*/
	new_hash_table->hash_func = hash_func;
	new_hash_table->capacity = capacity;
	new_hash_table->is_same = is_same_func;
	
	/*	return created hash map*/
	return (new_hash_table);
}
/******************************************************************************/
void HTDestroy(ht_ty *hash_table)
{
	size_t num_of_bins = hash_table->capacity, i = 0;
	/*	loop through the map and destory dlist at each index*/
	while (i < num_of_bins)
	{
		DlistDestroy(hash_table->items);
		hash_table->items = items + i;
		++i
	}
	
	/*	free the hash map*/
	memset(hash_table, 0, hash_table->capacity + sizeof(ht_ty));
	
	free(hash_table);
	
	hash_table = NULL;
}
/******************************************************************************/
int HTInsert(ht_ty *hash_table, void *data)
{
	size_t bin_index = -1;
	dlist_ty *dlist = NULL;
	dlist_iter_ty ret_status;
	
	/*	assert*/
	assert(hash_table);
	assert(data);	/* NULL data is not allowed in tis hash table	*/
	
	/*	use hash func to get the right index to insert data into*/
	bin_index = hash_table->hash_func(data, hash_table->param);
	/*	go to that index in the dlists array*/
	dlist = hash_table->items + bin_index;
	/*	use the insert func of dlist to insert the data*/
	ret_status = DlistPushFront(dlist, data);
	/*	return status of inserttion*/
}	return (ret_status == DlistIteratorEnd(dlist)) ? FAILURE : SUCCESS;
/******************************************************************************/
size_t HTSize(const ht_ty *hash_table)
{
	/*	assert */

	/*	loop on each index in the hash table and check for dlist size using*/
	/*	dlist size func*/

	/*	return the sum of all sizes*/
}
/******************************************************************************/
void *HTFind(ht_ty *hash_table, const void *key)
{
	/*	asserts*/
	/*	move to the right index by hash func(key)	*/
	/*	 use find function of dlist */
	/*	getdata on the result of find */
	/*	compare each key with is_same_func*/
	/*	to the given key*/
	/* if not equal - move next	*/

	/*	return null or the element*/
}
/******************************************************************************/
int HTIsEmpty(const ht_ty *hash_table)
{
	/*	loop on the table, and use isempty dlist at each index*/
	/*	if in the end everything is empty, return true*/
	/* OR */
	/*	check if HTSize is 0*/
}
/******************************************************************************/
void HTRemove(ht_ty *hash_table, const void *key)
{
	/*	use hash func to get right index of the right dlist */
	/*	dlist find(key,is_same_func)
	/*	remove on the iterator that recieved from the dlist find function 	*/ 
}
/******************************************************************************/

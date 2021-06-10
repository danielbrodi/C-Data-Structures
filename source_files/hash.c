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
	memset(hash_table, 0, sizeof(ht_ty));
	
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
	bin_index = hash_table->hash_func(data, hash_table->hash_param);
	
	/*	go to that index in the dlists array*/
	dlist = hash_table->items + bin_index;
	
	/*	use the push func of dlist to insert the data*/
	ret_status = DlistPushFront(dlist, data);
	
	/*	return status of inserttion*/
	/*	if ret_status is the end iterator of the list it means the
		insertion was failed.											*/
	return (DlistIteratorIsEqual(ret_status, DlistIteratorEnd(dlist)));
}
/******************************************************************************/
size_t HTSize(const ht_ty *hash_table)
{
	dlist *curr_list = *last_list = NULL;
	size_t total_size = 0;
	
	/*	assert */
	assert(hash_table);
	
	/*	loop on each index in the hash table and check for dlist size using*/
	/*	dlist size func*/
	curr_list = hash_table->items;	/*	first list	*/
	last_list = lists_runner + hash_table->capacity;
	
	while (curr_list < last_list)
	{
		total_size += DlistSize(curr_list);
	}
	
	/*	return the sum of all sizes*/
	return (total_size);
}
/******************************************************************************/
void *HTFind(ht_ty *hash_table, const void *key)
{
	size_t bin_index = -1;
	dlist_ty *dlist = NULL;
	void *ret = NULL;
	dlist_iter_ty ret_iter;
	
	/*	asserts*/
	assert(hash_table);
	assert(key);
	
	/*	move to the right index by hash func(key)	*/
	bin_index = hash_table->hash_func(key, hash_table->hash_param);
	
	dlist = hash_table->items + bin_index;
	
	/*	 use find function of dlist */
	ret_iter = DlistFind(DlistIteratorBegin(dlist), DlistIteratorEnd(dlist), 
										hash_table->is_same, hash_table->param);
	
	/*	return null or the element*/
	return (DlistIteratorIsEqual(ret_iter, DlistIteratorEnd(dlist)) ? NULL :
														DlistGetData(ret_iter));
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

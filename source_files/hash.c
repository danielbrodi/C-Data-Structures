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
#include <string.h>

#include "dlist.h"
#include "hash.h"


/******************************* Macros & enums *******************************/



/**************************** Structs  Definitions ****************************/

struct hash_table
{
	dlist_ty **items;
	hash_func_ty hash_func;
	size_t capacity;
	is_same_key_func_ty is_same;
	const void *hash_param;
};
/* TODO maybe create it locally because it used only by one function */
typedef struct extended_param
{
	ht_ty *hash_table;
	const void *key;
}extended_param_ty;

/**************************** Forward Declarations ****************************/


/*TODO create helper functions because remove, insert and find use the same
		things	*/
/************************* Functions  Implementations *************************/
ht_ty *HTCreate(size_t capacity, hash_func_ty hash_func, const void *hash_param,
											is_same_key_func_ty is_same_func)
{
	ht_ty *new_hash_table = NULL;
	
	size_t i = 0;
	
	/*	asserts for parameters*/
	assert(capacity);
	assert(hash_func);
	assert(is_same_func);
	
	/*	allocate memory for hash map structure & handle memory errors if any*/
	new_hash_table = (ht_ty *)malloc(sizeof(ht_ty));
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
		*(new_hash_table->items) = DlistCreate();
		if (!new_hash_table->items)
		{
			while (i > 0)
			{
				--i;
				DlistDestroy(*(new_hash_table->items - i));
			}
			
			free(new_hash_table);
			return (NULL);
		}
	}
	
	/*	assign rest of the parameters to the corrosponding struct members*/
	new_hash_table->hash_func = hash_func;
	new_hash_table->capacity = capacity;
	new_hash_table->is_same = is_same_func;
	new_hash_table->hash_param = hash_param;
	
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
		DlistDestroy(*(hash_table->items));
		hash_table->items += i;
		++i;
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
	dlist = *(hash_table->items + bin_index);
	
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
	dlist_ty *curr_list = NULL, *last_list = NULL;
	size_t total_size = 0;
	
	/*	assert */
	assert(hash_table);
	
	/*	loop on each index in the hash table and check for dlist size using*/
	/*	dlist size func*/
	curr_list = *(hash_table->items);	/*	first list	*/
	last_list = *(hash_table->items + hash_table->capacity);
	
	while (curr_list < last_list)
	{
		total_size += DlistSize(curr_list);
	}
	
	/*	return the sum of all sizes*/
	return (total_size);
}
/******************************************************************************/
int CompareKeysIMP(const void *data1, void *extended_param)
{
	ht_ty *hash_table = ((extended_param_ty *)extended_param)->hash_table;
	const void *key = ((extended_param_ty *)extended_param)->key;
	
	return(hash_table->is_same(data1, key));
}
/*----------------------------------------------------------------------------*/
void *HTFind(ht_ty *hash_table, const void *key)
{
	size_t bin_index = -1;
	
	dlist_ty *dlist = NULL;
	dlist_iter_ty ret_iter;
	
	extended_param_ty extended_param = {0};
	
	/*	asserts*/
	assert(hash_table);
	assert(key);
	
	/*	move to the right index by hash func(key)	*/
	bin_index = hash_table->hash_func(key, hash_table->hash_param);
	
	dlist = *(hash_table->items + bin_index);
	
	extended_param.hash_table = hash_table;
	extended_param.key = key;
	
	/*	 use find function of dlist */
	ret_iter = DlistFind(DlistIteratorBegin(dlist), DlistIteratorEnd(dlist), 
								CompareKeysIMP, &extended_param);
	
	/*	return null or the element*/
	return (DlistIteratorIsEqual(ret_iter, DlistIteratorEnd(dlist)) ? NULL :
														DlistGetData(ret_iter));
}
/******************************************************************************/
void HTRemove(ht_ty *hash_table, const void *key)
{
	size_t bin_index = -1;
	dlist_ty *dlist = NULL;
	dlist_iter_ty ret_iter;
	extended_param_ty extended_param = {0};
	
	/*	asserts	*/
	assert(hash_table);
	assert(key);
	
	/*	use hash func to get right index of the right dlist */
	bin_index = hash_table->hash_func(key, hash_table->hash_param);
	
	dlist = *(hash_table->items + bin_index);
	
	extended_param.hash_table = hash_table;
	extended_param.key = key;
	
	/*	 use find function of dlist */
	ret_iter = DlistFind(DlistIteratorBegin(dlist), DlistIteratorEnd(dlist), 
										CompareKeysIMP, &extended_param);
										
	/*	remove on the iterator that recieved from the dlist find function 	*/
	if (!DlistIteratorIsEqual(ret_iter, DlistIteratorEnd(dlist)))
	{
		DlistRemove(ret_iter);
	}
}
/******************************************************************************/

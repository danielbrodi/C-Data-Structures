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

/*	searches for an item in a hash table based on a given key to look for.
 *	returns a dlist iterator to that item if found.
 *	otherwise, returns iterator which points to '0'							*/
static dlist_iter_ty FindItemIMP(ht_ty *hash_table, const void *key_to_find);

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
	new_hash_table = malloc(sizeof(ht_ty));
	if (new_hash_table)
	{
		/*	assign parameters to the corrosponding struct members*/
		new_hash_table->hash_func = hash_func;
		new_hash_table->capacity = capacity;
		new_hash_table->is_same = is_same_func;
		new_hash_table->hash_param = hash_param;
		
		new_hash_table->items = malloc(sizeof(dlist_ty *) * capacity);
		if (!new_hash_table->items)
		{
			HTDestroy(new_hash_table);
			return (NULL);
		}
		/*	create and allocate memory for an array of */
		/*	dlists of size of capacity,*/
		/*	and assign to the struct member, handle memory errors if any.*/
		/* loop on the array and create dlist at each index				*/
		for (i = 0; i < capacity; ++i)
		{
			*(new_hash_table->items + i) = DlistCreate();
			
			if (!(*(new_hash_table->items + i)))
			{
				new_hash_table->capacity = i;
				HTDestroy(new_hash_table);
				new_hash_table = NULL;
			}
		}	
	}
	
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
		DlistDestroy(*(hash_table->items + i));
		++i;
	}
	
	free(hash_table->items);
	
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
	
	dlist_iter_ty ret_status = {0};
	
	/*	assert*/
	assert(hash_table);
	assert(data);	/* NULL data is not allowed in tis hash table	*/
	
	/*	use hash func to get the right index to insert data into*/
	bin_index = hash_table->hash_func(data, hash_table->hash_param) %
														 hash_table->capacity;
	
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
	size_t total_size = 0, i = 0;
	
	/*	assert */
	assert(hash_table);
	
	/*	loop on each index in the hash table and check for dlist size using*/
	/*	dlist size func*/
	curr_list = *(hash_table->items);	/*	first list	*/
	last_list = *(hash_table->items + hash_table->capacity - 1);
	
	while (curr_list < last_list)
	{
		total_size += DlistSize(curr_list);
		++i;
		curr_list = *(hash_table->items + i);
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
	dlist_iter_ty item_to_find, not_found_iter = {0};
	
	/*	asserts*/
	assert(hash_table);
	assert(key);
	
	item_to_find = FindItemIMP(hash_table, key);
	
	/*	return null or the element*/
	return (DlistIteratorIsEqual(item_to_find, not_found_iter) ? NULL :
													DlistGetData(item_to_find));
}
/******************************************************************************/
void HTRemove(ht_ty *hash_table, const void *key)
{
	
	dlist_iter_ty item_to_remove, not_found_iter = {0};
		
	/*	asserts	*/
	assert(hash_table);
	assert(key);
	
	item_to_remove = FindItemIMP(hash_table, key);
										
	/*	remove on the iterator that recieved from the FindIMP func	*/
	if (!DlistIteratorIsEqual(not_found_iter, item_to_remove))
	{
		DlistRemove(item_to_remove);
	}
}
/******************************************************************************/
/*	returns iter that equals to 0 if not found */
static dlist_iter_ty FindItemIMP(ht_ty *hash_table, const void *key_to_find)
{
	dlist_iter_ty ret_iter, not_found_iter = {0};
	
	dlist_ty *dlist = NULL;
	
	extended_param_ty extended_param = {0};
	
	size_t bin_index = -1;
		
	assert(hash_table);
	assert(key_to_find);
	
	/*	use hash func to get right index of the right dlist */
	bin_index = hash_table->hash_func(key_to_find, hash_table->hash_param) %
														hash_table->capacity;
	
	dlist = *(hash_table->items + bin_index);
	
	extended_param.hash_table = hash_table;
	extended_param.key = key_to_find;
	
	/*	 use find function of dlist */
	ret_iter = DlistFind(DlistIteratorBegin(dlist), DlistIteratorEnd(dlist), 
										CompareKeysIMP, &extended_param);
										
	if (DlistIteratorIsEqual(ret_iter, DlistIteratorEnd(dlist)))
	{
		return (not_found_iter);
	}
										
	return (ret_iter);
}
/******************************************************************************/

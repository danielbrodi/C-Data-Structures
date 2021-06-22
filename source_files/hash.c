/*********************************FILE__HEADER*********************************\
* File:				hash.c
* Author:			Daniel Brodsky				 		  												  								
* Date:				09-06-2021
* Code Reviewer:					   								
* Version:			1.0   								
* Description:		Hash Map implementation.
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <assert.h>			/*	assert				*/
#include <stddef.h>			/*	size_t, NULL		*/
#include <stdlib.h>			/*	malloc, free, qsort	*/
#include <string.h>			/*	memset				*/

#include "dlist.h"
#include "hash.h"

/**************************** Structs  Definitions ****************************/

/* Hash Table structure */
struct hash_table
{
	dlist_ty **items;
	hash_func_ty hash_func;
	size_t capacity;
	is_same_key_func_ty is_same;
	const void *hash_param;
};

/* Used for functions which look for a specific key in the hash table	*/
typedef struct extended_param
{
	ht_ty *hash_table;
	const void *key;
}extended_param_ty;

/**************************** Forward Declarations ****************************/

/*	searches for an item in a hash table based on a given key to look for.
 *	returns a dlist iterator to that item if found.
 *	otherwise, returns iterator to the end of the list which has been searched*/
dlist_iter_ty FindItemIMP(ht_ty *hash_table, const void *key_to_find, 
																dlist_ty *list);

/*	creates an array of doubly linked lists. Receives an allocated array
 *	and runs through it and creates a list in each element of the array
 *	returns 0 if succeeded, 1 otherwise	*/
static int CreateListsArrayIMP(dlist_ty **lists, size_t size);

/*	compares 2 lists lengths: 
 *	returns an integer less than, equal to, or greater than zero if
 *	the first argument is considered to be respectively less than,
 *	equal to, or greater than the second.	*/
static int CompareListsLengthIMP(const void *length1, const void *length2);

/*	returns the bin's index of the list that contains the key which is 
 *	looked for */
static int GetBinOfKeyIMP(ht_ty *hash_table, const void *key_to_find);
/************************* Functions  Implementations *************************/

ht_ty *HTCreate(size_t capacity, hash_func_ty hash_func, const void *hash_param,
											is_same_key_func_ty is_same_func)
{
	ht_ty *new_hash_table = NULL;
	
	/*	asserts for recevied parameters	*/
	assert(capacity);
	assert(hash_func);
	assert(is_same_func);
	
	/*	allocate memory for hash map structure & handle memory errors if any*/
	new_hash_table = (ht_ty *)malloc(sizeof(ht_ty));
	if (new_hash_table)
	{		
		/* allocate memory for the lists array and handle memory errors if any*/
		new_hash_table->items = (dlist_ty **)malloc(sizeof(dlist_ty *) * capacity);
		
		/* if memory allocation succeeded */
		if (new_hash_table->items)
		{	
			/* if lists creation inside the array was failed */
			if (CreateListsArrayIMP(new_hash_table->items, capacity))
			{
				free(new_hash_table->items);
				new_hash_table->items = NULL;
				
				free(new_hash_table);
				new_hash_table = NULL;
			}
			else
			{
				/*	assign parameters to the corrosponding struct members*/
				new_hash_table->hash_func = hash_func;
				new_hash_table->capacity = capacity;
				new_hash_table->is_same = is_same_func;
				new_hash_table->hash_param = hash_param;
			}
		}
		else
		{
			free(new_hash_table);
			new_hash_table = NULL;
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
	int bin_index = -1;
	
	dlist_ty *dlist = NULL;
	
	dlist_iter_ty ret_status;
	
	/*	assert*/
	assert(hash_table);
	assert(data);	/* NULL data is not allowed in tis hash table	*/
	
	/*	use hash func to get the right index to insert data into*/
	bin_index = GetBinOfKeyIMP(hash_table, data);
	
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
	dlist_ty **curr_list = NULL, **end_of_list = NULL;
	size_t total_size = 0;
	
	/*	assert */
	assert(hash_table);
	
	/*	loop on each index in the hash table and check for dlist size using*/
	/*	dlist size func*/
	curr_list = hash_table->items;	/*	first list	*/
	end_of_list = hash_table->items + hash_table->capacity;
	
	while (curr_list < end_of_list)
	{
		total_size += DlistSize(*curr_list);
		++curr_list;
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
	int bin_index = -1;
	
	dlist_iter_ty item_to_find;
	
	dlist_ty *dlist = NULL;
	
	/*	asserts	*/
	assert(hash_table);
	assert(key);
	
	/*	use hash func to get right index of the right dlist */
	bin_index = GetBinOfKeyIMP(hash_table, key);
	
	dlist = *(hash_table->items + bin_index);
	
	item_to_find = FindItemIMP(hash_table, key, dlist);
										
	/*	remove on the iterator that recieved from the FindIMP func	*/
	if (!DlistIteratorIsEqual(DlistIteratorEnd(dlist), item_to_find))
	{
		return (DlistGetData(item_to_find));
	}
	
	return (NULL);
}
/******************************************************************************/
void HTRemove(ht_ty *hash_table, const void *key)
{
	int bin_index = -1;
	
	dlist_iter_ty item_to_remove;
	
	dlist_ty *dlist = NULL;
	
	/*	asserts	*/
	assert(hash_table);
	assert(key);
	
	/*	use hash func to get right index of the right dlist */
	bin_index = GetBinOfKeyIMP(hash_table, key);
	
	dlist = *(hash_table->items + bin_index);
	
	item_to_remove = FindItemIMP(hash_table, key, dlist);
										
	/*	remove on the iterator that recieved from the FindIMP func	*/
	if (!DlistIteratorIsEqual(DlistIteratorEnd(dlist), item_to_remove))
	{
		DlistRemove(item_to_remove);
	}
}
/******************************************************************************/
statistics_ty HTGetStatistics(const ht_ty *hash_table)
{
	statistics_ty ret_stats = {0};
	
	dlist_ty **curr_list = NULL, **end_of_list = NULL;
	
	size_t *lists_sizes = NULL, *curr_list_size = NULL;
	size_t hash_table_size = 0;
	
	/*	assert */
	assert(hash_table);
	
	hash_table_size = hash_table->capacity;
	
	lists_sizes = (size_t *)malloc(sizeof(size_t) * hash_table_size);
	if (!lists_sizes)
	{
		return (ret_stats);
	}
	
	curr_list_size = lists_sizes;
	
	/*	loop on each index in the hash table and check for dlist size using*/
	/*	dlist size func*/
	curr_list = hash_table->items;	/*	first list	*/
	end_of_list = hash_table->items + hash_table_size;
	
	while (curr_list < end_of_list)
	{
		*(curr_list_size) = DlistSize(*curr_list);
		++curr_list;
		++curr_list_size;
	}
	
	qsort(lists_sizes, hash_table_size, sizeof(size_t), CompareListsLengthIMP);
	
	if (0 == (hash_table_size + 1) % 2)
	{
		ret_stats.median_list = *(lists_sizes + (hash_table_size + 1) / 2);
	}
	else
	{
		ret_stats.median_list = *(lists_sizes + hash_table_size / 2);
	}
	
	ret_stats.longest_list = *(lists_sizes + hash_table_size - 1);
	
	free(lists_sizes);
	
	return (ret_stats);
}
/******************************************************************************/
int CompareListsLengthIMP(const void *length1, const void *length2)
{
	assert(length1);
	assert(length2);
	
	return (*(int *)length1 - *(int *)length2);
}
/******************************************************************************/
dlist_iter_ty FindItemIMP(ht_ty *hash_table, const void *key_to_find, 
																dlist_ty *list)
{
	dlist_iter_ty ret_iter;
	
	dlist_ty *dlist = NULL;
	
	extended_param_ty extended_param = {0};
	
	assert(hash_table);
	assert(key_to_find);
	assert(list);
	
	extended_param.hash_table = hash_table;
	
	extended_param.key = key_to_find;
	
	dlist = list;
	
	/*	 use find function of dlist */
	ret_iter = DlistFind(DlistIteratorBegin(dlist), DlistIteratorEnd(dlist), 
										CompareKeysIMP, &extended_param);
										
	if (DlistIteratorIsEqual(ret_iter, DlistIteratorEnd(dlist)))
	{
		return (DlistIteratorEnd(dlist));
	}
										
	return (ret_iter);
}
/******************************************************************************/
static int CreateListsArrayIMP(dlist_ty **lists, size_t size)
{
	dlist_ty **start_list = NULL;
	dlist_ty **curr_list = NULL;
	dlist_ty **end_list = NULL;
	
	assert(lists);
	assert(size);
	
	start_list = lists;
	curr_list = start_list;
	end_list = lists + size;
	
	/* 	loop through the lists array and create a new list at every element
	 *	of the array. handle creation errors if any		*/
	while (curr_list < end_list)
	{
		*curr_list = DlistCreate();
		
		if (!curr_list)
		{
			/*	destroy any list (if any) which was created till now */	
			while (start_list < curr_list)
			{
				DlistDestroy(*start_list);
				++start_list;
			}
			break;
		}
		
		++curr_list;
	}
	
	/*	if start list equals curr list, it means a memory error has occured
	 *	while creating the lists */
	return (start_list == curr_list);
}
/******************************************************************************/
int GetBinOfKeyIMP(ht_ty *hash_table, const void *key_to_find)
{
	assert(hash_table);
	assert(key_to_find);
	
	return (hash_table->hash_func(key_to_find, hash_table->hash_param) %
														hash_table->capacity);
}

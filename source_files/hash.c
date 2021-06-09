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
ht_ty *HTCreate(size_t capacity, hash_func_ty hash_func, is_same_key_ty is_same_func, const void *hash_param)
{
	/*	asserts for parameters*/

	/*	allocate memory for hash map structure & handle memory errors if any*/

	/*	create and allocate memory for an array of */
	/*	dlists of size of capacity,*/
	/*	and assign to the struct member, handle memory errors if any.*/
	
	/* loop on the array and create dlist at each index				*/

	/*	assign rest of the parameters to the corrosponding struct members*/

	/*	return created hash map*/
}
/******************************************************************************/
void HTDestroy(ht_ty *hash_table)
{
	/*	loop through the map and destory dlist at each index*/

	/*	free the hash map*/
}
/******************************************************************************/
int HTInsert(ht_ty *hash_table, void *data)
{
	/*	assert*/

	/*	use hash func to get the right index to insert data into*/

	/*	go to that index in the dlists array*/

	/*	use the insert func of dlist to insert the data*/

	/*	return status of inserttion*/
}
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

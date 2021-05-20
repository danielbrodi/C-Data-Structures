/**********************************FILE-HEADER*********************************\
* File: slist_ex.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 24/03/2021							   								
* Version: 1.0 (After Review)						   								
* Reviewer: Olga							   								
* Description: Single Linked List Advanced Functions Implementations.			 
\******************************************************************************/

/****************************** Inclusions ************************************/
#include <assert.h>	/*	assert	*/
#include <stddef.h> /* 	NULL 	*/


#include "slist_ex.h"

/************************Functions Implementations*****************************/

/******************************************************************************/
node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *current = head;
	node_t *next = NULL;
	
	assert(head);
	
	while (NULL != current)
	{
/*		Store next*/
		next = current->next;

/*		 Reverse current node's pointer*/
		current->next = prev;

		/* Move pointers one position ahead. */
		prev = current;
		current = next;
	}
	
	return(prev);
}
/******************************************************************************/
int HasLoop(const node_t *head)
{
	const node_t *runner = head;
	const node_t *runner2 = NULL;
	
	assert(head);
	
	runner2 = head->next;
	
	while(NULL != runner2 && NULL != runner2->next)
	{
		if(runner == runner2)
		{
			return(1);
		}
		
		runner = runner->next;
		runner2 = runner2->next->next;
	}
	
	return(0); /* there is no loop */
}
/******************************************************************************/	
node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	node_t *list1_runner = head_1;
	node_t *list2_runner = head_2;

	assert(head_1);
	assert(head_2);

	while(NULL != list1_runner)
	{
		while(NULL != list2_runner)
		{
			if(list1_runner == list2_runner)
			{
				return(list1_runner);
			}
			list2_runner = list2_runner->next;
		}
		list1_runner = list1_runner->next;
		list2_runner = head_2;
	}
	
	return(NULL);
}
/******************************************************************************/

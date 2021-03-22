/**********************************FILE-HEADER*********************************\
* File: slist_ex.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 23/03/2021							   								
* Version: 1.0 (Before Review)						   								
* Reviewer: Olga							   								
* Description: Single Linked List Advanced Functions Implementations.			 
\******************************************************************************/

/********************************** Inclusions ********************************/

#include "slist_ex.h"

/******************************* Global Definitions ***************************/
struct node;
{
	void *data;
	struct node *next;
};

/************************Functions Implementations*****************************/
/******************************************************************************/

/* Reverses the order of a given slist. */
/* pseudo code */
node_t *Flip(node_t *head)
{

	runner = list->head;
	next1 = list>head;
	next2 = list->head->next;
	
	/* stop when reach last node */
	while(NULL != next2)
	{
		next1 = next2;
		next2 = next2->next;
		next1->next = runner;
		runner=next1;
	}
	
	list->head->next = NULL;
	
	return(runner);
}


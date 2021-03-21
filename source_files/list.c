/**********************************FILE-HEADER*********************************\
* File: list.c						 		  								
* Author: Daniel Brodsky					  								
* Date: 21/03/2021							   								
* Version: Beta 							   								
* Reviewer: Olga							   								
* Description: Single Linked List API's Functions Implementations.			 
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, realloc, free */
#include <assert.h> /* assert */

#include "../include/list.h"

/******************************* Global Definitions ***************************/
struct slist
{
	slist_node_ty *head;
	slist_node_ty *tail;
};

struct slist_node
{
	void *data;
	slist_node_ty *next;
};

/************************Functions Implementations*****************************/

/******************************************************************************/

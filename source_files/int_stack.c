/****************************** File Header ***********************************\
* File Name:  int_stack.c
* Author: Daniel Brodsky
* Description: 	Quiz - Implementation of a INT stack's data structure functions.
* Date: 29/03/2021
* Version: 2.0
\******************************************************************************/

/********************************** Inclusions ********************************/

#include <stdio.h> 	/* fprintf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "stack.h"
#include "int_stack.h"

/******************************* Globals & Statics ****************************/

struct int_stack
{
	stack_ty *stack;
};

/***********************************FUNCTIONS**********************************/
/******************************************************************************/
int_stack_ty *IntStackCreate(size_t capacity)
{
	int_stack_ty *new_stack = (int_stack_ty *)malloc(sizeof(int_stack_ty));
	if (NULL == new_stack)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}
	
	new_stack->stack = CreateStack(capacity);
	if (NULL == new_stack->stack)
	{
		fprintf(stderr, "Memory allocation failed\n");
		free(new_stack);
		return NULL;
	}
	
	return (new_stack);
}
/******************************************************************************/
int IntStackPop(int_stack_ty *int_stack)
{
	int ret = 0;
	
	assert(int_stack);
	
	ret = (int)(long)Peek(int_stack->stack);
	
	Pop(int_stack->stack);
	
	return (ret);
}
/******************************************************************************/
void IntStackPush(int_stack_ty *int_stack, int element)
{
	assert(int_stack);
	
	Push(int_stack->stack, (void *)(long)element);
}
/******************************************************************************/
int IntStackPeek(int_stack_ty *int_stack)
{	
	assert(int_stack);
	
	return((int)(long)Peek(int_stack->stack));
}
/******************************************************************************/
int IntStackIsEmpty(const int_stack_ty *int_stack)
{
	assert(int_stack);
	
	return(IsEmpty(int_stack->stack));
}
/******************************************************************************/

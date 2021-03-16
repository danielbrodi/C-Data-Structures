/****************************** File Header ***********************************\
* File Name:  stack.c
* Author: Daniel Brodsky
* Description: 	Implementation of a stack's data structure functions.
* Date: 16/03/2021
* Version: 1.0 (Before Review)
* Reviewer: Danel
\******************************************************************************/

/********************************** Inclusions ********************************/
#include <stdio.h> /* fprintf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "../include/stack.h"

/******************************* Globals & Statics ****************************/
struct stack
{
	void **items;
	size_t top;      
	size_t max_size;
};

/*******************************************************************************
 * Function: CreateStack
 * ----------------------------
 *  Creates a fixed size stack of elements.
 *
 *	@capicty - the desired size of the stack
 *
 *  returns: *new_stack or NULL if allocation failed
 */
stack_ty *CreateStack(size_t capacity)
{
	stack_ty *new_stack = (stack_ty *)malloc(sizeof(stack_ty));
	if (NULL == new_stack)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return (NULL);
	}
	
	assert(capacity > 0);
	
	new_stack->max_size = capacity;
	new_stack->top = -1;
	
	new_stack->items = malloc(sizeof(void *) * capacity);
	if (NULL == new_stack->items)
	{
		fprintf(stderr, "Failed to allocate memory\n");
		return (NULL);
	}

	return (new_stack);
}

/*******************************************************************************
 * Function: IsEmpty
 * ----------------------------
 *  Checks if the stack is empty
 *
 *   returns: boolean_ty 1 or 0 
 */
boolean_ty IsEmpty(const stack_ty *stack)
{
	assert(stack);
	
	return ((stack->top == -1UL));
}

/*******************************************************************************
 * Function: Pop
 * ----------------------------
 * Removes top element 		
   undefined if the stack is empty.
 */
void Pop(stack_ty *stack)
{
	assert(stack);
	assert(!IsEmpty(stack));
	
	stack->items[stack->top--];
}

/*******************************************************************************
 * Function: Peek
 * ----------------------------
 *  Returns the top element of the stack
 *
 *   returns: (void *) that points to the top element. 
 */
void *Peek(const stack_ty *stack)
{
	assert(stack);
	assert(!IsEmpty(stack));
	
	return(stack->items[stack->top]);
}

/*******************************************************************************
 * Function: Push
 * ----------------------------
 *  Push element to the top of the stack
 	undefined if the stack is full
 *
 *   returns: void 
 */
void Push(stack_ty *stack, void *element)
{
	size_t is_full = (0 != ((stack->max_size) - ((stack->top)+1)));
	assert(stack);
	assert(is_full);
	
	stack->items[++stack->top] = element;
}

/*******************************************************************************
 * Function: GetStackSize
 * ----------------------------
 *  Returns the used space in the size.
 *
 *   returns: size_t the used space 
 */
size_t GetStackSize(const stack_ty *stack)
{
	assert(stack);
	
	return (stack -> top + 1);
}

/*******************************************************************************
 * Function: Capacity
 * ----------------------------
 *  Returns the capacity (max_size) of stack
 *
 *   returns: size_t the capicty of the stack 
 */
size_t Capacity(const stack_ty *stack)
{
	assert(stack);
	
	return (stack->max_size);
}

/*******************************************************************************
 * Function: DestroyStack
 * ----------------------------
 *  Deletes the stack
 *
 *   returns: void 
 */
void DestroyStack(stack_ty *stack)
{
	assert(stack);
	
	free(stack);
}

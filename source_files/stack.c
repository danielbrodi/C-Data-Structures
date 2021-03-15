#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "../include/stack.h"

struct stack
{
	void **items;
	size_t top;      
	size_t max_size;
};


stack_ty *CreateStack(size_t capacity)
{
	stack_ty *new_stack = (stack_ty *)malloc(sizeof(stack_ty));
	new_stack->max_size = capacity;
	new_stack->top = -1;
	new_stack->items = malloc(sizeof(void *) * capacity);

	return (new_stack);
}

boolean_ty IsEmpty(const stack_ty *stack)
{
	return ((stack->top == -1UL));
}

void Pop(stack_ty *stack)
{
	assert(0 == IsEmpty(stack));
	
	stack->items[stack->top--];
}

void *Peek(const stack_ty *stack)
{
	printf("%d", *(int *)stack->items[stack->top]);
}

void Push(stack_ty *stack, void *element)
{
	assert(0 == IsEmpty(stack));
	
	*(size_t *)stack->items[++stack->top] = *(size_t *)element;
}

size_t GetStackSize(const stack_ty *stack)
{
	return ((stack->max_size) - ((stack->top)+1));
}


size_t Capacity(const stack_ty *stack)
{
	return (stack->max_size);
}

void DestroyStack(stack_ty *stack)
{
	free(stack);
}

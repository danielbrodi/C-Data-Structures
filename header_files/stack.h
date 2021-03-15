#ifndef	__STACK_H__
#define	__STACK_H__

#include <stddef.h>	/* size_t */

typedef enum
{
	FALSE,
	TRUE
} boolean_ty;

typedef enum
{
	FAILURE,
	SUCCESS
} status_ty;

typedef struct stack stack_ty;

/* Creates stack of elements with stack size */
stack_ty *CreateStack(size_t capacity);

/* Removes top element - undefined if the stack is empty */
void Pop(stack_ty *stack);

/* Returns the top element */
void *Peek(const stack_ty *stack);

/* Push element to the top of the stack - undefined if the stack is full */
void Push(stack_ty *stack, void *element);

/* Returns Stack size */
size_t GetStackSize(const stack_ty *stack);

/* Checks if the stack is empty */
boolean_ty IsEmpty(const stack_ty *stack);

/* Returns the capacity (max_size) of stack */
size_t Capacity(const stack_ty *stack);

/* Delete the stack */
void DestroyStack(stack_ty *stack);

#endif	/* __STACK_H__ */

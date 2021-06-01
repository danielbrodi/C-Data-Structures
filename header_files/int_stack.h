/****************************** File Header ***********************************\
* File Name: int_stack.h
* Author: Daniel Brodsky
* Description: 	Quiz - API of Stack of only INTs. 
* Date: 29/03/2021
* Version: 1.0
\******************************************************************************/

#ifndef __INT_STACK_H__ 
#define __INT_STACK_H__ 

typedef struct int_stack int_stack_ty;

/* Creates stack of int elements with stack capacity of 'capacity'. */
/* Capacity should be above 0. */
/* On failure, returns NULL. */
/* Complexity: O(1) */
int_stack_ty *IntStackCreate(size_t capacity);

/* Removes top element. */
/* Undefined behaviour if the stack is empty */
/* Complexity: O(1) */
int IntStackPop(int_stack_ty *int_stack);

/* Push int element to the top of the stack. */
/* Undefined behaviour if the stack is full */
/* Complexity: O(1) */
void IntStackPush(int_stack_ty *int_stack, int element);

/* Returns the top element of int stack */
int IntStackPeek(int_stack_ty *int_stack);

/* Checks if the Int Stack is empty */
int IntStackIsEmpty(const int_stack_ty *int_stack);

#endif /* __INT_STACK_H__ */

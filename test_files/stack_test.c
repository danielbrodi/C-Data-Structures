/****************************** File Header ***********************************\
* File Name:  stack_test.c
* Author: Daniel Brodsky
* Description: 	Tests of a stack's data structure functions.
* Date: 16/03/2021
* Version: 1.0 (Before Review)
* Reviewer: Danel
\******************************************************************************/

/********************************** Inclusions ********************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* free */

#include "../include/stack.h"

/******************************* Main Function ********************************/

int main()
{
    stack_ty *new_stack = CreateStack(5);
 
    Push(new_stack, (void *)1);
    Push(new_stack, (void *)2);
    Push(new_stack, (void *)8);
 
    printf("The top element is %ld\n", (size_t)Peek(new_stack));
    printf("Used space on the stack: %ld\n", GetStackSize(new_stack));
 
    Pop(new_stack);
    Pop(new_stack);
    Pop(new_stack);
    
    if (IsEmpty(new_stack)) {
        printf("The stack is empty\n");
    }
    else {
        printf("The stack is not empty\n");
    }
    
    free(new_stack);
 
    return 0;
}

/*********************************FILE__HEADER*********************************\
* File: 	mem_map.c						 		  								
* Author: 	Daniel Brodsky					  								
* Date: 	02/05/2021						   								
* Version:	1.0			   											   								
* Purpose:	Draw a memory map of different types, print their addresses to
			define in which memory segments they are located.				 
\******************************************************************************/

/******************************** HEADER_FILES ********************************/

#include <assert.h>	/*	assert									*/

#include <stdio.h>	/*	printf									*/	

/***************************** Macros Definitions *****************************/
/* escape keys for colored output */
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

/******************************************************************************/

int global_init = 100;
int global_not_init;

void PrintMemAddress(char *string, void *address);

static char global_static_init = 100;
static int global_static_not_init;

/******************************************************************************/

int main()
{
	static long local_static_init = 200;
	static char local_static_not_init;
	
	int local_init = 3;
	int local_not_init;
	
	printf("\n");
	
	PrintMemAddress("initialized global", (void*) &global_init);
	PrintMemAddress("uninitialized global", (void*) &global_not_init);
	printf("\n");
	
	PrintMemAddress("initialized global static", (void*) &global_static_init);
	PrintMemAddress("uninitialized global static", (void*) &global_static_not_init);
	printf("\n");
	
	PrintMemAddress("initialized local static", (void*) &local_static_init);
	PrintMemAddress("uninitialized local static", (void*) &local_static_not_init);
	printf("\n");
	
	PrintMemAddress("initialized local", (void*) &local_init);
	PrintMemAddress("uninitialized local", (void*) &local_not_init);
	printf("\n");
	
	return (0);
}

/******************************************************************************/
void PrintMemAddress(char *string, void *address)
{
	assert(string);
	assert(address);
	
	printf ("The memory address of an " GREEN "%s variable " RESET
	 								"is: " CYAN "%p\n" RESET, string, address);
}
/******************************************************************************/

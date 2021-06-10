/*********************************FILE__HEADER*********************************\
* File:				hash.c						 		  								
* Author:			Daniel Brodsky					  								
* Date:				09-06-2021
* Code Reviewer:							   								
* Version:			1.0					   								
* Description:		Hash Map implementation tests file.		 
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <stddef.h>	/*	size_t						*/
#include <stdio.h>	/*	printf						*/
#include <stdlib.h>	/*	rand, srand					*/
#include <time.h>	/*	time						*/

#include "../include/utils.h"	/*	PRINT_COLOR, COLOR			*/
#include "../include/hash.h"

/***************************** Macros Definitions *****************************/

#define DICTIONARY_PATH ("/usr/share/dict/words")

/* generates random number from -99 to 99 			*/
#define RANDOM_NUM ((rand() % 200 - 100))	

/**************************** Forward Declarations ****************************/



/******************************************************************************/
/******************************* Main__Function *******************************/

int main ()
{
    FILE *dictionary = fopen(DICTIONARY_PATH, "r");
    
    size_t i = 0, dict_size = 0;
    char *dict_arr = NULL;
    
    fseek(dictionary, 0, SEEK_END); /* move ptr to end of dict	*/ 
    
    dict_size = ftell(dictionary);
    
    printf("%ld", dict_size);
    
    fseek(dictionary, 0, SEEK_SET); /* move ptr to beginning of dict	*/ 
    
    dict_arr = (char *)malloc(sizeof(char) * dict_size);
    
    
    while (i < 100)
    {
    	*dict_arr++ = fgetc(dictionary);
    	++i;
    }
    
    fclose(dictionary);
    
    i = 0;
    
    dict_arr -= 100;
    
    while (i < 100)
    {
    	printf("%c,",*(dict_arr+i));
    	++i;
    }
    
    printf("\n\n");
    
    return(0);
}

/******************************************************************************/

/*CreateDict: */

/*open words file (linux dictionary)*/
/*get the number of total characters in the file*/
/*create a char array of size of that number*/
/*allocate a dynamic array of char * to store ptrs to the beginning of each word*/
/*simultaneously go through both arrays:*/
/*	for each words: store first char in the char * array*/
/*					change "\n" in the original array to "\0"*/

/******************************************************************************/

/*size_t hash(const void *str, const void *param)*/
/*{*/
/*	void(param);*/
/*	*/
/*    size_t hash = 5381;*/
/*    int c = 0;*/

/*    while (c = *str++)*/
/*        hash = ((hash << 5) + hash) + c; */

/*    return (hash);*/
/*}*/

/******************************************************************************/
/* Create HashTable for dict 	*/
/*create a hash table of the size of the words array + 10%*/


/*********************************FILE__HEADER*********************************\
* File:				hash.c						 		  								
* Author:			Daniel Brodsky					  								
* Date:				09-06-2021
* Code Reviewer:							   								
* Version:			1.0					   								
* Description:		Hash Map implementation tests file.		 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>
#include <stdio.h>	/* printf	*/
#include <stdlib.h>	/*	malloc, free, realloc 	*/
#include <string.h>	/* strlen	*/

#include "utils.h"
#include "hash.h"

/******************************* Macros & enums *******************************/

#define DICTIONARY_PATH ("/usr/share/dict/words")

/**************************** Structs  Definitions ****************************/

/* dynamic dictionary */
typedef struct dictionary
{
    size_t size;
    size_t reserved;
    char** words;
}dictionary_ty;
/******************************************************************************/

/* creates a dictionary_ty */
dictionary_ty* DictionaryCreate();

/* destroy a store */
void DictionaryDestroy(dictionary_ty* dict);

/* reserve more space for the characters if needed */
int DictionaryResize(dictionary_ty* dict, size_t new_res);

/* change 5/4 to a larger value for more aggressive
 * increase of memory allocation */
int DictionaryIsFull(dictionary_ty* dict);

/* adds a character to the dictionary_ty */
int DictionaryAddTo(dictionary_ty* dict, char* word_to_add);

/*	converts text file which contains chars to an array of words(strings)	*/
void TextFileToArray(dictionary_ty* dict, char *file_path, char** chars_array);

void HTCreateTest(ht_ty * hasht);

size_t hash_func(const void *data, const void *param);

int is_same_key(const void *data1, const void *data2);
/******************************* Main__Function *******************************/
int main() 
{
	char *chars_array = NULL;
	
	size_t i = 0;
	
	ht_ty *hash_table = NULL;
	
	dictionary_ty* dict = DictionaryCreate();
	if (!dict)
	{
		return (1);
	}
    
    TextFileToArray(dict, DICTIONARY_PATH, &chars_array);
	
	hash_table = HTCreate(dict->size * 1.1, hash_func, 0, is_same_key);
	
	HTCreateTest(hash_table);
	
	printf("SIZE OF HASH TABLE BEFORE INSERTS: %ld\n\n" ,HTSize(hash_table));
		
	for(i = 0; i < dict->size; ++i)
    {
        printf("%ld: %s\n", i, dict->words[i]);
    }
	
	i = 0;

	while (i < dict->size)
	{
		HTInsert(hash_table, dict->words[i]);
		++i;
	}
	
	HTInsert(hash_table, "Daniel");
	
	printf("\nSIZE OF HASH TABLE AFTER 10 INSERTS: %ld\n\n" ,HTSize(hash_table));
	
	i = 0;
	
	while (i < dict->size)
	{
		printf("%ld: %s\n", i, (char *)HTFind(hash_table, "Daniel"));
		++i;
	}
	
	HTRemove(hash_table, "Daniel");
	
	i = 0;
	
	printf("DANIEL REMOVED\n");
	while (i < dict->size)
	{
		HTFind(hash_table, "Daniel") ? printf("FOUND\n") : printf( "NOT FOUND\n");
		++i;
	}
	
	printf("\nSIZE OF HASH TABLE AFTER 1 REMOVE: %ld\n\n" ,HTSize(hash_table));
	
    DictionaryDestroy(dict);
    
    free(chars_array);
    
    HTDestroy(hash_table);
    
    return (0);
}	
/******************************************************************************/
void HTCreateTest(ht_ty * hasht)
{
	hasht ? PRINT_SUCCESS : PRINT_FAILURE;
}

dictionary_ty* DictionaryCreate() 
{
    dictionary_ty* dict = malloc(sizeof(dictionary_ty));

    if (dict) 
    {
        /* initialize values */
        dict->size = 0;
        dict->reserved = 1;
        dict->words = malloc(sizeof(char*) * dict->reserved);
        if (!dict->words) 
        {
            free(dict);
            dict = NULL;
        }
    }
    
    return (dict);
}
/******************************************************************************/
void DictionaryDestroy(dictionary_ty* dict) 
{
    /* free the words array */
    free(dict->words);
    
    /* free the dictionary struct */
    free(dict);
}
/******************************************************************************/
int DictionaryAddTo(dictionary_ty* dict, char* word_to_add)
{
    if (DictionaryIsFull(dict)) 
    {
    	return (1);
	}
	
    dict->words[dict->size++] = word_to_add;
    
    return (0);
}
/******************************************************************************/
void TextFileToArray(dictionary_ty* dict, char *file_path, char** chars_array) 
{

	size_t i = 0, num_of_chars = 0;
	
	int character = 0;
    
	char *char_arr_runner = NULL;
    
	FILE *text_file = fopen((char *)file_path, "r");
    
    fseek(text_file, 0, SEEK_END); /* move ptr to end of dict	 */
    
    num_of_chars = ftell(text_file);
    
	*chars_array = malloc(sizeof(char) * num_of_chars);

    char_arr_runner = *chars_array;
    
    printf("\nDictionary Size:%ld\n", num_of_chars);
    
    fseek(text_file, 0, SEEK_SET); /* move ptr to beginning of dict	 */

    DictionaryAddTo(dict, (char_arr_runner));
    
	while (i < 50)
    {
    	character = fgetc(text_file);
    	
    	if (character == EOF)
    	{
    		break;
    	}
    	
    	if (character == '\n')
    	{
    		*char_arr_runner =  '\0';
    		DictionaryAddTo(dict, (char_arr_runner + 1));	
    	}
    	
    	else
    	{
    		*char_arr_runner = character;
    	}

    	++char_arr_runner;
    	++i;
    }
    
    fclose(text_file);
}
/******************************************************************************/
int DictionaryResize(dictionary_ty* dict, size_t new_res) 
{
	char **temp = NULL;
	
    /* reserve more space for the chars if needed */
    if (new_res > dict->reserved)
     {
        temp = realloc(dict->words, sizeof(char*) * new_res);
        if (!temp)
        {
        	return (1); /* memory allocation failure */
        } 
        dict->reserved = new_res;
        dict->words = temp;
    }
    
    return (0);
}
/******************************************************************************/
int DictionaryIsFull(dictionary_ty* dict)
{
    if (dict->size == dict->reserved)
    {
        /* change 5/4 to a larger value for more aggressive
         * increase of memory allocation */
        return (DictionaryResize(dict, (dict->reserved+1) * 5 / 4));
	}
    else
    {
        return (0);
    }
    
   return (1);
}
/******************************************************************************/
size_t hash_func(const void *string, const void *param)
{
    int c = 0;
    size_t hash = 5381;
    
    char *string_runner = NULL;
    
    assert(string);
    
	UNUSED(param);
	
	string_runner = (char *)string;
	
    while (*string_runner )
    {
    	c = *string_runner;
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		++string_runner;
	}
	
    return (hash);
}
/******************************************************************************/
int is_same_key(const void *data1, const void *data2)
{
	const char *string1 = (char *)data1;
	const char *string2 = (char *)data2;
	return (strcmp(string1, string2) == 0);
}
/******************************************************************************/

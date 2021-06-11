/*********************************FILE__HEADER*********************************\
* File:				hash.c						 		  								
* Author:			Daniel Brodsky					  								
* Date:				09-06-2021
* Code Reviewer:							   								
* Version:			1.0					   								
* Description:		Hash Map implementation tests file.		 
\******************************************************************************/

/********************************* Inclusions *********************************/

#include <stdio.h>	/* printf	*/
#include <stdlib.h>	/*	malloc, free, realloc 	*/

/******************************* Macros & enums *******************************/

#define DICTIONARY_PATH ("/usr/share/dict/words")

/**************************** Structs  Definitions ****************************/

/* dynamic memory storage - dictionary */
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

void CharsToWords(dictionary_ty* dict, char* file_path, char **characters_arr);

void TextFileToArray(char *file_path, char **input_arr);

/******************************* Main__Function *******************************/

int main() 
{
	char *characters;
	
	size_t i = 0;
	
	dictionary_ty* dict = DictionaryCreate();
	if (!dict)
	{
		return(1);
	}
    
/*    TextFileToArray(DICTIONARY_PATH, &characters);*/
    
    CharsToWords(dict, DICTIONARY_PATH, &characters);
    
    for(i = 0; i < dict->size; ++i)
    {
        printf("%ld: %s\n", i, dict->words[i]);
    }

	free(characters);	
	
    DictionaryDestroy(dict);
    
    return(0);
}	

/******************************************************************************/

/*void TextFileToArray(char *file_path, char **input_arr)*/
/*{*/
/*	size_t i = 0, num_of_chars = 0;*/
/*	*/
/*	int character = 0;*/
/*    */
/*	FILE *text_file = fopen((char *)file_path, "r");*/
/*    */
/*    fseek(text_file, 0, SEEK_END);  move ptr to end of dict	 */
/*    */
/*    num_of_chars = ftell(text_file);*/
/*    */
/*    printf("\nDictionary SIZE:%ld\n", num_of_chars);*/
/*    */
/*    fseek(text_file, 0, SEEK_SET);  move ptr to beginning of dict	 */
/*    */
/*    *input_arr = (char *)malloc(sizeof(char) * num_of_chars);*/
/*    */
/*    while (i < 200)*/
/*    {*/
/*    	character = fgetc(text_file);*/
/*    	*/
/*    	if (character == EOF)*/
/*    	{*/
/*    		break;*/
/*    	}*/
/*    	*/
/*    	*(*input_arr + i) = character;*/
/*    	++i;*/
/*    }*/
/*}*/
/******************************************************************************/
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
void CharsToWords(dictionary_ty* dict, char *file_path, char** chars_array) 
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
    
	while (i < 100)
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
    
    char_arr_runner = *chars_array;
    i = 0;
    printf("\nSECOND LOOP:\n");
     while (i < 50)
    {
    	if (*char_arr_runner == '\0')
    	{
    		printf("\n");
    	}
    	else
    	{
    		printf("%c", *char_arr_runner);
    	}
    	++char_arr_runner;
    	++i;
    }
    printf("\n");
}
/******************************************************************************/

/*********************************FILE__HEADER*********************************\
* File:				hash.c						 		  								
* Author:			Daniel Brodsky					  								
* Date:				09-06-2021
* Code Reviewer:	Ariel White						   								
* Version:			1.0					   								
* Description:		Hash Map implementation tests file.		 
\******************************************************************************/

/********************************* Inclusions *********************************/
#include <assert.h>
#include <stdio.h>		/*	printf					*/
#include <stdlib.h>		/*	malloc, free, realloc 	*/
#include <string.h>		/* 	strlen, strcmp			*/

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

/* destroys a dictionary */
void DictionaryDestroy(dictionary_ty* dict);

/* reserve more space for the characters if needed */
int DictionaryResize(dictionary_ty* dict, size_t new_res);

/* returns 1 if dictionary is full, otherwise 0. */
int DictionaryIsFull(dictionary_ty* dict);

/*	adds a word to a dictionary */
int DictionaryAddTo(dictionary_ty* dict, char* word_to_add);

/*	converts a text file to an array of words (strings)
 *	also adds each character from the file to an array of characters */
void TextFileToArray(dictionary_ty* dict, char *file_path, char** chars_array);

/*	creates a hash table of words that are taken out of a dictionary	*/ 
static void HashTableFromStringsArr(ht_ty *hash_table, dictionary_ty *dict);

/*	hash function that takes strings and returns an index	*/
size_t hash_func(const void *data, const void *param);

/*	checks if 2 given data keys are equal */
int is_same_key(const void *data1, const void *data2);

/*	runs menu of the dictionary program	*/
static void RunMenu(ht_ty *hash_table);

/*	prints stats of the dictionary	*/
static void PrintStats(ht_ty *hash_table);

/*	removes a word from the dictionary */
static void RemoveFromDict(ht_ty *hash_table);

/*	prints the size of a hash table	*/
static void PrintSize(ht_ty *hash_table);
/******************************* Main__Function *******************************/
int main() 
{
	char *chars_array = NULL;
	
	ht_ty *dictionary_hash_table = NULL;
	
	dictionary_ty* dict = DictionaryCreate();
	if (!dict)
	{
		return (1);
	}
    
    /*	creates a dictionary data structure based on linux's dictionary	*/
    TextFileToArray(dict, DICTIONARY_PATH, &chars_array);
	
	/*	creates a hash table based on the dictionary	*/
	dictionary_hash_table = HTCreate(dict->size, hash_func, 0, is_same_key);
	if (!dictionary_hash_table)
	{
		free(dict);
		dict = NULL;
		
		free(chars_array);
		
		return (1);
	}
	
	/*	inserts all the words from the dictionary to the hash table	*/
	HashTableFromStringsArr(dictionary_hash_table, dict);
	
	/* run program of the dictionary	*/
	RunMenu(dictionary_hash_table);
	
	/* close program */
	DictionaryDestroy(dict);
	free(chars_array);
	HTDestroy(dictionary_hash_table);
	
	return (0);
}
/******************************************************************************/
void HashTableFromStringsArr(ht_ty *hash_table, dictionary_ty *dict)
{
	char **curr_word = NULL, **last_word = NULL;
	
	size_t size = 0;
	
	assert(hash_table);
	assert(dict);
	
	size = dict->size;
	
	curr_word = dict->words;
	
	last_word = curr_word + size;
	
	while (curr_word < last_word)
	{
		if (HTInsert(hash_table, *curr_word))
		{
			PRINT_FAILURE;
		}
		
		++curr_word;
	}
	
	printf(PURPLE "\nDictionary has been loaded into the memory.\n" RESET_COLOR);
	printf(GREEN "Spell Checker has been succeesfully created.\n\n" RESET_COLOR);
}
/******************************************************************************/
static void RunMenu(ht_ty *hash_table)
{
	char input_word[64] = {0};
	
	int cmdQuit = 0;
	
	printf("%15s\033[47;30mSpell-Checker: MENU\033[0m\n\n", "");
	printf(YELLOW "* Enter \"-size\"" " to see how big is the dictionary.\n");
	printf(YELLOW "* Enter \"-stats\"" " to see the statistics.\n");
	printf(YELLOW "* Enter \"-remove\"" " to remove a word from the dictionary.\n");
	printf(YELLOW "* Enter \"-exit\"" " to exit the program.\n\n" RESET_COLOR);
	
	while(!cmdQuit)
	{
		printf(CYAN "Enter a word: " RESET_COLOR);
		scanf("%s", input_word);

		if (0 == strcmp(input_word, "-exit"))
		{
			cmdQuit = 1;
			continue;
		}
		
		if (0 == strcmp(input_word, "-stats"))
		{
			PrintStats(hash_table);
			continue;
		}
		
		if (0 == strcmp(input_word, "-stats"))
		{
			PrintStats(hash_table);
			continue;
		}
		
		if (0 == strcmp(input_word, "-size"))
		{
			PrintSize(hash_table);
			continue;
		}
		
		if (0 == strcmp(input_word, "-remove"))
		{
			RemoveFromDict(hash_table);
			continue;
		}
		
		else if (strlen(input_word) < 64 && HTFind(hash_table, input_word))
		{
			printf(GREEN "Word \"%s\" is correct.\n\n" RESET_COLOR, input_word);
		} 
		else 
		{
			printf(RED "Word \"%s\" does not exist.\n\n" RESET_COLOR, input_word);
		}
	}
}
/******************************************************************************/
static void RemoveFromDict(ht_ty *hash_table)
{
	char word_to_remove[64] = {0};
	
	assert(hash_table);
	assert(word_to_remove);
	
	printf(PURPLE "Enter a word to remove: " RESET_COLOR);
	scanf("%s", word_to_remove);
	
	if (HTFind(hash_table, word_to_remove))
	{
		HTRemove(hash_table, word_to_remove);
		printf(GREEN "Word \"%s\" was succeesfully" 
		" removed from the dictionary.\n\n" RESET_COLOR, word_to_remove);
	}
	else
	{
	printf(RED "Word \"%s\" was not found.\n\n" RESET_COLOR, word_to_remove);
	}
}
/******************************************************************************/
static void PrintSize(ht_ty *hash_table)
{
	size_t size = 0;
	
	assert(hash_table);
	
	size = HTSize(hash_table);
	
	size ? printf(YELLOW "The dictionary is full of " GREEN "%ld " YELLOW
	 "different words.\n\n" RESET_COLOR, HTSize(hash_table)) : 
	 printf(RED "The dictionary is empty\n\n" RESET_COLOR);
}
/******************************************************************************/
static void PrintStats(ht_ty *hash_table)
{
	statistics_ty stats = {0};
	
	assert(hash_table);
	
	stats = HTGetStatistics(hash_table);
	
	if (stats.longest_list != 0)
	{
		printf(BLUE "Longest list has " GREEN "%ld " BLUE
		 "elements.\n" RESET_COLOR, stats.longest_list);
		printf(BLUE "Median list has " GREEN "%ld " BLUE
		 "elements.\n\n" RESET_COLOR, stats.median_list);
	}
	else
	{
		printf(RED "No statistics are available for now.\n\n" RESET_COLOR);
	}
}
/******************************************************************************/
dictionary_ty* DictionaryCreate() 
{
    dictionary_ty* dict = malloc(sizeof(dictionary_ty));

    if (dict) 
    {
        /* initialize values */
        dict->size = 0;
        dict->reserved = 1;
        dict->words = malloc(sizeof(char *) * dict->reserved);
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
    
	*chars_array = calloc(sizeof(char) , num_of_chars);

    char_arr_runner = *chars_array;
    
    fseek(text_file, 0, SEEK_SET); /* move ptr to beginning of dict	 */
    
    /* add first first char as a word to words array */
    DictionaryAddTo(dict, (char_arr_runner));
    
    /* num_of_chars - 1 because of the one char we already added the first char */
	while (i < num_of_chars - 1)
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
        return (DictionaryResize(dict, (dict->reserved + 1) * 5 / 4));
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
	
    while (*string_runner)
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

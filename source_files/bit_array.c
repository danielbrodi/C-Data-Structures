/****************************** File Header ******************************\
* File Name:  bit_array.c
* Author: Daniel Brodsky
* Description: 	Implementation of a bit array data structure.
* Date: 15/03/2021
* Version: 1.0 (After Review)
* Reviewer: Omer
\***************************************************************************/

/******************************* Inclusions **********************/
#include <assert.h> /* assert */

#include "../include/bit_array.h"

/********************** Macros & Enums Definitions **********************/
#define MASK_ONLY_ONES 0xFFFFFFFFFFFFFFFF
#define NUM_OF_BITS 64
#define ASCII_VALUE_ZERO '0'
#define NULL_TERMINATOR '\0'

typedef enum
{
	NOT_INITIALIZED,
	INITIALIZED
} lut_status_ty;

/********************** Forward Declreations & Globals **********************/
static int bits_lut[256]; /* For 8 bit lookup */

unsigned int CountBitsOn(bitsarr_ty bitarr);

lut_status_ty lut_status = NOT_INITIALIZED;

/******************************* InitLut **********************/

void InitLut()
{
	size_t i = 0;
	
	for (i = 0; i < 256; i++)
	{
		bits_lut[i] = CountBitsOn(i);
	}
}

/******************************* BitArraySetAll **********************/

bitsarr_ty BitArraySetAll(bitsarr_ty bitarr)
{
	bitarr |= ~(0);
	return(bitarr);
}

/******************************* BitArrayResetAll **********************/

bitsarr_ty BitArrayResetAll(bitsarr_ty bitarr)
{
	bitarr = 0;
	return(bitarr);
}

/******************************* BitArrayToString **********************/

char *BitArrayToString(bitsarr_ty bitarr, char *bit_string)
{
	char *str_runner = bit_string;
	size_t bit_number = NUM_OF_BITS;
	size_t mask = 1;
	
	assert(bit_string);
	
	while(bit_number > 0) 
	{
	 	*(str_runner + bit_number - 1) = (bitarr & mask) + ASCII_VALUE_ZERO;
		--bit_number;
		bitarr >>= 1;
	} 
	*(str_runner+NUM_OF_BITS) = NULL_TERMINATOR;
	
	return(bit_string);
}

/******************************* BitArraySetOn **********************/

bitsarr_ty BitArraySetOn(bitsarr_ty bitarr, unsigned int bit_to_turn)
{
	assert(bit_to_turn < NUM_OF_BITS);
	
	bitarr |= (1UL << bit_to_turn);
	return(bitarr);
}

/******************************* BitArraySetOff **********************/

bitsarr_ty BitArraySetOff(bitsarr_ty bitarr, unsigned int bit_to_turn)
{
	assert(bit_to_turn < NUM_OF_BITS);
	
	bitarr &= ~(1UL << bit_to_turn);
	return(bitarr);
}

/******************************* BitArraySetBit **********************/

bitsarr_ty BitArraySetBit(bitsarr_ty bitarr, unsigned int bit_to_set, 
												bit_state_ty new_state)
{
	assert(bit_to_set < NUM_OF_BITS);
	
	bitarr |= (new_state << bit_to_set);
	return(bitarr);
}

/******************************* BitArrayGetVal **********************/

bit_state_ty BitArrayGetVal(bitsarr_ty bitarr, unsigned int bit_to_read)
{
	int bit_status = bitarr & (1UL << bit_to_read);
	
	return(!!bit_status);
}

/******************************* BitArrayFlip **********************/

bitsarr_ty BitArrayFlip(bitsarr_ty bitarr, unsigned int bit_to_flip)
{
	assert(bit_to_flip < NUM_OF_BITS);
	
	bitarr ^= (1UL << bit_to_flip);
	return(bitarr);
}

/******************************* BitArrayMirror **********************/

bitsarr_ty BitArrayMirror(bitsarr_ty bitarr)
{
	size_t curr_bit_index = 0; 	
	bitsarr_ty mirrored_bitarr = 0; 
	
	for (curr_bit_index = 0; curr_bit_index < NUM_OF_BITS; ++curr_bit_index) 
	{ 
		if((bitarr & (1UL << curr_bit_index)))
		{
			mirrored_bitarr |= 1UL << ((NUM_OF_BITS - 1) - curr_bit_index); 
		}  
	} 
	
	return(mirrored_bitarr); 
}
	
/******************************* BitArrayRotR **********************/

bitsarr_ty BitArrayRotR(bitsarr_ty bitarr, unsigned int amount)
{
	size_t curr_bit_index = 0; 	
	bitsarr_ty rotated_bitarr = 0; 
	
	for (curr_bit_index = 0; curr_bit_index < NUM_OF_BITS; ++curr_bit_index) 
	{ 
		if((bitarr & (1UL << curr_bit_index)))
		{
			rotated_bitarr |= 1UL << (curr_bit_index - amount); 
		}  
	} 
	
	return(rotated_bitarr); 
}

/******************************* BitArrayRotL **********************/

bitsarr_ty BitArrayRotL(bitsarr_ty bitarr, unsigned int amount)
{
	size_t curr_bit_index = 0; 	
	bitsarr_ty rotated_bitarr = 0; 
	
	for (curr_bit_index = 0; curr_bit_index < NUM_OF_BITS; ++curr_bit_index) 
	{ 
		if((bitarr & (1UL << curr_bit_index)))
		{
			rotated_bitarr |= 1UL << (curr_bit_index + amount); 
		}  
	} 
	
	return(rotated_bitarr); 
}

/******************************* BitArrayRot **********************/

bitsarr_ty BitArrayRot(bitsarr_ty bitarr, unsigned int amount, 
														rotation_ty direction)
{
	size_t curr_bit_index = 0; 	
	bitsarr_ty rotated_bitarr = 0; 
	
	assert(LEFT == direction || RIGHT == direction);
	
	for (curr_bit_index = 0; curr_bit_index < NUM_OF_BITS; ++curr_bit_index) 
	{ 
		if((bitarr & (1UL << curr_bit_index)))
		{
			if(LEFT == direction)
			{
				rotated_bitarr |= 1UL << (curr_bit_index + amount); 
			}
			else
			{
				rotated_bitarr |= 1UL << (curr_bit_index - amount); 
			}
		}  
	} 
	
	return(rotated_bitarr); 
}

/******************************* BitArrayCountOn **********************/

unsigned int CountBitsOn(bitsarr_ty bitarr)
{
	size_t curr_bit_index = 0;
	size_t set_bits_counter = 0; 
	
	for (curr_bit_index = 0; curr_bit_index < NUM_OF_BITS; ++curr_bit_index) 
	{ 
		set_bits_counter += !!(bitarr & (1UL << curr_bit_index));
		
		bitarr &= ~(1UL << curr_bit_index);
		
		if (0 == bitarr)
		{
			break;
		}
	} 
	
	return(set_bits_counter); 
}

/******************************* BitArrayCountOff **********************/

unsigned int BitArrayCountOff(bitsarr_ty bitarr)
{
	size_t curr_bit_index = 0;
	size_t set_bits_counter = 0; 
	
	for (curr_bit_index = 0; curr_bit_index < NUM_OF_BITS; ++curr_bit_index) 
	{ 
			set_bits_counter += !!(bitarr & (1UL << curr_bit_index));
			 
			bitarr &= ~(1UL << curr_bit_index);
			
			if (0 == bitarr)
			{
				break;
			}
	} 
	
	return(NUM_OF_BITS - set_bits_counter); 
}

/******************************* BitArrayCountLut **********************/
unsigned int BitArrayCountOn(bitsarr_ty bitarr)
{
	unsigned int set_bits_counter = 0;
	
	if (NOT_INITIALIZED == lut_status)
	{
	InitLut();
	lut_status = INITIALIZED;
	}
	
	set_bits_counter = bits_lut[bitarr & 0xff] + 
	bits_lut[(bitarr >> 8) & 0xff] + 
	bits_lut[(bitarr >> 16) & 0xff] +
	bits_lut[(bitarr >> 24) & 0xff] + 
	bits_lut[(bitarr >> 32) & 0xff] + 
	bits_lut[(bitarr >> 40) & 0xff] + 
	bits_lut[(bitarr >> 48) & 0xff] + 
	bits_lut[bitarr >> 56];
	
	return (set_bits_counter);
}

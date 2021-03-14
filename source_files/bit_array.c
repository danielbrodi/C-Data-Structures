/****************************** File Header ******************************\
* File Name:  bit_array.c
* Author: Daniel Brodsky
* Description: 	Implementation of a bit array data structure.
* Date: 14/03/2021
* Version: Beta
* Reviewer: Omer
\***************************************************************************/

/******************************* Inclusions **********************/

#include <stdio.h>
#include <assert.h>

#include "../include/bit_array.h"

/********************** Macros Definitions **********************/

#define MASK_ONLY_ONES 0xFFFFFFFFFFFFFFFF
#define NUM_OF_BITS 64

/******************************* BitArraySetAll **********************/

bitsarr_ty BitArraySetAll(bitsarr_ty bitarr)
{
	bitarr |= MASK_ONLY_ONES;
	return(bitarr);
}

/******************************* BitArrayResetAll **********************/

bitsarr_ty BitArrayResetAll(bitsarr_ty bitarr)
{
	bitarr = 0;
	return(bitarr);
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

unsigned int BitArrayCountOn(bitsarr_ty bitarr)
{
	size_t curr_bit_index = 0;
	size_t set_bits_counter = 0; 
	
	for (curr_bit_index = 0; curr_bit_index < NUM_OF_BITS; ++curr_bit_index) 
	{ 
		if((bitarr & (1UL << curr_bit_index)))
		{
			++set_bits_counter; 
		}  
	} 
	
	return(set_bits_counter); 
}

/******************************* BitArrayCountOff **********************/

unsigned int BitArrayCountOff(bitsarr_ty bitarr)
{
	size_t curr_bit_index = 0;
	size_t off_bits_counter = 0; 
	
	for (curr_bit_index = 0; curr_bit_index < NUM_OF_BITS; ++curr_bit_index) 
	{ 
		if(0 == (bitarr & (1UL << curr_bit_index)))
		{
			++off_bits_counter; 
		}  
	} 
	
	return(off_bits_counter); 
}

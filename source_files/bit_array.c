/****************************** File Header ******************************\
* File Name:  bit_array.c
* Author: Daniel Brodsky
* Description: 	Implementation of a bit array data structure.
* Date: 15/03/2021
* Version: 2.0 (After Review)
* Reviewer: Omer
\***************************************************************************/

/******************************* Inclusions **********************/
#include <assert.h> /* assert */

#include "bit_array.h"

/********************** Macros & Enums Definitions **********************/
#define MASK_ONLY_ONES 0xFFFFFFFFFFFFFFFF
#define NUM_OF_BITS 64
#define ASCII_VALUE_ZERO '0'
#define NULL_TERMINATOR '\0'

typedef enum
{
	NOT_INITIALIZED,
	INITIALIZED
} bits_lut_status_ty;

typedef enum
{
	NOT_SETTED,
	SETTED
} mirrored_lut_status_ty;

/********************** Forward Declreations & Globals **********************/
static int bits_lut[256] = {0}; 
static unsigned char mirrored_bits_lut[256] = {0};

unsigned int BitArrayCountOn(bitsarr_ty bitarr);
bitsarr_ty ByteMirror(bitsarr_ty bitarr);

bits_lut_status_ty bits_lut_status = NOT_INITIALIZED;
mirrored_lut_status_ty mirrored_lut_status = NOT_SETTED;

/*******************************************************************
 * Function: InitBitsLUT
 * ----------------------------
 *  Initializing a look up table
 	of 256 integers' bits.
 *
 *   returns: void 
 */
void InitBitsLUT()
{
	size_t integer_value = 0;
	
	for (integer_value = 0; integer_value < 256; ++integer_value)
	{
		bits_lut[integer_value] = BitArrayCountOn(integer_value);
	}
}

/*******************************************************************
 * Function: InitMirroredLUT
 * ----------------------------
 *  Initializing a look up table
 	of 256 integeres with reversed bits.
 *
 *   returns: void 
 */
void InitMirroredLUT()
{
	size_t integer_value = 0;
	
	for (integer_value = 0; integer_value < 256; ++integer_value)
	{
		mirrored_bits_lut[integer_value] = ByteMirror(integer_value);
	}
}

/*******************************************************************
 * Function: BitArraySetAll
 * ----------------------------
 * Sets all bits in a given variable to '1'.
 *
 * @bitsarr_ty bitarr: the value of a 8 bytes variable
 *   
 * returns: the new value
 */
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
	assert(OFF == new_state || ON == new_state);
	
	bitarr &= ~(1UL << bit_to_set);
	bitarr |= ((bitsarr_ty)(new_state) << bit_to_set);
	return(bitarr);
}

/******************************* BitArrayGetVal **********************/

bit_state_ty BitArrayGetVal(bitsarr_ty bitarr, unsigned int bit_to_read)
{
	bitsarr_ty bit_status = bitarr & (1UL << bit_to_read);
	
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

/******************************* ByteMirror **********************/

bitsarr_ty ByteMirror(bitsarr_ty bitarr)
{
	size_t curr_bit_index = 0; 	
	bitsarr_ty mirrored_bitarr = 0; 
	
	for (curr_bit_index = 0; curr_bit_index < 8; ++curr_bit_index) 
	{ 
		if((bitarr & (1 << curr_bit_index)))
		{
			mirrored_bitarr |= 1 << ((8 - 1) - curr_bit_index); 
		}  
	} 
	
	return(mirrored_bitarr); 
}
	
/******************************* BitArrayRotR **********************/

bitsarr_ty BitArrayRotR(bitsarr_ty bitarr, unsigned int amount)
{
	size_t curr_bit_index = 0; 	
	bitsarr_ty rotated_bitarr = 0; 
	amount = amount % NUM_OF_BITS;
	
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
	amount = amount % NUM_OF_BITS;
	
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
	amount = amount % NUM_OF_BITS;
	
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

/******************************* CountBitsOn **********************/

unsigned int BitArrayCountOn(bitsarr_ty bitarr)
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

/******************************* BitArrayCountOn **********************/

unsigned int BitArrayCountOnLUT(bitsarr_ty bitarr)
{
	unsigned int set_bits_counter = 0;
	
	if (NOT_INITIALIZED == bits_lut_status)
	{
	InitBitsLUT();
	bits_lut_status = INITIALIZED;
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

/******************************* BitArrayCountOn **********************/

bitsarr_ty BitArrayMirrorLUT(bitsarr_ty bitarr)
{
	bitsarr_ty mirrored_bitarr = 0;
	
	if (NOT_SETTED == mirrored_lut_status)
	{
	InitMirroredLUT();
	mirrored_lut_status = SETTED;
	}
	
	mirrored_bitarr = (bitsarr_ty)mirrored_bits_lut[bitarr & 0xff] << 56 |
        (bitsarr_ty)mirrored_bits_lut[(bitarr >> 8) & 0xff] << 48 |         
        (bitsarr_ty)mirrored_bits_lut[(bitarr >> 16) & 0xff] << 40 |
        (bitsarr_ty)mirrored_bits_lut[(bitarr >> 24) & 0xff] << 32 |         
        (bitsarr_ty)mirrored_bits_lut[(bitarr >> 32) & 0xff] << 24 |
        (bitsarr_ty)mirrored_bits_lut[(bitarr >> 40) & 0xff] << 16 |
        (bitsarr_ty)mirrored_bits_lut[(bitarr >> 48) & 0xff] << 8 |            
        (bitsarr_ty)mirrored_bits_lut[(bitarr >> 56) & 0xff];
	
	return (mirrored_bitarr);
}

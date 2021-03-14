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

#include "../include/bit_array.h"

/********************** Macros Definitions **********************/

#define MASK_ONLY_ONES 0xFFFFFFFFFFFFFFFF

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
	bitarr |= (1 << bit_to_turn);
	return(bitarr);
}

/******************************* BitArraySetOff **********************/

bitsarr_ty BitArraySetOff(bitsarr_ty bitarr, unsigned int bit_to_turn)
{
	bitarr &= ~(1 << bit_to_turn);
	return(bitarr);
}

/******************************* BitArraySetBit **********************/

bitsarr_ty BitArraySetBit(bitsarr_ty bitarr, unsigned int bit_to_set, 
												bit_state_ty new_state)
{
	bitarr |= (new_state << bit_to_set);
	return(bitarr);
}

/******************************* BitArraySetBit **********************/

bit_state_ty BitArrayGetVal(bitsarr_ty bitarr, unsigned int bit_to_read)
{
	int bit_status = bitarr & (1 << bit_to_read);
	return(!!bit_status);
}

/****************************** File Header ******************************\
* File Name:  bit_array.c
* Author: Daniel Brodsky
* Description: 	Implementation of a bit array data structure.
* Date: 14/03/2020
* Version: Beta
* Reviewer: Omer
\***************************************************************************/

/******************************* Inclusions **********************/
#include <stdio.h>

#include "../include/bit_array.h"

#define MASK_ONLY_ONES 0xFFFFFFFFFFFFFFFF
/******************************* BitArraySetAll **********************/
bitsarr_ty BitArraySetAll(bitsarr_ty bitarr)
{
	bitarr |= MASK_ONLY_ONES;
	return(bitarr);
}

bitsarr_ty BitArrayResetAll(bitsarr_ty bitarr)
{
	bitarr = 0;
	return(bitarr);
}

bitsarr_ty BitArraySetOn(bitsarr_ty bitarr, unsigned int bit_to_turn)
{
	bitarr |= (1 << bit_to_turn);
	return(bitarr);
}

bitsarr_ty BitArraySetOff(bitsarr_ty bitarr, unsigned int bit_to_turn)
{
	bitarr &= ~(1 << bit_to_turn);
	return(bitarr);
}

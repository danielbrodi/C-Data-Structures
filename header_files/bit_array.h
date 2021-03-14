#ifndef	__BITARRAY_H__
#define	__BITARRAY_H__

#include <stddef.h>	/* size_t */

typedef size_t bitsarr_ty;	/* Assuming 64-bit system */

typedef enum
{
	OFF,
	ON
} bit_state_ty;

typedef enum
{
	LEFT,
	RIGHT
} rotation_ty;	

bitsarr_ty BitArraySetAll(bitsarr_ty bitarr);

bitsarr_ty BitArrayResetAll(bitsarr_ty bitarr);

/* bit_string must have enough room for the entire array */
char *BitArrayToString(bitsarr_ty bitarr, char *bit_string);

bitsarr_ty BitArraySetOn(bitsarr_ty bitarr, unsigned int bit_to_turn);

bitsarr_ty BitArraySetOff(bitsarr_ty bitarr, unsigned int bit_to_turn);

bitsarr_ty BitArraySetBit(bitsarr_ty bitarr, unsigned int bit_to_set, 
														bit_state_ty new_state);

bit_state_ty BitArrayGetVal(bitsarr_ty bitarr, unsigned int bit_to_read);

bitsarr_ty BitArrayFlip(bitsarr_ty bitarr, unsigned int bit_to_flip);

bitsarr_ty BitArrayMirror(bitsarr_ty bitarr);

bitsarr_ty BitArrayRotR(bitsarr_ty bitarr, unsigned int amount);

bitsarr_ty BitArrayRotL(bitsarr_ty bitarr, unsigned int amount);

bitsarr_ty BitArrayRot(bitsarr_ty bitarr, unsigned int amount, 
														rotation_ty direction);

unsigned int BitArrayCountOn(bitsarr_ty bitarr);

unsigned int BitArrayCountOff(bitsarr_ty bitarr);

#endif	/* __BITARRAY_H__ */

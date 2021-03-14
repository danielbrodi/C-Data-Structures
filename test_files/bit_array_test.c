#include <stdio.h> /* printf */

#include "../include/bit_array.h"

void PrintBits(bitsarr_ty bitarr);

int main()
{
	bitsarr_ty bitarr = 0;
	PrintBits(bitarr);
	bitarr = BitArraySetAll(bitarr);
	PrintBits(bitarr);
	bitarr = BitArrayResetAll(bitarr);
	PrintBits(bitarr);
	bitarr = BitArraySetOn(bitarr, 6);
	PrintBits(bitarr);
	bitarr = BitArraySetOff(bitarr, 6);
	PrintBits(bitarr);
	return(0);
}

void PrintBits(bitsarr_ty bitarr)
{
	size_t i = 0;

	for (i = 1UL << 63; i > 0; i = i / 2)
	{
		(bitarr & i) ? printf("1") : printf("0");
	}
	printf("\n\n");
}

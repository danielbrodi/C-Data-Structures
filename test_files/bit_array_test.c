#include <stdio.h> /* printf */

#include "../include/bit_array.h"

void PrintBits(bitsarr_ty bitarr);

int main()
{
	char bit_string[64] = {0};
	bitsarr_ty bitarr = 0;
	printf("Default:\n");
	PrintBits(bitarr);
	printf("BitArraySetAll:\n");
	bitarr = BitArraySetAll(bitarr);
	PrintBits(bitarr);
	printf("BitArrayResetAll:\n");
	bitarr = BitArrayResetAll(bitarr);
	PrintBits(bitarr);
	printf("BitArraySetOn:\n");
	bitarr = BitArraySetOn(bitarr, 37);
	PrintBits(bitarr);
	printf("BitArraySetOff:\n");
	bitarr = BitArraySetOff(bitarr, 6);
	PrintBits(bitarr);
	printf("BitArraySetBit:\n");
	bitarr = BitArraySetBit(bitarr, 6, ON);
	PrintBits(bitarr);
	printf("BitArrayGetVal:\n");
	printf("Index %d is: %d\n\n", 6, BitArrayGetVal(bitarr, 10));
	printf("BitArrayFlip:\n");
	bitarr = BitArrayFlip(bitarr, 3);
	PrintBits(bitarr);
	printf("BitArrayMirror:\n");
	bitarr = BitArrayMirror(bitarr);
	PrintBits(bitarr);
	printf("BitArrayRotR:\n");
	bitarr = BitArrayRotR(bitarr, 6);
	PrintBits(bitarr);
	printf("BitArrayRotL:\n");
	bitarr = BitArrayRotL(bitarr, 15);
	PrintBits(bitarr);
	printf("BitArrayRot:\n");
	bitarr = BitArrayRot(bitarr, 35, RIGHT);
	PrintBits(bitarr);
	printf("BitArrayCountOn & BitArrayCountOff:\n");
	printf("Bits on: %d | Bits off: %d --> for: \n", BitArrayCountOn(bitarr),
	 												BitArrayCountOff(bitarr));
	PrintBits(bitarr);
	printf("BitArrayToString:\n");
	BitArrayToString(bitarr, bit_string);
	printf("%s\n\n", bit_string);

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

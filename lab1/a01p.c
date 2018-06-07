// do not change this code except in the following ways:
//   * write code for the following functions:
//      * getNextHexInt()
//      * printNumberData()
//   * change studentName by changing "I. Forgot" to your actual name

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static char *studentName = "Alexander Saber";


// get next int (entered in hex) using scanf()
// returns true (success) or false (failure)
// if call succeeded, return int value via iPtr
bool getNextHexInt(unsigned int *iPtr)
{
	// replace this code with the call to scanf()
	scanf("%X", iPtr);
	return true;
}

// print requested data for the given number
void printNumberData(int i)
{	
	//Masking to find sign bit.
	printf("signBit ");
	int s = i & 0x80000000;
	bool negative;
	if (s >= 0x00) 
	{
		negative = false;
		printf("0,");
	} else {
		negative = true;
		printf("1,");
	}

	/*Masking exp bits and shifting to the right
	  to compute integer value.*/
	printf(" expBits ");
	s = i & 0x7F800000;
	s >>= 23;
	if ((int)s < 10) printf("  ");
	if ((int)s < 100 && (int)s >= 10) printf(" ");
	printf("%d, ", s);
	int expBits = s;
	
	//Masking to print only fraction bits
	printf("fractBits ");
	s = i & 0x007FFFFF;
	printf("0x%08X\n", s);

	//Finding type of floating point numbers
	s = i & 0x7F800000;
	s >>= 23;
	//Compute exp
	int exp = expBits - 127;
	//Normalized
	if ((int)s > 0 && s < 255) 
	{	
		printf("normalized:   exp = %d\n", exp);
	} 
	//Zero
	else if ((i & 0x7FFFFFFF) == 0) 
	{
		if (!negative)
		{
			printf("+");
		} 
		else
		{
			printf("-");
		}
		printf("zero\n");
	} 
	//Denormalized
	else if ((i & 0x7F800000) >> 23 == 0 && (i & 0x007FFFFF) != 0)  
	{
		printf("denormalized: exp = %d\n", exp+1);
	}
	//NaN
	else if ((i & 0x007FFFFF) != 0 && (i & 0x7F800000) == 0x7F800000)
	{ 
		if ((i & 0x00400000) != 0) 
		{
			printf("QNaN\n");
		}
		else if ((i & 0x00400000) == 0) 
		{	
			printf("SNaN\n");	
		}
	}
	//infinity
	else 
	{
		if (!negative)
		{
			printf("+");
		}
		else
		{
			printf("-");
		}
		printf("infinity\n");
	}

	printf("\n");
}

// do not change this function in any way
int main(int argc, char **argv)
{
	unsigned int	i;					// number currently being analyzed
	bool			validInput;			// was user input valid?

	printf("CS201 - A01p - %s\n\n", studentName);
	for (;;) {
		if (argc == 1)						// allow grading script to control ...
			printf("> ");					// ... whether prompt character is printed
		validInput = getNextHexInt(&i);
		printf("0x%08X\n", i);
		if (! validInput) {					// encountered bad input
			printf("bad input\n");
			while (getchar() != '\n') ;		// flush bad line from input buffer
			continue;
			}
		printNumberData(i);
		if (i == 0) {
			printf("bye...\n");
			break;
			}
		}
	printf("\n");
	return 0;
}

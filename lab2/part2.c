#include <stdio.h>
#include <stdlib.h>

//Alexander Saber

double period(double len)
{
	double toReturn = 0;
	double n = 2.01;
	
	asm(
	//Stack empty
	"	fldl   %[len]			\n"
	//Stack now contains length of pendulum
	"	fsqrt				\n"
	//Stack contains square rooted length
	"	fmull  %[n]			\n"
	//Stack contains square rooted length * 2.01
	"	fstl   %[toReturn]		\n"
	//Stack remains the same here
	: [toReturn] "=m" (toReturn)
	: [len] "m" (len),
	  [n]   "m" (n)
	
	);
	
	return toReturn;
}

int main(int argc, char **argv)
{
	double length = atof(argv[1]);

	printf("%f\n", period(length));

	return 0;
}

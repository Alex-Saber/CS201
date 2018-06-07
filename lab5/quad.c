#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
  _______________________________
 |	                  	 |
 |  CS201 Alexander Saber - LAB5 |
 |_______________________________|

*/
double root(double a, double b, double c, double d)
{
	double to_Return;
	double four = -4;
	double two = 2;
	double one = -1;
	asm(
	"	fldl %[two]		\n"	// 2
	"	fmull %[a] 		\n"	// 2a
	"	fldl %[a]		\n" 	// 2a, a
	"	fmull %[c]		\n"     // 2a, a*c
	"	fmull %[four]		\n" 	// 2a, -4*a*c
	"	fldl %[b]		\n"	// 2a, -4*a*c, b
	"	fmull %[b]		\n"	// 2a, -4*a*c, b*b
	"	faddp 		 	\n"	// 2a,  b*b - 4*a*c
	"	fsqrt			\n"	// 2a, (b*b - 4*a*c)^.5
	"	fmull %[d]		\n"	// 2a, +/- (b*b - 4*a*c)^.5
	"	fldl %[b]		\n"	// 2a, +/- (b*b - 4*a*c)^.5, b
	"	fmull %[one] 		\n"	// 2a, +/- (b*b - 4*a*c)^.5, -b
	"	faddp 			\n"	// 2a, -b +/- (b*b - 4*a*c)^.5	
	"	fdivp 			\n"	// (-b +/- (b*b - 4*a*c)^.5)/2a
	"	fstl %[to_Return]	\n"   	// (-b +/- (b*b - 4*a*c)^.5)/2a	
			
	: [to_Return] "=m" (to_Return)
	: [one] "m" (one), [two] "m" (two), [four] "m" (four), 
	  [a] "m" (a), [b] "m" (b), [c] "m" (c), [d] "m" (d)
	);

	return to_Return;
}

int main(int argc, char **argv)
{
	if (argc < 4) 
	{
		printf("Not enough arguments\n");
		return 0;
	}
	
	double a = atof(argv[1]);
	double b = atof(argv[2]);
	double c = atof(argv[3]);
	double ans1 = root(a,b,c, 1);
	double ans2 = root(a,b,c, -1);
	
	if (ans1 == ans2)
	{
		printf("\nRepeated Root, x = %.4f\n\n", ans1);
		return 0; 
	}
	
	printf("\nRoots:\n\nx_1 = %.4f\n\nx_2 = %.4f\n\n", ans1, ans2);
	return 0;	
}

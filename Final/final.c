#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double pythag_d(double x, double y)
{	
	double to_Return;
	asm(
	"	fldl %[x]		\n" // x
	"	fmull %[x]		\n" // x^2
	"	fldl %[y]		\n" // x^2, y
	"	fmull %[y]		\n" // x^2, y^2
	"	faddp			\n" // x^2 + y^2
	"      	fsqrt			\n" // sqrt(x^2 + y^2)
	"	fstl %[to_Return]	\n" // this is the value of d = sqrt(x^2 + y^2) 

	: [to_Return] "=m" (to_Return)
	: [x] "m" (x), [y] "m" (y)	
	);
	return to_Return;
}


int main(int argc, char **argv)
{
	printf("CS 201 - Final Exam - Alexander Saber\n");
	
	// Initialize variables for x, y, d, # of darts inside, # of darts outside
	double inside = 0;
	double outside = 0;
	
	double rand_x;
	double rand_y;
	double d;
	
	//Get command line arguments
	int n = atof(argv[1]);
	
	// Initialize random number generator
	srand48(0);
	
		
	// Throwing the specified number of darts (n)
	for (int i = 0; i < n; i++)
	{	
		rand_x = drand48();
		rand_y = drand48();
		
		d = pythag_d(rand_x, rand_y);
		
		if (d > 1)
		{
			outside++;
		}
		else if (d <= 1) 
		{
			inside++;
		}
	}
	double pi = 4 * (inside/n);
	printf("%d darts : pi = %.10f\n", n, pi);
	return 0;
}

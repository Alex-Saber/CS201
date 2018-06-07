#include <stdio.h>
#include <stdlib.h>

//Alexander Saber

int ERROR;

int add(int x, int y) 
{
	int toReturn;
	int overflow = 0;
	asm(
	"	movl %[x], %%eax         \n"
	"	addl %[y], %%eax         \n"
	"	jno  here 		 \n"
	"	movl $1, %[overflow]	 \n"
	"	here: movl %%eax, %[toReturn]  \n"
	: [toReturn] "=m"  (toReturn),
	  [overflow] "=m" (overflow)
	: [y] "m"  (y),		
	  [x] "m"  (x)
	: "eax"
	);
	
	if (overflow == 1)
	{
		printf("Error: Overflow has occured\n");
		ERROR = 1;
		return 0;
	} 
	else
	{
		return toReturn;
	}
}

int main(int argc, char **argv) 
{
	ERROR = 0;
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int sum = add(a, b);
	if (ERROR == 0) 
	{
		printf("%d\n", sum);
	}	
	return 0;
}

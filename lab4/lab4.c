// Numbers from command line arguments are sent to child process
// from parent process one at a time through pipe.
//
// Child process adds up numbers sent through pipe.
//
// Child process returns sum of numbers to parent process.
//
// Parent process prints sum of numbers.

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	printf("CS201 - Lab 4 - Alex Saber\n");

	// Initialize child pid and empty int used for sum.
	pid_t cpid;
	int to_Add;

	// Set up pipe and check for error
	int pfd[2];
	if (pipe(pfd) == -1)
	{
		printf("ERROR: Pipe Failed!\n");
		return 1;
	}

	// Call fork() and check for errors
	cpid = fork();
	if (cpid == -1) 
	{
		printf("ERROR: Could not create child proccess!\n");
		return 1;	
	}

	// If no errors in fork() run child process
	else if (cpid == 0) 
	{
		// -- running in child process --
		int sum = 0;
		// Receive numbers from parent process via pipe
		// one at a time, and count them.
		
		// This reads the first int in the pipe which is the number of integers/arguments to add.
		int t;
		read(pfd[0], &t, 4); 
		//write for loop to read from pipe, use size from pipe to stop the loop
		for (int i = 0; i < t; i++) 
		{
			read(pfd[0], &to_Add, 4);
			sum += to_Add;
		}
		// Return sum of numbers.
		return sum;
	}

	// Run parent process
	else 
	{
		// -- running in parent process --
		
		// This creates an array of integers based on the number
		// of arguments in the command line.
		int *input = (int *) malloc( (argc)*sizeof(int));
		
		//Checking for Error produced by malloc
		if (input == 0) 
		{
			printf("ERROR: malloc - out of memory\n");
			return 1;
		}

		// This is for writing the number of arguments to the pipe
		// so that the child can loop without directly refering to argc.
		input[0] = argc - 1;

		// This gathers the integers from the arguments passed
		// through the command line.
		for (int i = 1; i < argc; i++)
		{
			input[i] = atoi(argv[i]);
		}

		// Send numbers (datatype: int, 4 bytes) from command line arguments
		// starting with argv[1] one at a time through pipe to child process.
		int sum = 0;
		int status;
		for (int i = 0; i < argc; i++)
		{
			write(pfd[1], &input[i], 4);
		}
		
		// This memory is no longer needed 
		// Call to free 
		free(input);
		
		// Wait for child process to return. Reap child process.
		// Call waitpid and check for error within
		if (waitpid(cpid, &status, 0) == -1)
		{	
			printf("ERROR: waitpid() failed!\n");
			return 1;
		}
		
		// Receive sum of numbers via the value returned from child when exited.
		WIFEXITED(status);
		status = WEXITSTATUS(status);
		sum = status;

		printf("sum = %d\n", sum);
		return 0;
	}
}

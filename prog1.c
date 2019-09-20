#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define NUMBER_OF_CHILDREN 4

int main(int argc, char *argv[])
{
	int numberOfArgs = argc;
	char buf[100];
	int pid[NUMBER_OF_CHILDREN];
	pid_t child_fib, child_needle, child_ellipse, child_pball;
	printf("%d\n",isdigit("d"));
	if(numberOfArgs != 8) 
	{ 
		printf("	Incorrect Number of Arguments....\n		./prog1 n r a b s x y\n");
       		return 1;
	}
	for(int i = 0; i < NUMBER_OF_CHILDREN; i++)
	{
		pid[i] = fork();
		if(pid[i] < 0)
		{
			sprintf(buf, "Fork() did not work\n");
			write(1, buf, strlen(buf));
			return 1;
		}
	}

// Fibonacci child process
	if(getpid() = pid[0])
	{

		int fibNum = argv[1];
		sprintf(buf, "Fibonacci Process Started\nInput Number %d\n", fibNum);
		write(1, buf, strlen(buf));
		if(fibonacci(fibNum) < 0)
		{
			return 1;
		}
		sprintf(buf, "Fibonacci Number f(%d) is %d\n", fibNum, fibonacci(fibNum));
		return 0;	
	}

	int fibonacci(int fibNum)
	{
		if(fibNum < 1)
		{
			sprintf(buf, "Invalid Fibonacci number\n");
			write(1, buf, strlen(buf));
			return -1;;
		}else if(fibNum <= 2)
		{
			sprintf(buf, "Fibonacci Number f(%d) is 1\n", fibNum);
			write(1, buf, strlen(buf));
			return 0;
		}
		if(fibNum > 2)
		{
		}else
		{

		}	
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define NUMBER_OF_CHILDREN 4

int fibonacci(int fibNum)
{
	if(fibNum <= 1)
	{
		return fibNum; 
	}
	return (fibonacci(fibNum - 1) + fibonacci(fibNum - 2));
}

int main(int argc, char **argv)
{
	int numberOfArgs = argc;
	int arguments[numberOfArgs];
	char buf[100];
	pid_t pid[NUMBER_OF_CHILDREN];
	pid_t process[NUMBER_OF_CHILDREN];
	pid_t child_fib, child_needle, child_ellipse, child_pball;

	for(int i = 0; i < numberOfArgs; i++)
	{
		arguments[i] = atoi(argv[i]);
	}
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
		}else if(pid[i] == 0)
		{
			process[i] = getpid();
			break;
		}

	}



// Fibonacci child process
	if(getpid() == process[0])
	{

		int fibVal;
		int fibNum = arguments[1];
		sprintf(buf, "Fibonacci Process Started\nInput Number %d\n", fibNum);
		write(1, buf, strlen(buf));
		
		if(fibNum < 1)
		{
			sprintf(buf, "Invalid Fibonacci number\n");
			write(1, buf, strlen(buf));
			return -1;;
		}
		
		fibVal = fibonacci(fibNum);
		sprintf(buf, "Fibonacci Number f(%d) is %d\nFibonacci Process Exits\n", fibNum, fibVal);
		write(1, buf, strlen(buf));
		return 0;	
	}
	wait(NULL);
}	

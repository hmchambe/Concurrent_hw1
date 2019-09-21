#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/wait.h>

#define NUMBER_OF_CHILDREN 4
#define PI 3.1415926

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

// Buffon's Needle child process
	if(getpid() == process[1])
	{
		sprintf(buf, "Buffon's Needle Process Started\nInput Number %d\n", arguments[2]);
		write(1, buf, strlen(buf));

		int timesCrossingLine = 0, G = 1;
		double d, a;
		double probability;
		srand(time(NULL));
		for(int i = 0; i < arguments[2]; i++)
		{
			d = rand() / (double)RAND_MAX;
			a = rand() / ((double)RAND_MAX) * (2.0 * acos(-1.0));
			if(d + sin(a) < 0 || d + sin(a) > G)
			{
				timesCrossingLine++;	
			}	
		}
		probability = ((double)timesCrossingLine) / ((double) arguments[2]);
		
		sprintf(buf, "Times Crossing Line %d\nEstimated Probability is %lf\nBuffon's Needle Process Exits\n", timesCrossingLine, probability);
		write(1, buf, strlen(buf));	
		return 0;
	}
	
	wait(NULL);
}	

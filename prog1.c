/* ----------------------------------------------------------- */
/* NAME : Hunter Chambers                  User ID: 81276171   */
/* DUE DATE : 09/26/2019                                       */
/* PROGRAM ASSIGNMENT #1                                       */
/* FILE NAME : prog1.c				               */
/* PROGRAM PURPOSE :                                           */
/*    This program forks multiple times to create 4 child      */
/*    processes that calculate the fibonacci sequence for      */
/*    a given input, calculates the probability of Buffons     */
/*    needle equation for a given number of repitions, finds   */
/*    the area of an ellipse, and makes a histogram of a       */
/*    pinball game.					       */ 
/* ----------------------------------------------------------- */


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUMBER_OF_CHILDREN 4
#define PI 3.1415926

/* ----------------------------------------------------------- */
/* FUNCTION  fibonacci                                         */
/*     This function computes the fibonacci sequence	       */
/*     recursively           	                               */
/* PARAMETER USAGE :                                           */
/*	int fibNum => this is which index of the fibonacci     */
/*		sequence that the value is being computed for  */
/* FUNCTION CALLED :                                           */
/*    [none]					               */
/* ----------------------------------------------------------- */
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
	int numberOfArgs = argc, status, i;
	int arguments[numberOfArgs];
	char buf[100];
	pid_t pid[NUMBER_OF_CHILDREN];
	pid_t process[NUMBER_OF_CHILDREN];
	pid_t parentID = getpid();

	for(i = 0; i < numberOfArgs; i++)
	{
		arguments[i] = atoi(argv[i]);
	}
	if(numberOfArgs != 8) 
	{ 
		printf("	Incorrect Number of Arguments....\n		./prog1 n r a b s x y\n");
       		return 1;
	}
	for(i = 0; i < NUMBER_OF_CHILDREN; i++)
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
// Prints with 3 leading spaces
	if(getpid() == process[0])
	{

		int fibVal;
		int fibNum = arguments[1];
		sprintf(buf, "   Fibonacci Process Started\n   Input Number %d\n", fibNum);
		write(1, buf, strlen(buf));
		
		if(fibNum < 1)
		{
			sprintf(buf, "   Invalid Fibonacci number\n");
			write(1, buf, strlen(buf));
			return -1;;
		}
		
		fibVal = fibonacci(fibNum);
		sprintf(buf, "   Fibonacci Number f(%d) is %d\n   Fibonacci Process Exits\n", fibNum, fibVal);
		write(1, buf, strlen(buf));
		return 0;	
	}

// Buffon's Needle child process
// Prints with 6 leading spaces
	if(getpid() == process[1])
	{
		sprintf(buf, "      Buffon's Needle Process Started\n      Input Number %d\n", arguments[2]);
		write(1, buf, strlen(buf));

		int timesCrossingLine = 0, G = 1;
		double d, a;
		double probability;
		srand(time(NULL));
		for(i = 0; i < arguments[2]; i++)
		{
			d = rand() / (double)RAND_MAX;
			a = rand() / ((double)RAND_MAX) * (2.0 * acos(-1.0));
			if(d + sin(a) < 0 || d + sin(a) > G)
			{
				timesCrossingLine++;	
			}	
		}
		probability = ((double)timesCrossingLine) / ((double) arguments[2]);
		
		sprintf(buf, "      Estimated Probability is %lf\n      Buffon's Needle Process Exits\n", probability);
		write(1, buf, strlen(buf));	
		return 0;
	}
// Area of an Ellipse
// Prints with 9 leading spaces
	if(getpid() == process[2])
	{
		double  pairs = arguments[5];
		double x = arguments[3], y = arguments[4];
		sprintf(buf, "         Ellipse Process Area Started\n         Total Random Number Pairs %f\n         Semi-Major Axis Length %f\n         Semi-Minor Axis Length %f\n", pairs, x, y );
		write(1, buf, strlen(buf));

		srand(time(NULL));
		
		return 0;

	}
// Fourth child process
	if(getpid() == process[3]){ return 0; }

	if(getpid() == parentID)
	{
		for(int q = 0; q < NUMBER_OF_CHILDREN; q++)
		{
			sprintf(buf, "%d child exited\n", q);
			write(1, buf, strlen(buf));
			wait(&status);
		}
	}
}	

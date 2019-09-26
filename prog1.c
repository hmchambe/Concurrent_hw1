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

/* ----------------------------------------------------------- */
/* FUNCTION  main                                              */
/*     This function is the parent process that forks multiple */
/*     times to run given processes                            */
/* PARAMETER USAGE :                                           */
/*	int argc => number of command line args   	       */
/* FUNCTION CALLED :                                           */
/*    fibonacci					               */
/* ----------------------------------------------------------- */
int main(int argc, char **argv)
{
	int numberOfArgs = argc, status, i;
	int arguments[numberOfArgs];
	char buf[300];
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



/* Fibonacci child process */
/* Prints with 3 leading spaces */
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

/* Buffon's Needle child process */
/* Prints with 6 leading spaces */
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
/* Area of an Ellipse */
/* Prints with 9 leading spaces */
	if(getpid() == process[2])
	{
		int i = 0;
		double finalResult, actualArea, x, y; 
		int s = arguments[5], t = 0, a = arguments[3], b = arguments[4];
		sprintf(buf, "         Ellipse Process Area Started\n         Total Random Number Pairs %d\n", s);
		write(1, buf, strlen(buf));

		srand(time(NULL));
		
		for(i = 0; i < s; i++)
		{
			
			x = ((float) rand()/RAND_MAX) * a;
			y = ((float) rand()/RAND_MAX) * b;

			if(((float)pow(x,2)/pow(a,2))+((float)pow(y,2)/pow(b,2)) <= 1.0)
			{
				t++;
			}
		}
		sprintf(buf,"         Semi-Major Axis Length %d\n         Semi-Minor Axis Length %d\n         Total Hits %d\n", a, b, t);
		write(1, buf, strlen(buf));
		finalResult = (((float)t/s)*a*b)*4;
		actualArea = acos(-1.0)*a*b;

		sprintf(buf,"         Estimated Area is %2.5lf\n         Actual Area is %2.5lf\n         Ellipse Area Process Exits\n", finalResult, actualArea);
		write(1, buf, strlen(buf));

		return 0;

	}
/* Fourth child process */
	if(getpid() == process[3])
	{ 
		int x = arguments[6], y = arguments[7], pins = x - 1, i, j, finalBin = 1;
		int maxVal = 0, maxBin = 0, asterisks[x];
 		signed long int bins[x];
		double direction, percentage[x];
		sprintf(buf, "Simple Pinball Process Started\nNumber of Bins %d\nNumber of Ball Droppings %d\n", x, y);
		write(1, buf, strlen(buf));

		for(i = 0; i < x; i++)
		{
			bins[i] = 0;
		}
		for(i = 0; i < y; i++) /* Iterates for how many balls there are */
		{
			for(j = 0; j < pins; j++) /* Iterates as many times as there are pins */
			{
				direction = ((float)rand() / RAND_MAX);
				if(direction > 0.5)
				{ /* ball goes right */
					finalBin++;
				}
			}
			bins[finalBin - 1]++; /* tally for which bin the ball ended up in */
			finalBin = 1;
			if((i % 30000) == 0)
			{	/* New random seed */
				srand(time(NULL));
			}
		}
		maxBin = 0;
		maxVal = bins[0];
		for(i = 1; i < x; i++)
		{	/* Finding bin with max hits */
			if(bins[i] > maxVal)
			{
				maxVal = bins[i];
				maxBin = i + 1;
			}
			sprintf(buf, "bins[%d]: %ld\n", i-1, bins[i-1]);
			write(1, buf, strlen(buf));
		}	
		for(i = 0; i < x; i++)
		{	/* Percentage for each bin for histogram */
			percentage[i] = (float) bins[i] / y;
			sprintf(buf, "percentage[%d]: %lf\n", i, percentage[i]);
			write(1, buf, strlen(buf));
		}
		for(i = 0; i < x; i++)
		{	/* histogram for pinball */ 
			asterisks[i] = 50 * (percentage[bins[i]] / percentage[bins[maxBin]]);
			sprintf(buf, "%3d-(%7ld)-(%5.2f)|\n", i+1, bins[i], percentage[i]);
			for(j = 0; j < asterisks[i]; j++)
			{
				sprintf(buf, "*");
			}
			sprintf(buf, "\n");
			write(1, buf, strlen(buf));

		}
		return 0; 
	}

	if(getpid() == parentID)
	{
		int q;
		for(q = 0; q < NUMBER_OF_CHILDREN; q++)
		{
			wait(&status); /* waiting for all child processes */
		}
		
		return 0;
	}
}	

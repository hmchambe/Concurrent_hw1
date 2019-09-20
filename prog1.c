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
}

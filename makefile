all: prog1.c
	gcc -g -Wall -Wextra -o prog1 prog1.c

clean:
	$(RM) prog1

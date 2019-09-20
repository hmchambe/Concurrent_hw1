all: prog1.c
	gcc prog1 -lm -o prog1.c

clean:
	$(RM) prog1

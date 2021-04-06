build: 0main.o escape.o 
	gcc -ansi -std=c99 -Wall escape.o 0main.o -g -o run.exe

%.o: %.c
	gcc -ansi -std=c99 -Wall -g $^ -c

clean:
	$(RM) *.o

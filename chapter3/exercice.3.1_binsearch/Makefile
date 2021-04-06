binsearch: binsearch.o rand_array.o sort.o header_binsearch.h
	gcc binsearch.o rand_array.o sort.o -g -o run.exe

%.o: %.c
	gcc -ansi -std=c99 -Wall -g -c $^

clean:
	$(RM) *.o

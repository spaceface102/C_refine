# -*- MakeFile -*-

PROG = run.exe

# is called the pattern rules
#@ is a automatic variable, where @ is the target; you need another target to run this
%.c: 
	gcc $@ -ansi -std=c99 -Wall -g -o $(PROG)

clean:
	rm -f *.exe *.o

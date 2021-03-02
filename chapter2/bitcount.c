#include <stdio.h>
#include <stdlib.h>

int bitcount(int binary)
{
	int count;
	for(count = 0; binary; count++, binary &= (binary - 1));
	return count;
}

int main(int argc, char *argv[])
{
	if (argc > 1) {printf("bitcount(%s) = %d\n", argv[1], bitcount(atoi(argv[1])));}
	else {printf("Usage: %s <number_base10>\n", argv[0]); exit(42);}
	return 0;
}

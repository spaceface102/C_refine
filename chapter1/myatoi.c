#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t myatoi(char *number)
{
	uint8_t locate_null;
	uint64_t out = 0;
	for(locate_null = 0; number[locate_null] != '\0'; locate_null++);
	for(uint64_t i = 1; locate_null-- > 0; out += (number[locate_null] - '0')*i, i *= 10);
	return out;
}

int main(int argc, char *argv[])
{
	if(argc == 1) {printf("Usage: %s <integer number>\n", argv[0]); exit(42);}
	printf("\"%s\" == %lu\n", argv[1], myatoi(argv[1]));
	return 0;
}

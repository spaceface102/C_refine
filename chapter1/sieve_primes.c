#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define true 1
#define false 0

uint64_t myatoi(char *number);

int main(int argc, char *argv[])
{	
	if(argc == 1) {printf("\aUsage: %s <integer>\n", argv[0]); exit(42);}
	uint_fast64_t NUMB = myatoi(argv[1]);
	uint8_t *range = (uint8_t *)malloc(sizeof(uint8_t)*(NUMB + 1));
	uint_fast64_t numb_primes = 0;
	memset(range, true, NUMB+1);
	for(uint_fast64_t p = 2; p * p <= NUMB; p++)
	{
		if(range[p])
		{
			for(uint_fast64_t i = p * p; i <= NUMB; i += p)
				range[i] = false;
		}
	}
	for(uint_fast64_t i = 0; i <= NUMB; i++)
		if(range[i]) {range[numb_primes++] = i;}
	printf("numb of primes in first %ld numbers: %ld\n", NUMB, numb_primes);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define true 1
#define false 0
int main(int argc, char *argv[])
{	
	uint_fast64_t NUMB = atoi(argv[1]);
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

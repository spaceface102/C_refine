#include <stdio.h>
#include <stdint.h>
#define NUMB 100000 //number of primes that I want to find

int main(void)
{
	uint32_t test_numb; 
	uint32_t primes[NUMB];
	uint64_t track_prime = 0;
	uint64_t i;
	primes[track_prime++] = 2; test_numb = 3;
	while(track_prime < NUMB)
	{
		for(i = 0; (i < track_prime) && (test_numb%primes[i]); i++);
		if (i == track_prime) {primes[track_prime++] = test_numb;}
		test_numb++;
	}

	return 0;
}

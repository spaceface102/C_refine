#include <stdio.h>

int main(void)
{
	for(long i = 1; i <= 0xffff; i++)
		printf("%s%s", !(i%3) ? "Fizz":"", !(i%5) ? "Buzz":"")  ?  printf("\n") : printf("%ld\n", i);
	return 0;
}

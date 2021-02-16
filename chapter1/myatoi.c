#include <stdint.h>
#include <stdio.h>

uint64_t myatoi(char *number)
{
	uint8_t locate_null;
	uint64_t out = 0;
	for(locate_null = 0; number[locate_null] != '\0'; locate_null++);
	for(uint64_t i = 1; locate_null-- > 0; out += (number[locate_null] - '0')*i, i *= 10);
	return out;
}

int kr_atoi(char s[])
{
	int i, n;
	n = 0;
	for(i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = 10*n + (s[i] - '0');
	return n;
}

uint64_t mod(char num[])
{
	uint64_t out = 0;
	for(uint8_t i = 0; num[i] != '\0'; out = out*10 + (num[i] - '0'), i++);
	return out;
}

int main(void)
{
	kr_atoi("100");
	printf("mod(%s) = %ld\n", "100", mod("100"));
	return 0;
}

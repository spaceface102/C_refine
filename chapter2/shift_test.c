#include <stdio.h>
#include <stdint.h>

int main(void)
{
	int8_t x = 0x8f;
	printf("%x\n%x\n", x, x>>8);
	return 0;
}

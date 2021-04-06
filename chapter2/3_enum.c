#include <stdio.h>
#include <stdint.h>

int main(void)
{
	enum moth {yer = 213+213, hello = '\a'};
	printf("%x\n", yer);
	return 0;
}

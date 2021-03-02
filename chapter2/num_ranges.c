#include <stdio.h>

int main(void)
{
	//works for twos comps systems
	unsigned char ch = -1;
	unsigned short sh = -1;
	unsigned int i = -1;
	unsigned long lo = -1;
	printf("char: -%u to %u\nunsigned char: 0 to %u\n\n", 1+ch/2, ch/2, ch);
	printf("short: -%u to %u\nunsigned short: 0 to %u\n\n", 1+sh/2, sh/2, sh);
	printf("int: -%u to %u\nunsigned int: 0 to %u\n\n", 1+i/2, i/2, i);
	printf("long: -%lu to %lu\nunsigned long: 0 to %lu\n\n", 1+lo/2, lo/2, lo);

	//a little bit more compact and no need for variables to be declared
	printf("char: -%u to %u\nunsigned char: 0 to %u\n\n", 
	1+(unsigned char)(-1)/2, (unsigned char)(-1)/2, (unsigned char)(-1));
	printf("short: -%hu to %hu\nunsigned short: 0 to %hu\n\n",
	1+(unsigned short)(-1)/2, (unsigned short)(-1)/2, (unsigned short)(-1));
	printf("int: -%u to %u\nunsigned int: 0 to %u\n\n",
	1+(unsigned int)(-1)/2, (unsigned int)(-1)/2, (unsigned int)(-1));
	printf("long: -%lu to %lu\nunsigned long: 0 to %lu\n\n", 
	1+(unsigned long)(-1)/2, (unsigned long)(-1)/2, (unsigned long)(-1));

	return 0;
}

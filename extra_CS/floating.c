#include <stdio.h>
#include <stdint.h>

void rand_array(uint32_t array[], uint32_t max, uint32_t n);
int main(void)
{
	unsigned int x = 0x7f7fffff;
	float y = *(float *)&x;
	printf("%f\n", y);

	float f[3] = {42.42f, 69.69f, 420.69f};
	unsigned int *j = (unsigned int *)&f;
	for(int i = 0; i < 3; i++)
	{
		printf("%x ==", *(j+i));
		printf("%f\n", *(float *)(j+i));
	}
	return 0;
}

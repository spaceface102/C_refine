#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 0xffff

void radix_sort(uint32_t array[], uint32_t n);
void rand_array(uint32_t array[], uint32_t max, uint32_t n);
void test_sort();

int main(void)
{
	test_sort();
	//testing with float
	float yeah[101];
	rand_array((uint32_t *)yeah, 0x7f7fffff, 100);//0x7f7fffff is max numb with ieee754
	yeah[100] = -3.14e-38; //I want to display the problem 
	radix_sort((uint32_t *)yeah, 101);
	return 0;
}


void test_sort()
{
	uint32_t fail = 0;
	uint32_t *array = (uint32_t *)malloc(SIZE*sizeof(uint32_t));
	for(uint8_t i = 0; i < 0xf; i++)
	{
		rand_array(array, 0xfeedbeef, SIZE);
		radix_sort(array, SIZE);
		for(uint32_t j = 1; j < SIZE; j++)
			if(array[j] < array[j-1])
				fail = printf("Something is not working :/\n");
	}
	if(!fail)
		printf("Yessss sirrr!\n");
	free(array);
}


void radix_sort(uint32_t array[], uint32_t n)
{
	uint32_t bucket[0x100], *temp = NULL;
	uint32_t *sorting = (uint32_t *)malloc(n*sizeof(uint32_t));
	for(uint64_t sh = 0; sh < 32; sh += 8) //sh == shift us 64bit, native word size
	{
		memset(bucket, 0x0, (0x100)*sizeof(uint32_t));
		for(uint32_t i = 0; i < n; i++)
			bucket[(array[i]>>sh)&0xff]++;
		for(uint32_t j = 1; j <= 0xff; j++) //0xff == max index in bucket, aka 0x100 - 1
			bucket[j] += bucket[j-1];
		for(int64_t k = n - 1; k >= 0; k--)
			sorting[--bucket[(array[k]>>sh)&0xff]] = array[k];
		/*will always sort even amount of times due to end cond being curr_digit
		don't need to check if I have done an even or odd amount of swaps*/
		temp = sorting;
		sorting = array;
		array = temp;
	}
	free(sorting);
	/*consider passing in the "sorting" array instead of dynamically allocating 
	a local array every time you run the function; this might serve to useful as
	allocating and deallocating memory can be slow. If you are going to be using
	the function a lot, then why allocate more than you need to! As it stands right
	now it makes it so using it a couple of times is quick and easy, but the more 
	you use it, the more it becomes a better idea to pass in a pre allocated 
	memory block!*/
}


void rand_array(uint32_t array[], uint32_t max, uint32_t n)
{
	srand(time(NULL));
	max += 1;
	for(uint32_t i = 0; i < n; i++)
		array[i] = rand()%max;
}

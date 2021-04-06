#include <stdio.h>
#include <string.h>
#include "rand_array.c"

#define MIN_ARGS 1
#define SIZE 1000	
#define MAX 25000
#define USAGE "Usage %s <integer>\n"

int *randarr(int x[], int size_arr, int max); //found in rand_array.c in exercies 3.1
void shellsort(int v[], int n);
void rewriteshellsort(int arr[], int n);

int main(int argc, char *argv[])
{
	int x[SIZE], y[SIZE], i;
	randarr(x, SIZE, MAX);
	memcpy(y, x, sizeof(int)*SIZE);
	shellsort(x, SIZE);
	rewriteshellsort(y, SIZE);
	for(i = 0; i < SIZE && x[i] == y[i]; i++);
	(i == SIZE) ? printf("Good job!\n") : printf(":(\n");
	//(argc > MIN_ARGS) ? printf("%d\n", atoi(argv[1])) : printf(USAGE, argv[0]);
	return 0;
}

void shellsort(int v[], int n)
{
	int gap, i, j, temp;
	
	for(gap = n/2; gap > 0; gap /= 2)
		for(i = gap; i < n; i++)
			for(j = i-gap; j>=0 && v[j]>v[j+gap]; j-=gap)
			{
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
}

void rewriteshellsort(int arr[], int n)
{
	/*shell sort is like insertion sort, just
	that it first compares indexes that are on
	the oposite side of the spectrum. Therefore
	you can think of shell sort as creating a 
	sub array where it is all the elements that
	index%gap == 0, and then insertion sort is 
	used to sort through them. In this way elements
	that would have taken a lot more comparisons
	to get to the left with insertion sort, are
	quickly transported.*/
	int gap, i, j, temp; //"gap" indicates the difference in index between the two items that are being comp.
	for(gap = n/2; gap > 0; gap /= 2) //smallest gap == 1 @ which point doing vanilla insertion sort
		/*"i" is the index infront of "j", where "j" is defined as i - gap in order to make sure that distance
		between them is always == gap*/
		for(i = gap; i < n; i++)
			/*do j -= gap, to ensure that if there was a swap, the current swapped element
			is put in the right position in the sub array (like with insertion sort, but 
			instead of going back by 1, you go back by the gap.*/
			for(j = i - gap; j >= 0 && arr[j] > arr[j+gap]; j -= gap)
			{
				temp = arr[j+gap];
				arr[j+gap] = arr[j];
				arr[j] = temp;
			}
}

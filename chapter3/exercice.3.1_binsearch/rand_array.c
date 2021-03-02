#include <stdlib.h>
#include <time.h>

int *randarr(int x[], int size_arr, int max)
{
	srand(time(0));
	for(int i = 0; i < size_arr; x[i] = rand()%max, i++);
	return x;
}

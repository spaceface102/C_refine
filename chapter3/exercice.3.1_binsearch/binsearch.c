#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header_binsearch.h"

#define SIZE 100 //Size of random array
#define MAX 100  //Max number in random array
#define CHECK 100 //Ammount of times to check binsearch vs kr_binsearch

int binsearch(int x, int v[], int n)
{
	//from random website, still doesn't 
	//seem to work...
	int low = 0, high = n + 1, mid;
	while(high - low >= 2)
	{
		mid = (low+high)/2;
		if(mid*mid <= n) {low = mid;}
		else {high = mid;}
	}
	return low;
}

int kr_binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low+high)/2;
		if (x < v[mid])
			high = mid - 1; 
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1; //no match
}

int main(int argc, char *argv[])
{
	srand(time(0));
	int x[SIZE], comp[2][SIZE], numb;
	for(int i = 0; i < CHECK; i++)
	{
		sort(randarr(x, SIZE, MAX), SIZE);
		for(int j = 0; j < SIZE; j++)	
		{
			numb = rand()%MAX;
			comp[0][j] = kr_binsearch(numb, x, SIZE);
			comp[1][j] = binsearch(numb, x, SIZE);
			if (comp[0][i] != comp[1][i]) {printf("Oops: %d\n", i);}
		}
	}
	return 0;
}

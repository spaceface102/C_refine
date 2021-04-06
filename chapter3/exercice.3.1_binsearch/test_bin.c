#include <stdio.h>

#define SIZE 100
#define FIND 3

int binsearch(int x, int v[], int n)
{
	//there must be a way, come back to this.
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low+high)/2;
		if (x < v[mid])
			high = mid - 1; 
		else //either v[mid] > x or v[mid] == x
			low = mid + 1;
	}

	if(high < 0) {return -1;}
	else if(low == n)
	{
		if(x == v[n - 1]) {return n - 1;}
		else {return -1;}
	}
	else {return high;} 
}

int main(void)
{
	int x[SIZE] = 
	{0, 0, 0, 0, 0, 0, 4, 5, 5, 6, 7, 7, 9, 11, 11, 12, 13, 13, 14, 14, 15, 17, 
	18, 18, 18, 19, 19, 19, 20, 21, 22, 24, 25, 25, 26, 26, 29, 31, 31, 31, 33, 
	36, 36, 36, 37, 38, 39, 41, 43, 44, 45, 45, 46, 48, 49, 50, 50, 50,52, 54, 
	55, 57, 57, 58, 58, 59, 60, 61, 62, 62, 64, 64, 65, 67, 68, 68, 70, 70, 71, 
	71, 73, 78, 78, 78, 81, 82,86, 87, 87, 87, 91, 92, 92, 94, 95, 95, 96, 96, 97, 98};

	binsearch(FIND, x, SIZE);
	return 0;
}

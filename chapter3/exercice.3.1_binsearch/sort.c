void sort(int x[], int size_array)
{
	int head, j, curr;
	for(head = 1; head < size_array; head++)
	{
		curr = x[head];
		j = head - 1;
		while( (j >= 0) && (curr < x[j]) )
		{
			x[j + 1] = x[j];
			j--;
		}
		x[j + 1]= curr;
	}
}

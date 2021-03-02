#include <stdio.h>
#include <ctype.h>

#define MIN_ARGS 1
#define USAGE "Usage %s <string>\n"
#define SIZE 1000

char *expand(char s1[], char s2[]);
int cond_exp(int (*func)(int), char s1[], char s2[], int *i, int *k);

int main(int argc, char *argv[])
{
	char s2[SIZE];
	(argc > MIN_ARGS) ? printf("%s\n", expand(argv[1], s2)) : printf(USAGE, argv[0]);
	return 0;
}

char *expand(char s1[], char s2[])
{
	//a-z to abc..xyz
	int i, k; //k manages s2 index
	for (i = 0; isblank(s1[i]); i++);//skips init blanks
	for (k = 0; s1[i] != '\0';)
	{
		if (cond_exp(isalpha, s1, s2, &i, &k)) NULL;
		else if (cond_exp(isdigit, s1, s2, &i, &k)) NULL;
		else s2[k++] = s1[i++];
	}
	s2[k] = '\0';
	return s2;
}

int cond_exp(int (*func)(int), char s1[], char s2[], int *i, int *k)
{
	//return value to indicate if it is applicable or not. 
	int q, n_steps; 

	for(q = *i, n_steps = 0; func(s1[q]) && s1[q+1] == '-' && func(s1[q+2]); q += 2, n_steps++);
	//q += 2 & not 3 because it can be the case such as a-b-c (b in index 2)
	if (!n_steps) 
		return 0;
	else
	{
		for(int g = 0; g < n_steps; g++)
			for (int j = s1[(2*g) + (*i)]; j < s1[(2*(g+1)) + (*i)]; j++) //k tracks s2
				s2[(*k)++] = j;
		(*i) = q; //index of char right after '-'(ex: if "a-d", q is index of d) 
		//need to skip correct numb of chars (consider NO i++ in main expand() for loop)
		return 1;
	}
}

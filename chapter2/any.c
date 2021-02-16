#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t any(char s1[], char s2[])
{
	uint32_t s2_null, j;
	for(s2_null = 0; s2[s2_null++] != '\0';);
	for(uint32_t i = 0; s1[i] != '\0'; i++)
	{
		for(j = 0; j < s2_null && s2[j] != s1[i]; j++);
		if(j < s2_null) {return i;}
	}
	return -1; //s1 contains no chars that are in s2.
}

int main(int argc, char *argv[])
{
	if(argc > 2) 
	{
		printf("any(%s, %s) = ", argv[1], argv[2]);
		printf("%d\n", any(argv[1], argv[2]));
	}
	else {printf("Usage %s <string1> <string2>\n", argv[0]); exit(42);}
	return 0;
}

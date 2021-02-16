#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

char *squeeze(char s1[], char s2[]) 
//delete char in s1 if in s2
{
	uint32_t null_s2, j;
	for(null_s2 = 0; s2[null_s2++] != '\0';);
	for(uint32_t i = 0; s1[i] != '\0'; i++)
	{
		for(j = 0; j < null_s2 && s2[j] != s1[i]; j++);
		if(j < null_s2) {s1[i] = ' ';} //' ' == delete
	}
	return s1;
}

int main(int argc, char *argv[])
{
	if(argc > 2) 
	{
		printf("sqeeze(%s, %s) = ", argv[1], argv[2]);
		printf("%s\n", squeeze(argv[1], argv[2]));
	}
	else {printf("Usage %s <string1> <string2>\n", argv[0]); exit(42);}
	return 0;
}

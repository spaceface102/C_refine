#include <stdio.h>

char *lower(char str[])
{
	for(int i = 0; str[i] != '\0'; i++)
		str[i] += (str[i] >= 'A' && str[i] <= 'Z') ? 0x20 : 0;
	return str;
}

int main(int argc, char *argv[])
{
	(argc > 1) ? printf("%s\n", lower(argv[1])) : 
	printf("Usage %s <string>\n", argv[0]);
	return 0;
}

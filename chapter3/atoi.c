#include <stdio.h>
#include <ctype.h>

#define MIN_ARGS 1
#define USAGE "Usage %s <integer>\n"

int atoi(char s[])
{
	int i, n, sign;
	for (i = 0; isspace(s[i]); i++);
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for(n = 0; isdigit(s[i]); i++)
		n = n*10 + (s[i] - '0');
	return n*sign;
}

int main(int argc, char *argv[])
{
	(argc > MIN_ARGS) ? printf("%d\n", atoi(argv[1])) : printf(USAGE, argv[0]);
	return 0;
}

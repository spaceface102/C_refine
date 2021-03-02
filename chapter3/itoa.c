#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *itoa(int n);
void kr_itoa(int n, char s[]);
void reverse(char s[]);
void add_blank(char s[], int n);

int main(int argc, char *argv[])
{
	char *test, kr[12];
	test = itoa(0x80000000);
	printf("%s\n", test);
	free(test);

	kr_itoa(0x80000000, kr);
	printf("%s\n", kr);

	char j[1000] = "Get god on the phone, said it won't be long";
	add_blank(j, 4);
	printf("%s\n", j);

	memset(kr, 0, 12);
	kr_itoa(-123, kr);
	add_blank(kr, 10);
	printf("%s\n", kr);
	return 0;
}

char *itoa(int n)
{
	//10 max digits 32 bit, 1 for sign, 1 for null char
	char *s = (char *)malloc(12*sizeof(char));
	int i = 0, sign = (n<0) ? 1 : 0;
	s[i++] = abs(n%10) + '0'; n /= 10;
	n = (sign) ? -n : n;
	for(;n > 0; n /= 10)
		s[i++] = n%10 + '0';
	if (sign)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	return s;
}

void kr_itoa(int n, char s[])
{
	int i, sign;
	
	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do{
		s[i++] = n % 10 + '0';
	} while((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	reverse(s);
}

void add_blank(char s[], int n)
{
	//make sure that string's min length == n; if length >= n, do nothing
	int len = strlen(s), add, sign = 0;
	if ((add = n - len) > 0)
	{
		if (s[0] == '-')
			sign = 1;	
	/* Altough it seems to work, the safer way to go about it
	is using the memmove func*/
	//memcpy(s+n, s, len+1);
	
	/*This function first copies bytes into a new array and then
	pushes them on to the new destination, this is a safer option
	to the above memcpy func, although be aware if you are not using
	pointers that overlap, just use memcpy as the intermediate copying
	stage in memmove to make sure nothing unexpected happens is a whole
	nother step that will slow down processing.*/
	memmove(s+add+sign, s+sign, len+1); //len+1 make sure to keep NULL char
	//sign leaves '-' in place
	memset(s+sign, '0', add);
	}

}

void reverse(char s[])
{
	int len = strlen(s);
	char temp;
	for(int i = 0; i < len/2; i++)
	{
		temp = s[i];
		s[i] = s[len-i-1];
		s[len-i-1] = temp;
	}
}

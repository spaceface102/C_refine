#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000
#define MINARG 2
void itob(int n, char s[], int b);
void reverse(char s[]);

int main(int argc, char *argv[])
{
	char s[SIZE];
	if (argc > MINARG){
		itob(atoi(argv[1]), s, atoi(argv[2]));
		printf("%s\n", s);}
	else
		printf("Usage %s <integer> <base>\n", argv[0]);
	return 0;
}

void itob(int n, char s[], int b)
{	//n = num, s == output str, b == base
	if(b < 0 || b > 16 || b == 1){
		printf("You smoking some shit chief :/\n");
		return;}

	static const char table[16] = 
	{'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int i = 0, sign = (n<0) ? 1 : 0;
	//do this to be able to represent largest numb in 2s comp
	//problem if convert to positive imideatly!
	s[i++] = table[abs(n%b)]; n /= b;
	n = (sign) ? -n : n;
	for(;n > 0; n /= b)
		s[i++] = table[n%b];
	if(b == 16)
		/*use x0 instead of 0x because of 
		needing to reverse string at the end*/
		memcpy(s + i, "x0", 2), i += 2;
	if (sign)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

void reverse(char s[])
{
	char temp;
	int len = strlen(s);
	for(int i = 0; i < len/2; i++)
	{
		temp = s[i];
		s[i] = s[len-i-1];
		s[len-i-1] = temp;
	}
}

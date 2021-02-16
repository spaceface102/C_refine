#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h> //toupper();

uint64_t htoi(char hex[])
{
	uint8_t opt_format = 0; //"0x" or "0X"
	uint64_t out = 0;

	if(hex[0] != '\0' && hex[0] == '0') //"0x" hex[0] = '0'...hex[1] = 'x' or 'X'
		//do +1 since... if statement is true, want to start char array at index 2
		//else if false, want to skip over the leading zero assured from the first
		//if statment. Else, opt_format will be zero.
		opt_format = (hex[1] != '\0' && (hex[1] == 'x'|| hex[1] == 'X')) + 1;

	for(uint8_t i = opt_format; (hex[i] = toupper(hex[i])) != '\0'; i++)
	{
		out = out*16;
		if(hex[i] >= '0' && hex[i] <= '9') {out += hex[i] - '0';}
		else if(hex[i] >= 'A' && hex[i] <= 'F') {out += hex[i] - 'A' + 10;}
	}		
	return out;
}

int main(int argc, char *argv[])
{
	if (argc > 1) {printf("%s = %ld\n", argv[1], htoi(argv[1]));}
	else {printf("Usage: %s <hex_numb>\n", argv[0]); exit(42);}
	return 0;
}

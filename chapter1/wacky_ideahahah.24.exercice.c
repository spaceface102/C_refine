#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(void)
{	
	//don't use array for these bc it is more readable like so
	uint8_t paren, brack, braces, squote, dquote, comm;
	paren=brack=braces=squote=dquote=comm=0xff;
	//in ascii opening symbol comes before closing 
	paren -= '(' + (')' - '(');
	brack -= '[' + (']' - '[');
	braces -= '{' + ('}' - '{');
	squote -= ''';
	dquote -= '"';
	comm -= 
	/*the idea is to set up the var values such that
	in the event that there is an opening pair, but
	not a closing pair the value of var would be
	something, not
	return 0;
}

#include <stdio.h>

/*If you have a string long to represent in
just one single line, you can always just make
a new string with sepertae identifing "". This
is in large part due to the limitation that you
are not allowed to have a new line mid " ". So 
instead of having multiple lines of printf, you
can one single printf whose strings are concatinated
at compile time. */

int main(void)
{
	printf("hello,"" world"
		  " I wonder if this will work too\n"
		  "Or this?\n"
		 /* "This should not		  
		 work" Since string is seperated into two lines.*/);
	/* Old way to go about doing this.
	printf("hello");
	printf(" world");
	printf(" I wonder if this will work too\n");
	printf("Or this?\n"); */
	return 0;
}	

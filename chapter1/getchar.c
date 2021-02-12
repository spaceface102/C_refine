#include <stdio.h>

int main(void)
{
	char c;
	while (c = getchar() != '\t') //EOF not working for me...
	{	putchar(c);
		if (c == ' ')
			{while ( (c = getchar()) == ' '); putchar(c);}
	}
	return 0;
}
//NOTES
/*takes in a file stream and does not ask 
for a new file stream until it is already
done with the current one. So it is init
like scanf, but the curious thing about it
is that it know if there is still more data
to be read from the file stream. When it has
finished reading each char one by one, it
finally ask for some more of that juciy data*/

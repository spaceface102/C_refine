#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void repeat(char c, int times);
void dots(int num_dots, double sleep_time); 


int main(int argc, char *argv[])
{
	int times = (argc > 1) ? atoi(argv[1]) : 3;
	int num_dots = (argc > 2) ? atoi(argv[2]) : 3;
	double sleep_time = (argc > 3) ? atof(argv[3]) : 1;

	printf("Loading");
	for(int i = 0; i < times; i++)
		dots(num_dots, sleep_time);

	if (argc <= 3)
		printf("\nUsage: <times_repeat> <num_dots> <sleep_time>\n");
	return 0;
}

void dots(int num_dots, double sleep_time) 
{
	/*with fflush. Sleep for one second in order to not instantly display the next
	'.' so it looks empty for a bit*/
	sleep(sleep_time);
	for(int j = 0; j < num_dots; j++)
	{
		printf("."); 
		//https://stackoverflow.com/questions/338273/why-does-printf-not-print-anything-before-sleep
		/*"The buffer isn't flushed by the time sleep is called so nothing is displayed, when the 
		program exits all streams are automatically flushed which is why it prints right before exiting.
		Printing a newline will usually cause the stream to be flushed, alternatively you could use the
		fflush function:"*/
		fflush(stdout); 
		sleep(sleep_time);
	}
	/*return the cursor to start, fill in spaces with 'blanks' aka spaces
	then once more return cursor to start, and finally ensure displaying with fflush
	I do it like this since \b is non destructive on my terminal, and more or
	less just shifts the cursor back to the left*/
	repeat('\b', num_dots);
	repeat(' ', num_dots);
	repeat('\b', num_dots);
	fflush(stdout);
}

void repeat(char c, int times)
{
	for(int i = 0; i < times; i++)
		printf("%c", c);
}

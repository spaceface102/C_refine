#include <stdio.h>
#include <stdarg.h> //used for variable number of arguments

typedef struct a_struct{
	int track;
	int somebs;
	float trash;
	char hello[0xff];
} a_struct;

double sum(int num, ...);//need to have at least one required argument!
void init_a_struct(int num, ...);



int main(void)
{
	double result = sum(2, 3.14159265359, 2.71828182846);
	printf("%lf\n", result);	

	a_struct x, y, z, a, b, c;
	x.track = 0xfeed;
	init_a_struct(6, &x, &y, &z, &a, &b, &c);
	return 0;
}

/*the required argument (in this case int num) is used
to relay some information about the other args 

	here a good idea would be to use num to indicate
	how many numbers we wish to sum up */
double sum(int num, ...)//... means it can be multiple other args
{
	//accesing agruments using  va_start, va_arg, va_end
	double out = 0.0;
	va_list args; //variable
	va_start(args, num); //(va_list, name of last required argument)
	/*As Jacob Sorber explains, va_start is setting a pointer to where
	the varaible arguments are stored; it might be intresting to check
	this out with a deuger */
	for(int i = 0; i < num; i++)
	{
		out += va_arg(args, double); //this is used to get the arguments one by one
		/*we have to also pass what type we expect the agrs to be; I want to add
		integers so I will be using int, but if I wanted to add floating point
		numbers I would use double
			Professor Sorber also notes that the types must be "self promoting";
			I am not completly sure that means, but I probably want to look that up
				Just following his advice, no chars, no short, no floats*/

		/*compile error message when tried to pass use float in va_arg:
		unlimited_args.c: In function ‘sum’:
		unlimited_args.c:28:23: warning: ‘float’ is promoted to ‘double’ when passed through ‘...’
		   28 |   out += va_arg(args, float); //this is used to get the arguments one by one
		         |                       ^
				 unlimited_args.c:28:23: note: (so you should pass ‘double’ not ‘float’ to ‘va_arg’)
				 unlimited_args.c:28:23: note: if this code is reached, the program will abort
		And when ran output is:
		$ llegal instruction
		*/
	}
	va_end(args); //apperently not necessary with glang and gcc, but for portability good idea
	return out;
}


void init_a_struct(int num, ...) //pass in 'numbs' pointer
{
	va_list args;
	va_start(args, num); //provide last req arg
	for(int i = 0; i < num; i++)
	{
		//the data type being used is a_struct * aka a_struct pointer
		a_struct *temp = va_arg(args, a_struct *);
		temp->track = 0;
		temp->somebs = 0;
		temp->trash = 0.0;
	}
	va_end(args); //apperently not necessary with glang and gcc, but for portability good idea
}

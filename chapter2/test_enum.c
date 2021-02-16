#include <stdio.h>
//enum is good replacement for some sort of names that
//are order, and inriment by one, and are integer valges
//CAN NOT use floats

enum gang{k = 128LU, gg = 0x21u};
run()
{printf("Run: %d\n", k); return 23LU;}

int main(void)
{
	enum complex{e = 'g', pi = 3};
	/*enum comp{j = "a", fsd = 128};
	the reason that doesn't work, is that
	"a" is an array of chars, = ['a', '\0']...
	enums only take in integers, and that is it.*/
	enum gang{k = 9090LU, gg = 0x21u};
	/*same like with any variable, you can define
	the same variable, with the same name, even with
	the same values, and everything will be alright*/

	//enum jjj{k = 18, d = 12};
	/*Although the enum name is different, the elements
	inside it (at least k) are the same and the
	language does not know what to do.*/
	printf("Inside main: %d\n", k); 
	run();
	return 0;
}

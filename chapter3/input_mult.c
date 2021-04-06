#include <stdio.h>
//https://stackoverflow.com/questions/5240789/scanf-leaves-the-new-line-char-in-the-buffer
//https://stackoverflow.com/questions/2979209/using-fflushstdin
int main(void)
{
	int w, x, y, z;
	int j;
	scanf("%d\n%d\n%d\n%d", &w, &x, &y, &z);
	printf("%d\n%d\n%d\n%d\n", w, x, y, z);
	/*the reason for using " hello" instead of "hello" is note that
	the first scanf, when inputing the data, after every data input
	you will have a new line char, but since I didn't put a trailing
	'/n', the io stream will still have that final '\n' that the user
	inputs when they input data. Having " hello" tells scanf to ignore
	the previous blank space which in this case would be '\n'. 
	I would seem like adding '\n' at the very end of the scanf would 
	fix the problem, but I tried it and it didn't seem to work...
	Experiment more boy!*/
	scanf(" hello  %d", &j);
	printf("\n\n%d\n", j);
	return 0;
}

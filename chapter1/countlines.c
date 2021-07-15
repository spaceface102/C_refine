#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE* file;
    long countNewLines;
    long countBlanks;
    long countTabs;
    int c;

    if (argc > 1)
        file = fopen(argv[1], "r");
    else
    {
        printf("Usage: %s <file name>\n", argv[0]);
        return 1;
    }

    if (!file)
    {
        printf("Huston, we have a problem!\n");
        return 1;
    }
    
    for (countNewLines = countBlanks = countTabs = 0; (c = getc(file)) != EOF;
         countNewLines += (c == '\n'), countBlanks += (c == ' '),
         countTabs += (c == '\t'))
        ;

    printf("%s summary:\n", argv[1]);
    printf("Number of lines:\t%ld\n", countNewLines);
    printf("Number of spaces:\t%ld\n", countBlanks);
    printf("Number of tabs:\t\t%ld\n", countTabs);

    return 0;
}
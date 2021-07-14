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
    printf("Number of line in %s: %ld\n", argv[1], countNewLines);
    printf("Number of spaces in %s: %ld\n", argv[1], countBlanks);
    printf("Number of tabs in %s: %ld\n", argv[1], countTabs);

    return 0;
}
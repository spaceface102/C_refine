#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE* file;
    long countNewLine;
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
    for (countNewLine = 0; (c = getc(file)) != EOF; countNewLine += (c == '\n'))
        ;
    printf("Number of line of %s: %ld\n", argv[1], countNewLine);

    return 0;
}
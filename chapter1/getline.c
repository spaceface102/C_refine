#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE *file;
    char *aLine;
    size_t numCharsLine;

    file = NULL; aLine = NULL; numCharsLine = 0;
    file = (argc > 1) ? fopen(argv[1], "r") : stdin;
    
    if (!file)
    {
        printf("Huston, we have a problem\n");
        return 1;
    }

    getline(&aLine, &numCharsLine, file);
    printf("Input: %s", aLine);
    printf("Size of the char array: %lu\n", numCharsLine);

    fclose(file);
    free(aLine);
    return 0;
}
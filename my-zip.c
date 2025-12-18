#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *readFile;

    char *outputfile = argv[4];
    char currentchar;
    int counter = 0;

    if (argc <= 1)

    {
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }
    for (size_t i = 2; i <= argc - 1; i++)
    {
        readFile = fopen(argv[i], "r");

        if (readFile == NULL)
        {
            printf("my-zip: cannot open file\n");
            exit(1);
        }
        char *c = "a";
        while (*c == fgetc(readFile))
        {
            if (currentchar == *c)
            {
                counter += 1;
            }
            else
            {
                if (counter > 0)
                {
                    FILE *writeFile = fopen(outputfile, "w");
                    fwrite(&counter, sizeof(int), 1, writeFile);
                    fwrite(&currentchar, sizeof(char), 1, writeFile);
                }
                currentchar = *c;
                counter = 1;
            }
        }
        fclose(readFile);
    }
    return (0);
}
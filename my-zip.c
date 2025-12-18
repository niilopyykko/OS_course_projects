#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    char *buffer = 0;    // for getline
    size_t bufsize = 32; // for getline
    FILE *fp;

    char inputfile = argv[2];
    char outputfile = argv[3];

    if (argc <= 1)
    {
        prinf("my-zip: file1 [file2 ...]\n");
        return 1;
    }
    for (size_t i = 2; i <= argc - 1; i++)
    {
        fp = fopen(argv[i], "r");

        if (fp == NULL)
        {
            printf("my-zip: cannot open file\n");
            exit(1);
        }

        while (getline(&buffer, &bufsize, fp) != -1)
        {
            int counter = 0;
            char currentchar = buffer[i];
            while (currentchar == buffer[i + 1])
            {
                counter += 1;
            }
            FILE *fileToWriteTo = fopen(outputfile, "w");
            fwrite("%d%c", counter, currentchar);
        }
        fclose(fp);
    }
    free(buffer);
    return (0);
}
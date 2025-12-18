#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    char *buffer = 0;    // for getline and fgets
    size_t bufsize = 32; // for getline and fgets
    char *hakusana = argv[1];
    FILE *fp;

    if (argc <= 1)
    {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    if (argc == 2)
    {
        fp = fgets(*buffer, bufsize, stdin);
    }
    for (size_t i = 2; i <= argc - 1; i++)
    {
        fp = fopen(argv[i], "r");

        if (fp == NULL)
        {
            printf("cannot open file\n");
            exit(1);
        }

        while (!feof(fp))
        {
            getline(&buffer, &bufsize, fp);
            if (strcmp(buffer, hakusana) == 1)
            {
                printf("%s", buffer);
            }
        }
        printf("\n");
        fclose(fp);
    }

    return (0);
}

#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void main(char *argv[])
{
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("cannot open file\n");
        exit(1);
    }
    while (!feof(fp))
    {
        char buffer[100];
        fgets(buffer, 100, fp);
        printf(buffer);
    }
    fclose(fp);
}
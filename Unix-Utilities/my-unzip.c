#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *readFile;

    int amount = 0; // amount of character
    char character; // what character

    if (argc < 2) // EROR MESAGE
    {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    for (size_t i = 1; i < argc; i++) // loop through files
    {
        readFile = fopen(argv[i], "r"); // open file

        if (readFile == NULL) // if no file or something
        {
            printf("my-unzip: cannot open file\n");
            exit(1);
        }
        while (fread(&amount, sizeof(int), 1, readFile) && // while can read file
               fread(&character, sizeof(char), 1, readFile))
        {
            for (size_t i = 0; i < amount; i++) // for amount of char
            {
                printf("%c", character); // print char
            }
        }
        fclose(readFile); // close file
    }
    return (0);
}
#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void fileHandling(FILE *in, FILE *out);

int main(int argc, char *argv[])
{
    // input and output filenames
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];

    FILE *in = stdin;
    FILE *out = stdout;

    // IF NO ARGUMENTS
    if (argc <= 1)
    {
        in = stdin;
    }

    // IF ONLY 1 ARGUMENT //lol also works for 3 argument file read
    if (argc >= 2)
    {
        in = fopen(inputFileName, "r");
        if (in == 0)
        // IF FILE OPEN FAIL
        {
            fprintf(stderr, "error: cannot open file 'input.txt'\n");
            exit(1);
        }
    }

    // IF 2 ARGUMENTS
    if (argc == 3)
    {
        // COMPARE INPUT OUTPUT FILENAMES
        if (strcmp(inputFileName, outputFileName) == 0)
        {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        out = fopen(outputFileName, "w");
        // IF FILE OPEN FAIL
        if (out == 0)
        {
            fprintf(stderr, "error: cannot open file 'input.txt'\n");
            exit(1);
        }
    }

    // IF MORE THAN 2 ARGUMENTS
    else if (argc > 3)
    {
        printf("usage: reverse <input> <output>\n");
        exit(1);
    }

    fileHandling(in, out);
    fclose(in);
    fclose(out);

    return (0);
}

void fileHandling(FILE *in, FILE *out)
{
    char *buffer = 0;    // for getline
    size_t bufsize = 32; // for getline

    char **lines = NULL; // pointers for lines
    int count = 0;       // amount of read liens

    while (getline(&buffer, &bufsize, in) != -1)
    {
        char **tmp = realloc(lines, (count + 1) * sizeof(char *));
        if (tmp == NULL)
        {
            fprintf(stderr, "realloc failed\n");
            exit(1);
        }

        lines = tmp;
        lines[count] = malloc(strlen(buffer) + 1);
        if (lines[count] == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        strcpy(lines[count], buffer);
        count++;
    }
    for (int i = count - 1; i >= 0; i--)
    {
        fprintf(out, "%s", lines[i]);
        free(lines[i]);
    }
    free(buffer);
    return;
}

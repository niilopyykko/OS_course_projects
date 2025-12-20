#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void fileHandling(FILE *in, FILE *out); // function declaration

int main(int argc, char *argv[])
{
    // input and output filenames
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];

    FILE *in = stdin;   // make screen text capture default
    FILE *out = stdout; // make screen text print default

    // IF NO ARGUMENTS
    if (argc <= 1)
    {
        in = stdin; // read input from user input in terminal or pipe
    }

    // IF ONLY 1 ARGUMENT //lol also works for 3 argument file read
    if (argc >= 2)
    {
        in = fopen(inputFileName, "r"); // open file as input source for in variable
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
        out = fopen(outputFileName, "w"); // make output get values from file
        // IF FILE OPEN FAIL
        if (out == 0)
        {
            fprintf(stderr, "error: cannot open file 'input.txt'\n");
            exit(1);
        }
    }

    // IF MORE THAN 2 ARGUMENTS
    if (argc > 3)
    {
        printf("usage: reverse <input> <output>\n");
        exit(1);
    }

    fileHandling(in, out); // call funktion with proper paths for in(file or userinput) and out(screen or file)
    fclose(in);            // close in
    fclose(out);           // close out

    return (0);
}

void fileHandling(FILE *in, FILE *out)
{
    char *buffer = 0;    // for getline
    size_t bufsize = 32; // for getline

    char **lines = NULL; // pointers for lines
    int count = 0;       // amount of read liens

    while (getline(&buffer, &bufsize, in) != -1) // read until new line in file
    {
        char **tmp = realloc(lines, (count + 1) * sizeof(char *)); // dynamically handle amount of lines
        if (tmp == NULL)
        {
            fprintf(stderr, "realloc failed\n");
            exit(1);
        }

        lines = tmp;                               // continue to dynamically allocate space for lines
        lines[count] = malloc(strlen(buffer) + 1); // dynamically read data to line (about unlimited lenght)
        if (lines[count] == NULL)
        {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        strcpy(lines[count], buffer); // use buffer for dynamically storing lines with strings
        count++;
    }
    for (int i = count - 1; i >= 0; i--) // loop startging from end i
    {
        fprintf(out, "%s", lines[i]); // print lines with i index starting from end
        free(lines[i]);               // free dynamically allocated memory slot i at the end of  for loop
    }
    free(buffer); // free dynamically allocated entire buffer at the end of while
    free(lines);  // free dynamically allocated entire lines at the end of while //found using valgrind
    return;
}

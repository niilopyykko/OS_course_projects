#include <stdio.h>

int main(int argc, char *argv[])
{

    if (argc == 0)
    {
        FILE *userInput = stdin;
    }
    else if (argc == 1)
    {
        const char inputFile = *argv[0];

        FILE *userInput = stdin;
    }

    else if (argc == 2)
    {
        const char outputFile = *argv[1];
    }

    else
    {
        printf("wery broken c-code ah yes");
    }

    // REVERSE LINES

    // WRITE FILE
    FILE *WriteFile;
    WriteFile = fopen(outputFile, "w");

    exit(1);
}

char readFile(inputFile)
{
    // OPEN FILE
    FILE *readFile;
    readFile = fopen(inputFile, "r");

    // READ FILE
    getline(&buffer, &size, stdin);

    return (0)
}

#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *readFile;

    int previousCharacter = EOF; // imaginery end of previous file
    int currentCharacter = 0;    // start
    int counter = 0;             // amount of characters

    if (argc < 2) // error not enough arguments
    {
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }

    for (size_t i = 1; i < argc; i++) // for each file
    {
        readFile = fopen(argv[i], "r"); // file open

        if (readFile == NULL) // error
        {
            printf("my-zip: cannot open file\n");
            exit(1);
        }
        while ((currentCharacter = fgetc(readFile)) != EOF) // while not at the end of the file
        {
            if (counter == 0) // if first time we see this character
            {
                previousCharacter = currentCharacter; // we have seen it
                counter = 1;                          // once
            }
            else if (previousCharacter == currentCharacter) // if this was seen last round
            {
                counter++; // we have seet it one more time
            }
            else // if this character is a new character we print the previous character (example: aa[b]bb) here we compare "a" != "b" but previous is "a" and counter is 2
            {
                fwrite(&counter, sizeof(int), 1, stdout);            // write counter (example 2)
                fwrite(&previousCharacter, sizeof(char), 1, stdout); // write what character (example "a")
                previousCharacter = currentCharacter;                // reset values for next round with current char as last rounds char (example: prev was "a", now it is "b")
                counter = 1;                                         // reset values for next round with counter at 1 for first seen amount (example: prev was "2" times "a", now it is "1" times "b")
            }
        }
        fclose(readFile); // close file
    }
    if (counter > 0) // for last file and last row/line/char
    {
        fwrite(&counter, sizeof(int), 1, stdout);            // print amount
        fwrite(&previousCharacter, sizeof(char), 1, stdout); // what char to print
    }
    return (0); // end of program
}
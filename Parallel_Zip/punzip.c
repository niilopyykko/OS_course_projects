#define _GNU_SOURCE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

pthread_mutex_t output_lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    const char *filename;
} fileSpecs;

void *worker(void *arg)
{
    fileSpecs *file = arg; // worker input back to chuck structure
    FILE *readFile = fopen(file->filename, "rb");

    if (readFile == NULL)
    {
        printf("punzip: cannot open file\n");
        exit(1);
    }

    int amount = 0;
    char character;

    while (fread(&amount, sizeof(int), 1, readFile) &&
           fread(&character, sizeof(char), 1, readFile))
    {
        pthread_mutex_lock(&output_lock);
        for (size_t i = 0; i < amount; i++)
        {
            printf("%c", character);
        }
        pthread_mutex_unlock(&output_lock);
    }
    fclose(readFile);
    return NULL;
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }
    pthread_t workers[argc - 1]; // one thread for each file
    fileSpecs tasks[argc - 1];

    for (size_t i = 1; i < argc; i++)
    {
        tasks[i - 1].filename = argv[i];
        pthread_create(&workers[i], NULL, worker, &tasks[i]);

        for (size_t i = 0; i < argc - 1; i++)
        {
            pthread_join(workers[i], NULL);
        }
    }
    return (0);
}
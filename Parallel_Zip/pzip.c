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

typedef struct
{
    // FOR INPUT
    char *data;
    size_t start;
    size_t end;

    // worker buffer // FOR OUTPUT
    char *buff;
    size_t buffsize;

} chunk;

void *worker(void *arg)
{
    chunk *chunk = arg; // worker input back to chuck structure

    int previousCharacter = EOF;
    int currentCharacter = 0;
    int counter = 0;
    FILE *readFile = arg;

    while ((currentCharacter = fgetc(readFile)) != EOF)
    {
        if (counter == 0)
        {
            previousCharacter = currentCharacter;
            counter = 1;
        }
        else if (previousCharacter == currentCharacter)
        {
            counter++;
        }
        else
        {
            previousCharacter = currentCharacter;
            counter = 1;
        }
    }
    return NULL;
}
int main(int argc, char *argv[])
{
    int fd;
    char *addr;
    off_t offset, pa_offset;
    size_t length;
    struct stat sb;

    int availableThreads = get_nprocs(); // THIS TELLS THE PARALLELLISM^TM system how many cores/threads is available
    pthread_t workers[availableThreads];
    chunk chunks[availableThreads];

    for (size_t i = 1; i < argc; i++)
    {
        {
            fprintf(stderr, "%s file offset [length]\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
            handle_error("open");

        if (fstat(fd, &sb) == -1) /* To obtain file size */
            handle_error("fstat");

        offset = atoi(argv[2]);
        pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
        /* offset for mmap() must be page aligned */

        if (offset >= sb.st_size)
        {
            fprintf(stderr, "offset is past end of file\n");
            exit(EXIT_FAILURE);
        }

        if (argc == 4)
        {
            length = atoi(argv[3]);
            if (offset + length > sb.st_size)
                length = sb.st_size - offset;
            /* Can't display bytes past end of file */
        }
        else
        { /* No length arg ==> display to end of file */
            length = sb.st_size - offset;
        }

        addr = mmap(NULL, length + offset - pa_offset, PROT_READ,
                    MAP_PRIVATE, fd, pa_offset);
        if (addr == MAP_FAILED)
            handle_error("mmap");

        size_t chunk_size = length / availableThreads;

        for (size_t i = 1; i < availableThreads; i++)
        {
            chunks[i].data = addr;
            chunks[i].start = i * chunk_size;
            chunks[i].end = (i == availableThreads - 1); // pls keksi tähän jtn järkeä
            chunks[i].buff = malloc(chunks[i].end - chunks[i].start);
            chunks[i].buffsize = 0;
            pthread_create(&workers[i], NULL, worker, &chunks[i]);
        }
    }
    for (size_t i = 1; i < availableThreads; i++)
    {
        pthread_join(workers[i], NULL);
        write(STDOUT_FILENO, chunks[i].buff, chunks[i].buffsize);
        free(chunks[i].buff);
    }

    munmap(addr, length + offset - pa_offset);
    close(fd);

    exit(EXIT_SUCCESS);
    return (0);
}
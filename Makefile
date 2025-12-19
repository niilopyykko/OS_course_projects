# Makefile

# REVERSE
reverse: reverse/reverse.o
	gcc -o reverse_bin reverse/reverse.o

reverse/reverse.o: reverse/reverse.c
	gcc -c reverse/reverse.c -Wall -Werror -o reverse/reverse.o


# UNIX UTILITIES
utils: my-cat my-grep my-unzip my-zip

my-cat: Unix-Utilities/my-cat.o
	gcc -o my-cat Unix-Utilities/my-cat.o

my-grep: Unix-Utilities/my-grep.o
	gcc -o my-grep Unix-Utilities/my-grep.o

my-unzip: Unix-Utilities/my-unzip.o
	gcc -o my-unzip Unix-Utilities/my-unzip.o

my-zip: Unix-Utilities/my-zip.o
	gcc -o my-zip Unix-Utilities/my-zip.o

Unix-Utilities/my-cat.o: Unix-Utilities/my-cat.c
	gcc -c Unix-Utilities/my-cat.c -Wall -Werror -o Unix-Utilities/my-cat.o

Unix-Utilities/my-grep.o: Unix-Utilities/my-grep.c
	gcc -c Unix-Utilities/my-grep.c -Wall -Werror -o Unix-Utilities/my-grep.o

Unix-Utilities/my-unzip.o: Unix-Utilities/my-unzip.c
	gcc -c Unix-Utilities/my-unzip.c -Wall -Werror -o Unix-Utilities/my-unzip.o

Unix-Utilities/my-zip.o: Unix-Utilities/my-zip.c
	gcc -c Unix-Utilities/my-zip.c -Wall -Werror -o Unix-Utilities/my-zip.o


# PARALLEL ZIP
parallel: pzip punzip

pzip: Parallel_Zip/pzip.o
	gcc -o pzip Parallel_Zip/pzip.o -pthread

punzip: Parallel_Zip/punzip.o
	gcc -o punzip Parallel_Zip/punzip.o

Parallel_Zip/pzip.o: Parallel_Zip/pzip.c
	gcc -c Parallel_Zip/pzip.c -Wall -Werror -o Parallel_Zip/pzip.o

Parallel_Zip/punzip.o: Parallel_Zip/punzip.c
	gcc -c Parallel_Zip/punzip.c -Wall -Werror -o Parallel_Zip/punzip.o


# CLEAN
clean:
	rm -f reverse_bin my-cat my-grep my-unzip my-zip pzip punzip
	rm -f reverse/*.o Unix-Utilities/*.o Parallel_Zip/*.o

// Lab 09 Written by Rifa Jamal COMP1521
// file_sizes.c, which is given one or more 
// filenames as command line arguments. 
// It should print one line for each filename which 
// gives the size in bytes of the file. It should also 
// print a line giving the combined number of bytes in the files.

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int stat_file(char *pathname); 

int main(int argc, char *argv[]) {

    long size = 0;

    for (int arg = 1; arg < argc; arg++) {
        struct stat s;
        if (stat(argv[arg], &s) != 0) {
            perror(argv[arg]);
            exit(1);
        }

        printf("%s: %ld bytes\n",argv[arg], (long)s.st_size);
        size+= (long)s.st_size;
    }

    printf("Total: %ld bytes\n", size);

    return 0;

}
        

// Lab 08 COMP1521
// Written by Rifa Jamal z5311190

// Write a C program, create_integers_file, which takes 3 arguments:
// 1. a filename,
// 2. the beginning of a range of integers, and
// 3. the end of a range of integers;
// and which creates a file of this name containing the specified integers

// program also prints a suitable error message 
// if given the wrong number of arguments, or if the file can not be created.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE * outfile = fopen(argv[1], "w");

    // change string character to int
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);

    if (outfile == NULL) {
        //perror(argv[1]); -> both are same
        perror(argv[3]);
        exit(1);
    }

    for(int i = start; i <= end; i++) {
        fprintf(outfile, "%d\n", i);
    }

    fclose(outfile);
    return 0;
}




// Lab 08 COMP1521
// Written by Rifa Jamal z5311190

// C program, print_bytes, which takes one argument, a filename, 
// and which should should read the specifed file 
// and print one line for each byte of the file. 
// The line should show the byte in decimal and hexadecimal. 
// If that byte is a an ASCII printable character, its ASCII value should also be printed.

// Assume ASCII printable characters are those for which 
// the ctype.h function isprint(3) returns a non-zero value.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

    FILE * outfile = fopen(argv[1], "r");

    if (outfile == NULL) {
        perror(argv[1]);
        exit(1);
    }

    long bytes_read = 0;
    int byte;

    while ((byte = fgetc(outfile)) != EOF) {
        printf("byte %4ld: %3d 0x%02x", bytes_read, byte, byte);

        if (isprint(byte)) {
            printf(" '%c'", byte);
        }
        printf("\n");
        bytes_read++;
    }

    fclose(outfile);
    return 0;
}
// Lab 08 COMP1521
// Written by Rifa Jamal z5311190

// C program, hidden_strings, which takes one argument, a filename; 
// it should read that file, 
// and print all sequences of length 4 or longer of consecutive byte values 
// corresponding to printable ASCII characters. 
// In other words, your program should read through the bytes of the file, 
// and if it finds 4 bytes in a row containing printable characters, 
// it should print those bytes, and any following bytes containing ASCII printable characters.

// Print each sequence on a separate line.
// Assume ASCII printable characters are those for which the ctype.h function isprint(3) returns a non-zero value.
// Do not read the entire file into an array.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

    FILE * outfile = fopen(argv[1], "r");
    if (outfile == NULL) {
        perror(argv[1]);
        exit(1);
    }

    int buffer[3];
    int printable_characters_read = 0;
    int byte = 0;

    while ((byte = fgetc(outfile)) != EOF) {
        if (isprint(byte)) {
            if (printable_characters_read <= 2) {
                buffer[printable_characters_read] = byte;
                printable_characters_read++;
            } else {
                printf("%c%c%c%c", buffer[0], buffer[1], buffer[2], byte);
                while (((byte = fgetc(outfile)) != EOF) && isprint(byte)) {
                    printf("%c", byte);
                }
                printable_characters_read = 0;
                printf("\n");
            }
        } else {
            printable_characters_read = 0;
        }
    }

    fclose(outfile);
    return 0;

}
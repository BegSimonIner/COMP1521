// Weekley Test 8 
// Written by Rifa Jamal z5311190

// non_ascii.c, which takes one argument, a filename.
// It should print one line of output.
// If the file contains a non-ASCII byte, non_ascii.c should print the location of the first non-ASCII byte. Use the same format as the example below.
// If the file contains no non-ASCII byte non_ascii.c should print a message indicating this.
// Assume a byte is non-ASCII if it contains a value between 128..255 inclusive.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *outfile = fopen(argv[1], "r");

    if (outfile == NULL) {
        //perror(argv[1]); -> both are same
        perror(argv[3]);
        exit(1);
    }

    int pos = 0;
    int byte;

    while ((byte = fgetc(outfile)) != EOF){
        if (byte >= 128 && byte <= 255) {
            printf("%s: byte %d is non-ASCII\n", argv[1], pos);
            return 0;
        }
        pos++;
    }

    fclose(outfile);
    printf("%s is all ASCII\n", argv[1]);
    return 0;
}
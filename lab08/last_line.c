// SAMPLE SOLUTIONNNNNN

// Print the last line of a file without reading the entire file

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s: <file> <byte0> <byte1> ...\n", argv[0]);
        exit(1);
    }

    FILE *stream = fopen(argv[1], "r");
    if (stream == NULL) {
        fprintf(stderr, "%s: ", argv[0]);
        perror(argv[1]);
        exit(1);
    }

    // look backwards through the file for a '\n'
    // or start of the file
    // starting at the 2nd last byte

    long offset = -2;
    while (fseek(stream, offset, SEEK_END) == 0 && fgetc(stream) != '\n') {
        offset--;
    }

    // write out all bytes after the '\n' or start of file
    fseek(stream, offset + 1, SEEK_END);
    int byte;
    while ((byte = fgetc(stream)) != EOF) {
        fputc(byte, stdout);
    }

    fclose(stream);

    return 0;
}


//Write a C program, last_line, which takes one argument, a filename, and which should print the last line of that file.
// You program should not assume the last byte of the file is a newline character.
// Your program should handle extremely large files. It should not read the entire file. 
//As this is a challenge exercise, marks will not be awarded for programs which read the entire file.


// Note
//If the last byte of file is not '\n', you should print all bytes after the last '\n' byte.
// If there is no '\n' byte, you should print the entire file.
// If the last byte of the file is '\n', you should print every byte after the previous (second last '\n') '\n' byte.
// If there is no previous '\n' byte, you should print the entire file.
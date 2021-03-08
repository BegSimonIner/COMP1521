// Weekley Test 8 
// Written by Rifa Jamal z5311190

// leave_only_ascii.c, which takes one argument, a filename.
// leave_only_ascii.c should remove all non-ASCII bytes from the file.
// After it is run the file should contain only a ASCII bytes.
// It should print nothing on stdout. It should only change the file.
// Assume a byte is non-ASCII if it contains a value between 128..255 inclusive.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    /*
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        perror(argv[1]);
        exit(1);
    }

    char temp[strlen(argv[1])+1];
    strcpy(temp, argv[1]);

    FILE *output = fopen("temp", "w");
    if (output == NULL) {
        perror(argv[1]);
        exit(1); 
    }

    int byte;
    while ((byte = fgetc(input)) != EOF) {
        if (byte <= 127) {
            fputc(byte, output);
        }
    }
    fclose(input);
    fclose(output);

    //remove temporary file
    remove("temp");
    */

    FILE *output = fopen(argv[1], "r");
    
    if (output == NULL) {
        perror(argv[1]);
        exit(1);
    }

    FILE *temp = fopen("temp", "w");
    
    int byte;
    while ((byte = fgetc(output)) != EOF) {
        if (byte <= 127) {
            fputc(byte, temp);
        }
    }

    fclose(output);
    fclose(temp);

    FILE *change_file = fopen(argv[1], "w");
    FILE *read_temp = fopen("temp", "r");

    while ((byte =fgetc(read_temp)) != EOF) {
        fputc(byte, change_file);
    }

    fclose(read_temp);
    fclose(change_file);
    remove("temp");
   

    return 0;

}
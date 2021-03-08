// Weekley Test 8 
// Written by Rifa Jamal z5311190

// compare_file.c, which takes two arguments, both filenames. Compare_file.c should print one line of output.
// If the two files are different compare_file.c should print the location of the first byte whether they differ. 
// If the one file is shorter than the other but the bytes it contains are identical to the other file, 
// compare_file.c should print a message indicating this. Use the same format as the example below.
// If the 2 files contain exactly the same bytes compare_file.c should print a message indicating this.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    //check if only 2 files entered/ 3 arguments
    if (argc != 3) {
        fprintf(stderr, "Enter two files only\n");
        return 1;
    }
    
    FILE *file1 = fopen(argv[1], "r");

    if (file1 == NULL) {
        perror(argv[1]);
        exit(1);
    }

    FILE *file2 = fopen(argv[2], "r");

    if (file2 == NULL) {
        perror(argv[2]);
        exit(1);
    }

    int pos = 0;
    int i = 0;
    int byte1 = fgetc(file1);
    int byte2 = fgetc(file2);

    while (byte1 != EOF && byte2 != EOF && i == 0) {
        if (byte1 != byte2) {
            printf("Files differ at byte %d\n", pos);
            i++;
        }
        pos++;
        byte1 = fgetc(file1);
        byte2 = fgetc(file2);
    }
    
    if ((byte1 == EOF) && byte2 != EOF) {
        printf("EOF on %s\n", argv[1]);
        return 0;
    } else if (byte1 != EOF && byte2 == EOF) {
        printf("EOF on %s\n", argv[2]);
        return 0;
    } else if (i == 0) {
        printf("Files are identical\n");
    }

    fclose(file1);
    fclose(file2);
    return 0;

}


// SAMPLE SOLUTIONNNN

/*

// Print position of first non-ASCII byte in file

#include <stdio.h>
#include <stdlib.h>

int compare_files(char *pathname1, char *pathname2);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    return compare_files(argv[1], argv[2]);
}

int compare_files(char *pathname1, char *pathname2) {
    FILE *stream1 = fopen(pathname1, "r");
    if (stream1 == NULL) {
        perror(pathname1);
        return 1;
    }

    FILE *stream2 = fopen(pathname2, "r");
    if (stream2 == NULL) {
        perror(pathname2);
        return 1;
    }

    ssize_t byte_position = 0;
    int byte1, byte2;
    while (1) {
        byte1 = fgetc(stream1);
        byte2 = fgetc(stream2);
        if (byte1 != byte2 || byte1 == EOF) {
            break;
        }
        byte_position++;
    }

    if (byte1 == byte2) {
        printf("Files are identical\n");
    } else if (byte1 == EOF) {
        printf("EOF on %s\n", pathname1);
    } else if (byte2 == EOF) {
        printf("EOF on %s\n", pathname2);
    } else {
        printf("Files differ at byte %zd\n", byte_position);
    }

    fclose(stream1);
    fclose(stream2);
    return 0;
}

*/
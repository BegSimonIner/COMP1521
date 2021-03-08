// Lab 08 COMP1521
// Written by Rifa Jamal z5311190

// C program, create_binary_file, takes at least one argument: 
// a filename, 
// and subsequently, integers in the range 0…255 inclusive specifying byte values. 
// It should create a file of the specified name, containing the specified bytes.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {

// Make sure number of arguments is more than 1
assert(argc > 1);

FILE * outfile = fopen(argv[1], "w");
if (outfile == NULL) {
    perror(argv[1]);
    exit(1);
}

for (int i = 2; i < argc; i++) {
    fputc(atoi(argv[i]), outfile);
}
fclose(outfile);
return 0;

}

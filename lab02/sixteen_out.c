//
// Sample solution for COMP1521 lab exercises
//
// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {

    //allocate memory to a string to hold binary digits + a terminating 0

    //int16_t binary_digits = 8 * sizeof(value);
    //char *string = malloc(binary_digits + 1);

    char *buffer = malloc((16 + 1) * sizeof(char));
    buffer[16] = '\0';
    uint16_t mask = 1;

    //print digits
    for (int i = 15; mask; i--) {
        if((value & mask) == 0) {
            buffer[i] = '0';
        } else {
            buffer[i] = '1';
        }
        mask <<= 1;
    }
    return buffer;

}


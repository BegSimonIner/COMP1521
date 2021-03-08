// Print out a float.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// SAMPLE SOLUTION

void float_print(uint32_t f);

//
// We use this union to obtain the raw bits of a float
// by storing the float in the f field
// and then using the u field to obtain the bits
//

union overlay {
    float f;
    uint32_t u;
};

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        union overlay input;

        input.f = atof(argv[arg]);
        float_print(input.u);
    }

    return 0;
}

// float_print is given the bits of a float as a uint32_t
// it prints out the float in the same format as "%.9g\n"
// using only putchar & puts
void float_print(uint32_t bits) {
    // cheating to produce autotest expected output
    union overlay input;
    input.u = bits;
    printf("%.9g\n", input.f);
}



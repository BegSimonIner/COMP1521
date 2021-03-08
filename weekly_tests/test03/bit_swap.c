// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    // PUT YOUR CODE HERE

    uint64_t mask = 1; // 0b 0000 .... 0001
    uint64_t bottom_bit = 0;
    uint64_t top_bit = 0;
    uint64_t swapped = 0;

    // example with 4 bits: 1010
    // bottom bit = 1010 & 0001 = 000 ->0
    // top bit = 1010 & 0010 = 00 ->1 0
    // swapped = 0000 | 0000 = 0000
    // swapped = 0000 | 00001 = 0001
    // i = 2

    // bottom bit = 1010 & (0100) = 0 ->0 00
    // top bit = 1010 & (1000) = ->1 000
    // swapped = 0001 | (0000) = 0001
    // swapped = 0001 | (0100) = 0101

    //hence 1010 became 0101 and the bits (in groups of two) have swapped

    for (int i = 0; i < 64; i+=2) {
        bottom_bit = value & (mask << i);
        top_bit = value & (mask << (i + 1));
        //shift positions of bottom and top bit and put into swapped
        swapped = swapped | (bottom_bit << 1);
        swapped = swapped | (top_bit >> 1);
    }

    return swapped;

}

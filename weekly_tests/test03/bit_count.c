// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return how many 1 bits value contains
int bit_count(uint64_t value) {
    // PUT YOUR CODE HERE

    uint64_t mask = 1; // 0b 0000 .... 0001
    int count = 0;

    // how this works:
    // e.g. value = 0b 0101 0101
    // first iteration of for loop:
    // 0101 0101 & 0000 0001 = 0000 0001
    // count = 1
    // value >>= 1 -->  0010 1010

    //second iteration of for loop:
    //0010 1010 & 0000 0001 = 0000 0000
    // hence count is still 1
    // value = 0001 0101

    //and so on...

    while (value != 0) {
        if ((value & mask) == 1) {
            count++;
        }
        value >>= 1;
    }

    return count;
}

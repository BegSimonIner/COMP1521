// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    // PUT YOUR CODE HERE

    uint16_t mask = 0xff; //0b 0000 0000 1111 1111
    uint16_t swapped = 0; //0b 0000 0000 0000 0000

    //e.g. let value be 0000 0000 1111 1111
    swapped = mask & value; // 0b 0000 0000 1111 1111
    swapped <<= 8; // 0b 1111 1111 0000 0000
    value >>= 8; // 0b 0000 0000 0000 0000
    swapped = swapped | (mask & value); 
    //mask & value = 0000 0000 0000 0000
    // hence, swapped = 1111 1111 0000 0000

    return swapped;

}

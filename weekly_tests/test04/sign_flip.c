#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {
    
    // change sign of float
    uint32_t sign = 0;
    sign = f & 0x80000000;
    
    if (sign == 0) {
        sign = 0x80000000;
    } else {
        sign = 0;
    }

    // find f without sign
    f &= 0x7fffffff;

    //join sign and new f into flipper float
    uint32_t flipped = 0;
    flipped = f | sign;

    return flipped;
}

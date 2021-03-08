#include "float_exp.h"

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f) {
    
    //extract exponent (similar to float_bits in lab03)
    uint32_t exponent = 0;
    exponent = (f >> 23) & 0xff;

    return exponent;
}

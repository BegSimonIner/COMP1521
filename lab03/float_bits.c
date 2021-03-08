// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    // PUT YOUR CODE HERE
    // components of struct in float.h
    float_components_t fc;
    fc.sign = (f >> 31) & 0x1;
    fc.exponent = (f >> 23) & 0xff;
    fc.fraction = f & 0x7fffff;
    
    return fc;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    // PUT YOUR CODE HERE
    
    //NaN means:
    //sign = either 0 or 1.
    //biased exponent = all 1 bits.
    //fraction = anything except all 0 bits (since all 0 bits represents infinity).

    if ((f.exponent == 0xff) && f.fraction != 0) {
        return 1;
    } else {
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    // PUT YOUR CODE HERE

    //positive infinity means:
    //sign = 0 for positive infinity
    //biased exponent = all 1 bits.
    //fraction = all 0 bits.
    
    if (f.sign == 0 && f.exponent == 0xff && f.fraction == 0) {
        return 1;
    } else {
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    // PUT YOUR CODE HERE

    //negative infinity means:
    //sign = 1 for negative infinity
    //biased exponent = all 1 bits.
    //fraction = all 0 bits.
    
    if (f.sign == 1 && f.exponent == 0xff && f.fraction == 0) {
        return 1;
    } else {
        return 0;
    }
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    // PUT YOUR CODE HERE

    // if the float is zero, then:
    //sign = 0 for positive zero, 1 for negative zero.
    //biased exponent = 0.
    //fraction = 0.

    if (f.exponent == 0 && f.fraction == 0) {
        return 1;
    } else {
        return 0;
    }
    
}

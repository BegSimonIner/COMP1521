// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

uint32_t componenents_to_float (float_components_t f);
float_components_t float_bits(uint32_t f);
int is_nan(float_components_t f);
int is_positive_infinity(float_components_t f);
int is_negative_infinity(float_components_t f);
int is_zero(float_components_t f);

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -int, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    // PUT YOUR CODE HERE

    // note 2048 = 2^11
    // float = sign * (1 + frac) * 2^(exp - 127) * 2^(11)
    //simplifies to: sign * (1 + frac) * 2^(exp - 127 + 11)
    //so we are only modifying the exponent

    float_components_t fc = float_bits(f);

    if (is_nan(fc) == 1
        || is_negative_infinity(fc) == 1
        || is_positive_infinity(fc) == 1
        || is_zero(fc) == 1) {
            return f;
    } else {
        fc.exponent += 11;

        //check if number too large
        if (fc.exponent >= 0xff) {
            //note you can't return '-/inf'
            // so change components
            fc.fraction = 0;
            fc.exponent = 0xff;
        }

        return componenents_to_float (fc);
    }

    
}

// join componenents of float back into a new float
// including new exponent

uint32_t componenents_to_float (float_components_t f) {

    uint32_t new_float = 0;

    //shift sign to beginning i.e. move 31 left
    // shift exponenet to next 8 bits (after sign !!)
    // keep fraction where it is.
    new_float = f.sign << 31 | new_float;
    new_float = f.exponent << 23 | new_float;
    new_float = f.fraction << 0 | new_float;

    return new_float;

}

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

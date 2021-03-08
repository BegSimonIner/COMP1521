// Compare 2 floats using bit operations only

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

float_components_t float_to_components(uint32_t f);
uint32_t float_from_components(float_components_t f);

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {
    // PUT YOUR CODE HERE

    // SAMPLE SOLUTIONS

    float_components_t f1 = float_to_components(bits1);
    float_components_t f2 = float_to_components(bits2);

    if (is_nan(f1) || is_nan(f2)) {
        return 0;
    }

    if (is_negative_infinity(f1)) {
        // f1 is -inf, return 1 if f2 is not -inf
        return !is_negative_infinity(f2);
    }

    if (is_positive_infinity(f1) || is_negative_infinity(f2)) {
        return 0;
    }

    if (is_positive_infinity(f2)) {
        return 1;
    }

    if (is_zero(f1) && is_zero(f2)) {
        // special needed to handle +0, -0
        return 0;
    }

    if (f1.sign != f2.sign) {
        // f1, f2 have different signs, return 1 if f1 negative
        return f1.sign;
    }

    if (f1.exponent != f2.exponent) {
        // f1, f2 have different exponents
        if (f1.sign) {
            return f2.exponent < f1.exponent;
        } else {
            return f1.exponent < f2.exponent;
        }
    }

    // exponent and sign are identical
    if (f1.sign) {
        return f2.fraction < f1.fraction;
    } else {
        return f1.fraction < f2.fraction;
    }
}

#define SIGN_SHIFT       31
#define SIGN_MASK        0x1
#define EXPONENT_SHIFT   23
#define EXPONENT_MASK    0xFF
#define FRACTION_SHIFT   0
#define FRACTION_MASK    0x7FFFFF

#define EXPONENT_INF_NAN 0xFF

// separate out the 3 components of a float
float_components_t float_to_components(uint32_t f) {
    float_components_t c;
    c.exponent = (f >> EXPONENT_SHIFT) & EXPONENT_MASK;
    c.fraction = (f >> FRACTION_SHIFT) & FRACTION_MASK;
    c.sign = (f >> SIGN_SHIFT) & SIGN_MASK;
    return c;
}


// build a float from its 3 components
uint32_t float_from_components(float_components_t f) {
    return (f.sign << SIGN_SHIFT)
         | (f.exponent << EXPONENT_SHIFT) |
           (f.fraction << FRACTION_SHIFT);
}

int is_nan(float_components_t f) {
    return f.exponent == EXPONENT_INF_NAN && f.fraction != 0;
}

int is_positive_infinity(float_components_t f) {
    return f.exponent == EXPONENT_INF_NAN && f.fraction == 0 && f.sign == 0;
}

int is_negative_infinity(float_components_t f) {
    return f.exponent == EXPONENT_INF_NAN && f.fraction == 0 && f.sign == 1;
}

int is_zero(float_components_t f) {
    return f.exponent == 0 && f.fraction == 0;
}

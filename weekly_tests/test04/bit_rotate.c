#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    
    uint16_t mask_left = bits & 0x8000;
    uint16_t mask_right = bits & 0x0001;
    int i = 0;
    if (n_rotations > 0) {
        while (i < n_rotations) {
            mask_left = bits & 0x8000;
            mask_left >>= 15;
            bits <<= 1;
            bits = bits | mask_left;
            i++;
        }
    } else {
        while (n_rotations < i) {
            mask_right = bits & 0x0001;
            mask_right <<= 15;
            bits >>= 1;
            bits |= mask_right;
            n_rotations++;
        }
    }

    return bits;

    }

// SAMPLE SOLUTION:

/*
#include "bit_rotate.h"

uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    uint32_t bits32 = bits;
    n_rotations = n_rotations % 16;
    if (n_rotations < 0) {
        n_rotations += 16;
    }
    bits32 <<= n_rotations;
    return (bits32 & 0xffff) | (bits32 >> 16);
}
*/

    /*
    if (bits == 0xffff) {
        return 0xffff;
    }
    if (bits == 0x0000) {
        return 0x0000;
    }

    uint16_t rotated = 0;
    uint16_t mask = 32768; // 1000 0000 0000 0000

    //first check for negative 
    if (n_rotations < 0) {
        uint16_t mask_flip = 1;
        uint16_t flipped = 0;
        for (int j = 0; j < 15; j++) {
            flipped |= mask_flip & bits;
            flipped <<= 1;
            bits >>=1;
        }
        bits = flipped;
        n_rotations = n_rotations * (-1);
        n_rotations = n_rotations -1;
    }
    while (n_rotations > 15) {
            n_rotations = n_rotations - 16;
    }
    for (int i = 0; i <= n_rotations; i++) {

        
        rotated |= (mask & bits);
        mask >>= 1;
    }

    rotated >>= n_rotations;
    bits <<= n_rotations;
    rotated |= bits;

   
    return rotated;
    */

    /*
    uint16_t rotated = 0;
    

    //first check for negative 
    if (n_rotations < 0) {
        n_rotations = n_rotations * (-1);
        uint16_t mask_right = 0; // 0000 0000 0000 0001
        for (int i = 0; i <= n_rotations; i++) {

            while (n_rotations > 15) {
                n_rotations = n_rotations - 16;
            }
            rotated |= (mask_right & bits);
            rotated <<= 1;
            bits >>= 1;
        }
        printf("%x\n", rotated);

        rotated <<= (10);
        rotated |= bits;

    } else {
        uint16_t mask_left = 32768; // 1000 0000 0000 0000

        for (int i = 0; i <= n_rotations; i++) {

            while (n_rotations > 15) {
                n_rotations = n_rotations - 16;
            }
            rotated |= (mask_left & bits);
            mask_left >>= 1;
        }

        rotated >>= n_rotations;
        bits <<= n_rotations;
        rotated |= bits;

    }
    

    return rotated;

    */



// Written by Rifa Jamal COMP1521 20T2

// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {

    // addi has an opcode of 001000
    // 001000ssssstttttIIIIIIIIIIIIIIII
    
    uint32_t result = 0x00000000;
    uint32_t opcode = 0x20000000;
    
    if (i >= 0) {
        result |= i;
        t <<= 16;
        result |= t;
        s <<= 21;
        result |= s;
        result |= opcode;
    } else {
        i &= 0x0000ffff;
        result |= i;
        t <<= 16;
        result |= t;
        s <<= 21;
        result |= s;
        result |= opcode;
    }

    return result;

}


// SAMPLE SOLUTION:
/*

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    return          0x20000000 |
           ((uint32_t)s) << 21 |
           ((uint32_t)t) << 16 |
           (i & 0xFFFF);
}

*/
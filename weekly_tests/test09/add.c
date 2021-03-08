//Weekly Test09
//COMP1521 - Rifa Jamal z5311190
//Written on 6/08/2020

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

// return the MIPS opcode for add $d, $s, $t
uint32_t add(uint32_t d, uint32_t s, uint32_t t) {

    uint32_t funct = 1;
    uint32_t opcode = (s << 21)|(t << 16)|(d << 11)|(funct << 5);
    return opcode;

}

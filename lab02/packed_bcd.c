#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);
int change_to_4_bits(int packed_bcd_value, uint32_t mask);
int convert_to_decimal(int digit);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {

    uint32_t decimal = 0;

    int i = 1;

    for (int j = 0; j < 32; j += 4) {
        decimal = decimal + (i * ((packed_bcd_value >> j) & 0x0000F));
        i = i * 10;
    }

    return decimal;

}

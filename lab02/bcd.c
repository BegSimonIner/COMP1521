#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {

//////////////// MEHTOD 1 /////////////////////////////////

    /* 

    uint16_t mask = 32768; // 0b 1000 0000 0000 0000
    // split of 16 bits into 2 bytes - for 2 decimal digits
    int result_one[8];
    int result_two[8];

    //digit 1
    for (int i = 0; i < 8; i++) {
        if ((mask & bcd_value) == 0) {
            result_one[i] = 0;
        } else {
            result_one[i] = 1;
        }
        mask >>= 1;
    }

    //digit 2
    for (int j = 0; j < 8; j++) {
        if ((mask & bcd_value) == 0) {
            result_two[j] = 0;
        } else {
            result_two[j] = 1;
        }
        mask >>= 1;
    }

    //convert two digit arrays back into decimal

    uint8_t digit_one = 0;
    uint8_t mask_one = 1; 

    for (int pos_one = 7; mask_one; pos_one--) {
        if (result_one[pos_one] == 1) {
            // | inclusive OR
            digit_one |= mask_one;
        }
        mask_one <<= 1;
    }

    uint8_t digit_two = 0;
    uint8_t mask_two = 1; 

    for (int pos_two = 7; mask_two; pos_two--) {
        if (result_two[pos_two] == 1) {
            // | inclusive OR
            digit_two |= mask_two;
        }
        mask_two <<= 1;
    }

    //return digits

    int decimal = digit_two + (10 * digit_one) ;

    //decimal[0] = digit_one;
    //decimal[1] = digit_two;

    return decimal;


    */

    ////////////// MEHTOD 2 //////////////////////////

    uint16_t decimal = 0;

    int i = 1;

    for (int j = 0; j < 16; j += 8) {
        decimal = decimal + (i * (bcd_value >> j) & 0x00FF);
        i = i * 10;
    }

    return decimal;

    /*

    // first convert integer to binary

    uint16_t mask = 1;
    int buffer[16];

    for (int i = 15; mask; i--) {
        if((bcd_value & mask) == 0) {
            buffer[i] = 0;
        } else {
            buffer[i] = 1;
        }
        mask <<= 1;
    }

    // split the 16 bits into 2 * 8 bits
    // copy into two different strings

    int byte_one[8];
    int byte_two[8];

    for (int j = 0; j < 8; j++) {
        byte_one[j] = buffer[j];
    }

    for (int j = 8; j < 16; j++) {
        for (int k = 0; k < 8; k++){
            byte_two[k] = buffer[j];
        }
    }

    // now convert these two bytes into decimal

    uint16_t result_one = 0;
    uint16_t mask_one = 1; 

    for (int pos_one = 7; mask_one; pos_one--) {
        if (byte_one[pos_one] == 1) {
            // | inclusive OR
            result_one |= mask_one;
        }
        mask_one <<= 1;
    }

    uint16_t result_two = 0;
    uint16_t mask_two = 1; 

    for (int pos_two = 7; mask_two; pos_two--) {
        if (byte_two[pos_two] == 1) {
            // | inclusive OR
            result_two |= mask_two;
        }
        mask_two <<= 1;
    }

    return result_one + result_two;

    */

}





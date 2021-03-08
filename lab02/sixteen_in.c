//
// Sample solution for COMP1521 lab exercises
//
// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//

// My explantion on how this works:

//say char[bits] = 0110
//pos = 0, bits[0] = 1, ascii = '0' - '0' = 0
//value = 0000 << 1 = 0000, value = 0000 | 0 = 0000

//pos = 1, bits[1] = 1, ascii = '1' - '0' = 1
//value = 0000 << 1 = 0000, value = 0000 | 0001 = 0001

//pos = 2, bits[2] = 1, ascii = 1
//value = 0001 << 1 = 0010, value = 0010 | 1 = 0010 | 0001 = 0011

//pos = 3, bits[3] = 0, ascii = 0
//value = 0011 << 1 = 0110, value = 0110 | 0000 = 0110

//Hence, we arrived at original char and computer will convert to decimal

int16_t sixteen_in(char *bits) {

////////////////// METHOD ONE //////////////////////////////////////////


    //note: value starts off as 16 0's
    uint16_t value = 0;
    
    //loop through each bit individually
    //copy each character from the string onto individual bits of 'value'
    //note: at the end computer will manually change bits into decimal.
    for (int position = 0; position < N_BITS; position++) {
        int ascii_binary_digit = bits[position];
        //note: we are changing ascii value of digit to its corresponding value
        //e.g. 1 in ascii is 49, so '1' - '0' = 49 - 48 = 1
        int binary_digit = ascii_binary_digit - '0';
        
        //move to the next digit to next number can be copied in
        //e.g. if value = 0001, value then becomes 0010
        value = value << 1;

        //OR operator results in 1 unless both bits are 0, 
        //so whenever there is a 1, value will also be 1
        //e.g. if value is 0010 and binary digit is 1 (0001)
        //then 0010 | 0001 = 0011
        value = value | binary_digit;

    }
    return value;


////////////////// METHOD TWO //////////////////////////////////////

/*

uint16_t result = 0;

//use mask to look/extract single bit at a time from bits
uint16_t mask = 1; 

// mask:   0b 0000 0000 0000 0001
// bits:   0b 0000 0101 0110 0111 (example of bits)
//                                |
// result: 0b 0000 0101 0110 0111

//this tells use where the '1' is
//we can move the 1 in mask left one position, we can look at each position in bits individually
//move mask with <<

//same as saying while (mask != 0) i.e. when you move << all the way you get 0
//check for each character in string of digits
// i -- since checking bits from right to left (as mask moves)
for (int i = 15; mask; i--) {
    if (bits[i] == '1') {
        // | inclusive OR
        result |= mask;
    }
    mask <<= 1;
}

return result;

*/

}


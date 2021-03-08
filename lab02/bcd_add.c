#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

//
// Store an arbitray length Binary Coded Decimal number.
// bcd points to an array of size n_bcd
// Each array element contains 1 decimal digit.
// Digits are stored in reverse order.
//
// For example if 42 is stored then
// n_bcd == 2
// bcd[0] == 0x02
// bcd[1] == 0x04
//

typedef struct big_bcd {
    unsigned char *bcd;
    int n_bcd;
} big_bcd_t;


big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y);
void bcd_print(big_bcd_t *number);
void bcd_free(big_bcd_t *number);
big_bcd_t *bcd_from_string(char *string);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <number>\n", argv[0]);
        exit(1);
    }

    big_bcd_t *left = bcd_from_string(argv[1]);
    big_bcd_t *right = bcd_from_string(argv[2]);

    big_bcd_t *result = bcd_add(left, right);

    bcd_print(result);
    printf("\n");

    bcd_free(left);
    bcd_free(right);
    bcd_free(result);

    return 0;
}


// DO NOT CHANGE THE CODE ABOVE HERE



big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y) {

    // PUT YOUR CODE HERE

    // SAMPLE SOLUTION

    big_bcd_t *sum = malloc(sizeof *sum);
    assert(sum);

    int n_digits = 0;
    if (x->n_bcd > y->n_bcd) {
        n_digits = x->n_bcd;
    } else {
        n_digits = y->n_bcd;
    }

    sum->n_bcd = n_digits;
    sum->bcd = malloc(n_digits * sizeof sum->bcd[0]);
    assert(sum->bcd);

    int carry = 0;
    for (size_t i = 0; i < n_digits; i++) {
        int digit_sum = carry;

        if (i < x->n_bcd) {
            digit_sum += x->bcd[i];
        }

        if (i < y->n_bcd) {
            digit_sum += y->bcd[i];
        }

        sum->bcd[i] = digit_sum % 10;
        carry = digit_sum / 10;
    }

    if (carry) {
        // we need to grow the array by to fit the carry digit
        sum->n_bcd = n_digits + 1;
        sum->bcd = realloc(sum->bcd, (n_digits + 1) * sizeof sum->bcd[0]);
        assert(sum->bcd);
        sum->bcd[n_digits] = carry;
    }

    return sum;
}
}


// DO NOT CHANGE THE CODE BELOW HERE


// print a big_bcd_t number
void bcd_print(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    assert(number->n_bcd > 0);
    for (int i = number->n_bcd - 1; i >= 0; i--) {
        putchar(number->bcd[i] + '0');
    }
}

// free storage for big_bcd_t number
void bcd_free(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    // or it is calling free for the numbers it is given
    free(number->bcd);
    free(number);
}

// convert a string to a big_bcd_t number
big_bcd_t *bcd_from_string(char *string) {
    big_bcd_t *number = malloc(sizeof *number);
    assert(number);

    int n_digits = strlen(string);
    assert(n_digits);
    number->n_bcd = n_digits;

    number->bcd = malloc(n_digits * sizeof number->bcd[0]);
    assert(number->bcd);

    for (int i = 0; i < n_digits; i++) {
        int digit = string[n_digits - i - 1];
        assert(isdigit(digit));
        number->bcd[i] = digit - '0';
    }

    return number;
}

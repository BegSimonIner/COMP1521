// read a number n and print the integers 1..n one per line

#include <stdio.h>

int main(void) {
    int number, i;

    printf("Enter number: ");
    scanf("%d", &number);

    i = 1;
    while (i <= number) {
        printf("%d\n", i);
        i = i + 1;
    }

    // note this is equivalent to:
    /*
    
    start: 
        if (i > number) goto end;
        printf("%d\n", i)
        i++:
        goto start;
    end:;

    */

    return 0;
}

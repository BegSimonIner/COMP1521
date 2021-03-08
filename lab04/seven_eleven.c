// Read a number and print positive multiples of 7 or 11 < n

#include <stdio.h>


int main(void) {
    int number, i;

    printf("Enter number: ");
    scanf("%d", &number);

    i = 1;
    while (i < number) {
        if (i % 7 == 0 || i % 11 == 0) {
            printf("%d\n", i);
        }
        i = i + 1;
    }

    return 0;
}


/*
int main(void) {

    int number;
    printf("Enter number: ");
    scanf("%d", &number);

    //counter to count up from 1 to number
    int i = 1;

    int counter_7 = 1;
    int j_7 = 1;

    int counter_11 = 1;
    int j_11 = 1;

    while (i < number) {

        //check 7
        if ((i - (7*j_7)) == 0) {
            printf("%d\n", i);
        }
        counter_7++;
        if(counter_7 == 7) {
            counter_7 = 0;
            j_7++;
        }

        //check 11
        if ((i - (11*j_11)) == 0) {
            printf("%d\n", i);
        }
        counter_11++;
        if(counter_11 == 11) {
            counter_11 = 0;
            j_11++;
        }

        i++;

    }

    return 0;
}
*/




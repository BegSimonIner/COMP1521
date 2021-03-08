//Weekly Test09
//COMP1521 - Rifa Jamal z5311190
//Written on 6/08/2020

#include <stdio.h>

#include "put_string.h"

// print s to stdout with a new line appended using fputc (only)

void put_string(char *s) {

   while (*s != '\0') {
        fputc(*s, stdout);
        s++;
   }
   
   fputc('\n', stdout);

}

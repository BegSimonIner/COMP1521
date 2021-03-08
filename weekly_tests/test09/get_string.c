//Weekly Test09
//COMP1521 - Rifa Jamal z5311190
//Written on 6/08/2020

#include <stdio.h>

#include "get_string.h"

// print a line from stream using fgetc (only)
// reads  in at  most one less than size characters from stream and stores them into the
// buffer pointed to by s.  Reading stops after an EOF or a newline.  If a newline is read, it  is
// stored  into  the buffer.  A terminating null byte ('\0') is stored after the last character in the buffer.
void get_string(char *s, int size, FILE *stream) {


// SAMPLE SOLUTION - MUCH BETTER:
// HAVENT COMMENTED FUNCTION OUTTTTTT

void get_string(char *s, int size, FILE *stream) {

    int bytes_read = 0;
    int c;
    while (bytes_read < size - 1 && (c = fgetc(stream)) != EOF) {
        s[bytes_read] = c;
        bytes_read++;
        if (c == '\n') {
            break;
        }
    }
    s[bytes_read] = '\0';

}

    /*
    int i;
    //ch = fgetc(stream);
    i = 0;
    // Read in size - 1 characters and place them in "s":
    while (fgetc(stdin) != EOF) {
        while (i < (size - 1)){ 
            //ch = fgetc(stream);
            //s[i] = (char)ch;
            s[i] = *s;
            //s++;
            i++;
        }
    }
    // Add null to end string
        s[i] = '\0';
    
    //printf( "%s\n", s);
   */
    int i = 0;
    int ch;
    while((ch = fgetc(stdin)) != '\n' && (i < (size -1))) {
        if(ch == EOF) {
            break;
        }
            s[i] = ch;
            i++;  
        
    }
    if (i == size - 1) {
        
        s[size - 1] = '\0';

    } else {

        if (ch == '\n') {
            s[i] = '\n';
        }

        // the strings should be end with '\0'
        s[i+1] = '\0';
    }
    
  
} 



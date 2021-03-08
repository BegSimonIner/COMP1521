// Weekly Test 10 COMP1521
// Written by Rifa Jamal z5311190
// On 13/08/2020

// is_diary_public.c, which prints 1 if a file named 
// $HOME/.diary exists and is publically readable.
// It should print 0 otherwise.
// $HOME means the value of the environment variable HOME.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    char *home = getenv("HOME");

    int size = snprintf(NULL, 0, "%s/.diary", home);
    char *path = calloc(size + 1, sizeof(char));
    snprintf(path, size + 1, "%s/.diary", home);

    struct stat s;
    
    /*if (stat(path, &s) < 0) {
        perror(path);
        return 1;
    }*/

    if((stat(path, &s) == 0) && (s.st_mode & S_IROTH)){
        printf("1\n");
        
    } else {
        printf("0\n");    
    }

    return 0;

}
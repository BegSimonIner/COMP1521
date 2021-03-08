// Weekly Test 10 COMP1521
// Written by Rifa Jamal z5311190
// On 13/08/2020

// is_directory.c, which takes one argument a pathname.
// If the pathname exists and is a directory, 
// it should print 1, otherwise it should print 0.

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    
    assert(argc == 2);
    char *path = argv[1];

    struct stat s;
    if (stat(path, &s) == 0) {
        if( s.st_mode & S_IFDIR ) {
            //it's a directory
            printf("1\n");
        }
        /*else if( s.st_mode & S_IFREG ) {
            //it's a file
            printf("0\n");
        }*/
        else {
            //something else
            printf("0\n");
        }
    }
    else {
        //error
        printf("0\n");
    }

    return 0;
}
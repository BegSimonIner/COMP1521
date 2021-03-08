// Weekly Test 10 COMP1521
// Written by Rifa Jamal z5311190
// On 13/08/2020

// is_var_set.c, which takes one argument, the name of environment variable
// If the environment variable is set to a non-empty string, 
// it should print 1, otherwise it should print 0.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[]) {

    assert(argc == 2);
    char *stream = argv[1];
    char *env_var = getenv(stream);
    if (env_var != NULL && env_var[0] != '\0') {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;

}

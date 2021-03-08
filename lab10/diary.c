// Lab 10 COMP1521
// Written by Rifa Jamal (z5311190)
// on 8/08/2020

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

    FILE *infile = fopen(path, "a");
    if (!infile) {
        perror(path);
        exit(1);
    }

    int i = 1;
    while (i < argc){
        fprintf(infile, "%s ", argv[i]);
        i++;
    }
    fprintf(infile, "%s", "\n");
    return 0;
}
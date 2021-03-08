// Lab 09 Written by Rifa Jamal COMP1521
// 20T2

// file_modes.c, which is given one or more pathnames 
// as command line arguments. It should print 
// one line for each pathnames which 
// gives the permissions of the file or directory.

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void stat_file(char *pathname);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        stat_file(argv[arg]);
    }
    return 0;
}

void stat_file(char *pathname) {
    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    printf( (S_ISDIR(s.st_mode)) ? "d" : "-");
    printf( (s.st_mode & S_IRUSR) ? "r" : "-");
    printf( (s.st_mode & S_IWUSR) ? "w" : "-");
    printf( (s.st_mode & S_IXUSR) ? "x" : "-");
    printf( (s.st_mode & S_IRGRP) ? "r" : "-");
    printf( (s.st_mode & S_IWGRP) ? "w" : "-");
    printf( (s.st_mode & S_IXGRP) ? "x" : "-");
    printf( (s.st_mode & S_IROTH) ? "r" : "-");
    printf( (s.st_mode & S_IWOTH) ? "w" : "-");
    printf( (s.st_mode & S_IXOTH) ? "x" : "-");
    printf(" %s", pathname);
    printf("\n");
    
}


// SAMPLE SOLUTIONS:

/*

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void file_mode(char *pathname);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        file_mode(argv[arg]);
    }
    return 0;
}

// convert octal mode to -rwxrwxrwx string and print itm

void file_mode(char *pathname) {
    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    mode_t mode = s.st_mode;

    char permissions[] = "?rwxrwxrwx";
    int n_permissions = strlen(permissions);

    if (S_ISREG(mode)) {
        permissions[0] = '-';
    } else if (S_ISDIR(mode)) {
        permissions[0] = 'd';
    }

    for (int i = 1; i < n_permissions; i++) {
        if (!(mode & (1 << (i - 1)))) {
            permissions[n_permissions - i] = '-';
        }
    }

    printf("%s %s\n", permissions, pathname);
}

*/
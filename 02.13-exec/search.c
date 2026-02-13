#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int fsearch(char *, char *);

int main(int argc, char *argv[]) {
    int i, tmp, status = EXIT_FAILURE;
    pid_t pid;

    for (i = 2; i < argc; i++) {
        if ((pid = fork()) == 0) {
            exit(fsearch(argv[1], argv[i]));
        }
    }

    for (i = 2; i < argc; i++) {
        pid = wait(&tmp);
        if (WIFEXITED(tmp) && WEXITSTATUS(tmp) == EXIT_SUCCESS) {
            status = EXIT_SUCCESS;
        }
    }

    return status;
}

/* fsearch: Prints occurrences of a string in a file. */
int fsearch(char *str, char *fname) {
    int status = EXIT_FAILURE;
    char buf[LINELEN];
    FILE *file = fopen(fname, "r");

    while (fgets(buf, LINELEN, file) != NULL) {
        if (strstr(buf, str) != NULL) {
            printf("%s: %s", fname, buf);
            status = EXIT_SUCCESS;
        }
    }

    fclose(file);
    return status;
}

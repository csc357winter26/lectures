#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int fsearch(char *, char *);

int main(int argc, char *argv[]) {
    int status = 0, i;
    pid_t pid;

    for (i = 2; i < argc; i++) {
        if ((pid = fork()) == 0) {
            printf("%d is the child of %d.\n", getpid(), getppid());
            exit(fsearch(argv[1], argv[i]));
        }
        else {
            printf("%d is the parent of %d.\n", getpid(), pid);
        }
    }

    /* NOTE: It is the parent's responsibility to wait for each and every one
     *       of its children. In this case, however, we can't wait for a child
     *       until after all children have been forked; we need the children to
     *       execute simultaneously. */

    for (i = 2; i < argc; i++) {
        pid = wait(&status);

        if (WIFEXITED(status)) {
            printf("%d exited with status %d.\n", pid, WEXITSTATUS(status));
        }
        else {
            printf("%d exited abnormally.\n", pid);
        }
    }

    return EXIT_SUCCESS;
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

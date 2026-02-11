#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int fsearch(char *, char *);

int main(int argc, char *argv[]) {
    int i, status = 0;
    pid_t pid;

    /* NOTE: Calling "fork" duplicates the now-parent process, which means the
     *       newly created child process has access to all of the parent's
     *       existing data. The parent can then create multiple children to
     *       execute multiple tasks in parallel. */

    for (i = 2; i < argc; i++) {
        if ((pid = fork()) == 0) {
            printf("%d is the child of %d.\n", getpid(), getppid());
            exit(fsearch(argv[1], argv[i]));
        }
    }

    /* NOTE: The parent is responsible for eventually waiting for each of its
     *       children. In this case, however, we don't want to wait for each
     *       child immediately; we need to create all of our children first so
     *       that they execute simultaneously, then wait for them later. */

    for (i = 2; i < argc; i++) {
        printf("%d is the parent of %d.\n", getpid(), pid);
        pid = wait(&status);

        if (WIFEXITED(status)) {
            printf("%d exited normally with status %d.\n",
             pid, WEXITSTATUS(status));
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

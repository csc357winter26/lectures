#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int main(int argc, char *argv[]) {
    int i, tmp, status = EXIT_FAILURE;
    pid_t pid;

    for (i = 2; i < argc; i++) {
        if ((pid = fork()) == 0) {
            /* NOTE: There already exists a program that searches files. We
             *       don't need to rewrite that code -- we certainly don't want
             *       to have to write both parent and child code in the same
             *       program -- we can just replace the child with "grep".
             * exit(fsearch(argv[1], argv[i])); */

            /* NOTE: In this case, we need "execLP"; we are going to pass a
             *       List of arguments, and we need the OS to search the Path
             *       for the "grep" executable. By convention, the first
             *       argument is always the name of the executable. */
            execlp("grep", "grep", argv[1], argv[i], NULL);

            /* NOTE: A successful call to "exec" never returns; any code below
             *       effectively ceases to exist. The only way to get here is
             *       if "exec" failed. This also means we need to replace the
             *       child; the parent needs to go on to wait. */
            perror("execlp");
            exit(EXIT_FAILURE);
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

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
            /* NOTE: There already exists a program, "grep", for searching
             *       files; there is no reason to rewrite that code -- there is
             *       certainly no reason to write that code in the same program
             *       as the parent process that will never need it.
             * exit(fsearch(argv[1], argv[i])); */

            /* NOTE: In this case, we need "execLP"; we are going to pass a
             *       List of arguments, and we need the OS to search the Path
             *       for the "grep" executable. By convention, the first
             *       argument is always the name of the executable. */
            execlp("grep", "grep", argv[1], argv[i], NULL);

            /* NOTE: Once we call "exec", there is no coming back, since the
             *       current executable will have been replaced. The only way
             *       to get this far is if the call failed. This also means we
             *       can't replace the parent; it has other responsibilities. */
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

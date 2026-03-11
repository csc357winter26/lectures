#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fds[2];
    pid_t pid;

    pipe(fds);

    if ((pid = fork()) == 0) {
        char buf[5];
        int n;

        close(fds[1]);

        /* NOTE: Pipes are essentially queues. UNIX likes to pretend that all
         *       I/O is file I/O, and pipes are no exception. To dequeue from a\
         *       pipe, we use the existing "read" system call. */
        printf("%d is the child of %d.\n", getpid(), getppid());
        while ((n = read(fds[0], buf, 4)) > 0) {
            buf[n] = '\0';
            printf("%d read \"%s\" from the pipe.\n", getpid(), buf);
        }

        close(fds[0]);
    }
    else {
        /* NOTE: "fds[0]" is the read end of the pipe and "fds[1]" is the write
         *       end; in the parent, we don't intend to ever read from the
         *       pipe, so we should close the read end... */
        close(fds[0]);

        printf("%d is the parent of %d.\n", getpid(), pid);
        write(fds[1], "Hello, child!", 13);

        /* NOTE: ...in the case of pipes, closing unneeded file descriptors is
         *       not just a matter of cleanliness or best practice, it's also
         *       how we communicate to other processes that we're done. */
        close(fds[1]);

        wait(NULL);
    }

    return EXIT_SUCCESS;
}

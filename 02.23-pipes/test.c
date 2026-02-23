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

        /* NOTE: A pipe is essentially a queue accessible by multiple processes.
         *       UNIX likes to pretend that all I/O is file I/O; to dequeue, we
         *       use the existing "read" system call. */
        printf("%d is the child of %d.\n", getpid(), getppid());
        while ((n = read(fds[0], buf, 4)) > 0){
            buf[n] = '\0';
            printf("%d read \"%s\" from the pipe.\n", getpid(), buf);
        }

        close(fds[0]);
    }
    else {
        close(fds[0]);

        printf("%d is the parent of %d.\n", getpid(), pid);
        write(fds[1], "Hello, child!", 13);

        /* NOTE: With pipes, closing unused file descriptors is not just a
         *       matter of cleanliness or best practice; it's how we notify
         *       other processes that no more data is coming. */
        close(fds[1]);

        wait(NULL);
    }

    return EXIT_SUCCESS;
}

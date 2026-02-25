#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    pid_t pid;
    int ptoc[2], ctop[2];

    /* NOTE: In theory, we could do this with a single pipe to which both
     *       parent and child had read/write access, as long as we were very
     *       careful about who accessed that pipe and when. In pratice, it's
     *       easier to just make two pipes: one for each direction. */

    pipe(ptoc);
    pipe(ctop);
    
    if ((pid = fork()) == 0) {
        printf("%d is the child of %d.\n", getpid(), getppid());

        /* NOTE: By replacing stdin/stdout with the ends of the pipes, whenever
         *       the child reads from stdin, it'll actually be reading from the
         *       "ptoc" pipe; whenever it writes to stdout, it'll actually be
         *       writitng to the "ctop" pipe. */

        dup2(ptoc[0], STDIN_FILENO);
        dup2(ctop[1], STDOUT_FILENO);

        /* NOTE: With the appropriate stdin/stdout descriptors replaced, we no
         *       longer need any of the original pipe ends, so we should close
         *       all of them. Note that stdin/stdout are closed automatically
         *       on termination, so we can just set them and forget them. */

        close(ptoc[0]);
        close(ptoc[1]);
        close(ctop[0]);
        close(ctop[1]);

        execlp("./hello", "./hello", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    else {
        char buf[80];
        int n;

        printf("%d is the parent of %d.\n", getpid(), pid);

        close(ptoc[0]);
        close(ctop[1]);

        /* NOTE: Both processes expect to read and write, but they can't both
         *       read first, otherwise they will be deadlocked waiting for
         *       data which only the other process can send. */

        write(ptoc[1], "parent\n", 7);
        close(ptoc[1]);

        n = read(ctop[0], buf, 80);
        buf[n - 1] = '\0';
        close(ctop[0]);

        printf("%d read \"%s\" from the child-to-parent pipe.\n", getpid(), buf);
        wait(NULL);
    }

    return EXIT_SUCCESS;
}

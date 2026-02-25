#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int ptoc[2], ctop[2];

    /* NOTE: In theory, we could have all processes use one single pipe, if we
     *       we very careful about exactly which process accessed the pipe and
     *       when. In practice, we typically just make one pipe for each
     *       direction that information needs to travel. */

    pipe(ptoc);
    pipe(ctop);

    if (fork() == 0) {

        /* NOTE: By replacing stdin/stdout with the ends of pipes, we can
         *       "trick" a process that does not know about the existence of
         *       those pipes into reading from and writing to them instead of
         *       stdin/stdout. */

        dup2(ptoc[0], STDIN_FILENO);
        dup2(ctop[1], STDOUT_FILENO);

        /* NOTE: We generally need to make sure that we close pipe ends we are
         *       not using, but in the case of stdin/stdout, those files are
         *       closed automatically on program termination, so we can safely
         *       attach them to pipes and then forget about them. */

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

        close(ptoc[0]);
        close(ctop[1]);

        /* NOTE: We now have two processes, both of which expect to read and
         *       write to one another via pipes. But they can't *both* read
         *       first, otherwise they will be deadlocked waiting for something
         *       that only the other process can provide. */

        write(ptoc[1], "parent\n", 7);
        close(ptoc[1]);
        n = read(ctop[0], buf, 80);
        close(ctop[0]);

        buf[n - 1] = '\0';
        printf("Read \"%s\" from the pipe.\n", buf);
        wait(NULL);
    }

    return EXIT_SUCCESS;
}

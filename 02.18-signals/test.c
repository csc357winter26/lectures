#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signum) {
    /* NOTE: This is technically unsafe; printf is not async-signal-safe. We'll
     *       probably get away with it since there are no other calls to printf
     *       in this program, but typically a signal handler should just do the
     *       bare minimum to respond to a signal, and maybe set some global
     *       variable that the rest of the program can check later. */
    if (signum == SIGINT) {
        printf("But SAIGE lets their processes eat clock cycles before dinner!\n");
    }
    else if (signum == SIGQUIT) {
        printf("But JOHN lets their processes stay up as long as they want!\n");
    }
}

int main(void) {
    /* NOTE: This is not always the desired behavior, but it's usually the most
     *       common options: we want to call a signal handler upon receiving a
     *       signal, and then we want to try to restart any system calls that
     *       may have been interrupted. */
    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = SA_RESTART; 

    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);

    /* NOTE: In general, we can install signal handlers to effectively block or
     *       ignore signals. However, we cannot change the default action of a
     *       SIGSTOP or a SIGKILL. */
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    /* NOTE: Installing a handler simply requests that the OS call that
     *       function *if* a signal occurs; it does not necessarily mean that
     *       the signal *will* occur or that the function *will* be called. In
     *       this case, we just need this program to wait for a signal. */
    while (1);

    return EXIT_SUCCESS;
}

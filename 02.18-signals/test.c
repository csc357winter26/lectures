#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signum) {
    /* NOTE: A signal handler is called in response to some asynchronous event.
     *       It effectively has no caller, and thus it cannot take additional
     *       arguments or produce return values. That also means that this is
     *       technically unsafe, as "printf" is not async-signal-safe. We'll
     *       probably get away with it, as there are no other calls to "printf"
     *       in this program, but typically signal handlers just do the bare
     *       minimum to respond to a signal; they might just set a global
     *       variable which can then be checked by the rest of the program */
    if (signum == SIGINT) {
        printf("But CARTER lets their processes stay up as long as they want!\n");
    }
    else if (signum == SIGQUIT) {
        printf("But STELLA lets their processes eat memory before dinner!\n");
    }
}

int main(void) {
    struct sigaction action;

    /* NOTE: These are the general common-sense options: we want to call a
     *       handler in response to a signal, and we then want to resume any
     *       system calls that may have been interrupted by that signal. */
    action.sa_handler = handler;
    action.sa_flags = SA_RESTART; 
    sigemptyset(&(action.sa_mask));
    
    /* NOTE: The arguments to "sigaction" include a structure containing new
     *       options and a structure that will be populated with existing
     *       options. If, for example, we only wanted to temporarily change the
     *       action, we could save the existing options to reset them later. */
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);

    /* NOTE: The above effectively ignores SIGINT (Ctrl+c) and SIGQUIT (Ctrl+\)
     *       but SIGSTOP (Ctrl+z) and SIGKILL cannot be blocked, ignored, or
     *       otherwise handled. */
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    /* NOTE: Installing a handler simply requests that the OS call a function
     *       *if* a signal is received; it does not guarantee that the signal
     *       will be received or that the function will be called. */
    while (1);

    return EXIT_SUCCESS;
}

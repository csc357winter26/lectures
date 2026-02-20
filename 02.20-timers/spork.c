#include <sys/resource.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

/* NOTE: A static global is accessible anywhere within this file -- since a
 *       handler has no caller, globals are one of the few ways to get data
 *       into or out of it. For simplicity, we'll assume we never create more
 *       than one child, else we'd need some dynamic data structure of pids. */
static pid_t pid;

void handler(int signum) {
    kill(pid, SIGKILL);
}

/* spork: Creates a new resource-limited process. */
pid_t spork(time_t timeout) {
    /* TODO: Write a safer wrapper around "fork": create a child process, but
     *       prevent that child from creating any children of its own, and
     *       terminate it if it takes too long to execute. */
    struct rlimit limit;
    struct sigaction action;
    struct itimerval timer;

    if ((pid = fork()) == 0) {
        /* NOTE: In the child, lower the soft and hard limits on the number of
         *       processes to 1, so that the child cannot fork any children of
         *       its own. */
        getrlimit(RLIMIT_NPROC, &limit);
        limit.rlim_cur = 1;
        limit.rlim_max = 1;
        setrlimit(RLIMIT_NPROC, &limit);
    }
    else {
        /* NOTE: Install a handler for SIGALRM; this must be done before setting
         *       the timer, otherwise there is theoretically a chance the timer
         *       could elapse before we had a chance to set the handler. */
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigemptyset(&action.sa_mask);
        sigaction(SIGALRM, &action, NULL);

        /* NOTE: Initialize a timer to go off in "timeout" seconds... */
        timer.it_value.tv_sec = timeout;
        timer.it_value.tv_usec = 0;

        /*       ...but don't repeat the timer after it elapses... */
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;

        /*       ...and set the timer. */
        setitimer(ITIMER_REAL, &timer, NULL);

        /* NOTE: If we don't have anything to do other than wait for a signal, we
         *       can call "pause" to request that the OS suspend execution until a
         *       signal arrives instead of wasting resources by busy waiting.
         * pause(); */
    }

    return pid;
}

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 1024

/* NOTE: Since threads share (among others) a global data segment, they can
 *       communicate their results by mutating the same global variables... */
static int count = 0;

/* NOTE: ...however, that creates a race condition, where, if two threads
 *       increment the same global, it may only be incremented once. */
static pthread_mutex_t lock;

typedef struct Arg {
    int *arr;
    int n;
    int x;
} Arg;

void *f(void *ptr) {
    Arg *arg = (Arg *)ptr;
    int i;

    for (i = 0; i < arg->n; i++) {
        if (arg->arr[i] == arg->x) {
            /* NOTE: The body of this "if" statement is the "critical section",
             *       the code that only one thread can be allowed to execute at
             *       once. Threads must cooperatively agree to acquire a mutex
             *       before entering the critical section... */
            pthread_mutex_lock(&lock);

            /* NOTE: ...by definition, only one thread can possess the mutex at
             *       a time. Thus, only thread can return from "pthread_mutex_
             *       lock" at a time, thus, only one thread can execute the
             *       following increment at a time. */
            count++;

            pthread_mutex_unlock(&lock);
        }
    }

    return NULL;
}


int main(void) {
    int arr[LENGTH], i;
    pthread_t tids[2];
    Arg args[2];

    for (i = 0; i < LENGTH; i++) {
        arr[i] = rand() % 10;
    }

    args[0].arr = arr;
    args[0].n = LENGTH / 2;
    args[0].x = 1;
    args[1].arr = arr + LENGTH / 2;
    args[1].n = LENGTH / 2;
    args[1].x = 1;

    pthread_mutex_init(&lock, NULL);
    pthread_create(&tids[0], NULL, f, &args[0]);
    pthread_create(&tids[1], NULL, f, &args[1]);
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    pthread_mutex_destroy(&lock);

    printf("%d\n", count);

    return EXIT_SUCCESS;
}

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Arg {
    int *arr;
    int n;
} Arg;

int intcmp(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

void *f(void *arg) {
    /* NOTE: Since the threading library cannot possibly anticipate all the
     *       functions we ever want to parallelize, this function must take a
     *       void pointer, which we can then cast accordingly inside. */
    qsort(((Arg *)arg)->arr, ((Arg *)arg)->n, sizeof(int), intcmp);

    return NULL;
}

int main(void) {
    int arr[128], i;
    pthread_t tids[2];
    Arg args[2];

    for (i = 0; i < 128; i++) {
        arr[i] = rand() % 10;
    }

    /* NOTE: This is data parallelism: we're going to perform the same task on
     *       two subsets of the overall dataset. These subsets are the same
     *       size, such that the two threads ought to take roughly the same
     *       amount of time. */
    args[0].arr = arr;
    args[0].n = 64;
    args[1].arr = arr + 64;
    args[1].n = 64;

    /* NOTE: The thread IDs must be passed to other threading functions that
     *       impact these threads, however, they are not guaranteed to be
     *       integers (or even printable). */
    pthread_create(&tids[0], NULL, f, &args[0]);
    pthread_create(&tids[1], NULL, f, &args[1]);

    /* NOTE: The function passed on creation is essentially the new thread's
     *       "main"; it is called on creation, and once it returns, the thread
     *       can be joined. */
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);

    for (i = 0; i < 127; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[127]);

    return EXIT_SUCCESS;
}

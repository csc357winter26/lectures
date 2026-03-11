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

void *f(void *ptr) {
    /* NOTE: Since the threading library cannot possibly anticipate every
     *       function we might wish to parallelize, this function must take a
     *       single void pointer, which we can then cast as appropriate. */
    Arg *arg = (Arg *)ptr;
    qsort(arg->arr, arg->n, sizeof(int), intcmp);

    return NULL;
}

int main(void) {
    int arr[128], i;
    pthread_t tids[2];
    Arg args[2];

    for (i = 0; i < 128; i++) {
        arr[i] = rand() % 10;
    }

    /* NOTE: This is data parallelism: we create two threads to perform the
     *       same operations, just on two different subsets of the overall
     *       dataset, ideally of equal size. */
    args[0].arr = arr;
    args[0].n = 64;
    args[1].arr = arr + 64;
    args[1].n = 64;

    /* NOTE: On newer versions of UNIX-like systems, pthread_t does not have to
     *       be an integer, nor even printable. If we need to print thread IDs
     *       for debugging, we have to assign separate IDs ourselves. */
    pthread_create(&tids[0], NULL, f, &args[0]);
    pthread_create(&tids[1], NULL, f, &args[1]);

    /* NOTE: The function passed to "pthread_create" is essentially the new
     *       thread's "main": once it returns, the thread terminates, and it
     *       can then be awaited with "pthread_join". */
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);

    for (i = 0; i < 127; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[127]);

    return EXIT_SUCCESS;
}

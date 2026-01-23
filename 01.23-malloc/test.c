#include <stdlib.h>
#include <stdio.h>

int *pair(int, int);

int main(void) {
    int *arr;

    arr = pair(1, 2);
    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    return 0;
}

int *pair(int first, int second) {
    /* NOTE: This is never safe. Automatically allocated locals on the runtime
     *       stack must be deallocated on return, so this will end up returning
     *       a pointer to memory that is no longer in use.
     * int arr[2]; */

    /* NOTE: Instead, dynamically allocated data on the heap can be allocated
     *       at runtime and will not be deallocated on return. Recall that
     *       we are allowed to use array syntax on pointers. */
    int *arr = (int *)malloc(sizeof(int) * 2);

    arr[0] = first;
    arr[1] = second;

    return arr;
}

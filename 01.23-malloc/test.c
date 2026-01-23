#include <stdlib.h>
#include <stdio.h>

int *pair(int, int);

int main(void) {
    int *arr;

    arr = pair(1, 2);
    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    /* NOTE: It makes no sense to free memory that isn't on the heap...
     * free(&arr); */

    /* NOTE: ...nor is it possible to free a portion of a block...
     * free(arr + 1); */

    /* NOTE: ...but without any free this would be a memory leak... */
    free(arr);

    /* NOTE: ...and it makes no sense to free something twice.
     * free(arr); */

    return 0;
}

int *pair(int first, int second) {
    /* NOTE: Automatically allocated locals on the runtime stack must be
     *       deallocated on return, so returning this array retuns a pointer
     *       to memory that is effectively garbage.
     * int arr[2]; */

    /* NOTE: Dynamically allocated date on the heap can be allocated at runtime
     *       and will not be deallocated on return. Recall that we may use
     *       array syntax on pointers. */
    int *arr = (int *)malloc(sizeof(int) * 2);

    arr[0] = first;
    arr[1] = second;

    return arr;
}

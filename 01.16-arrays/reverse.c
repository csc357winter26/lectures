#include <stdio.h>

void swap(int *, int *);
void reverse(int[], int);

int main(void) {
    int arr[] = {1, 2, 3, 4};

    reverse(arr, 4);
    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" |- %p: %d\n", (void *)&arr[1], arr[1]);
    printf(" |- %p: %d\n", (void *)&arr[2], arr[2]);
    printf(" +- %p: %d\n", (void *)&arr[3], arr[3]);

    return 0;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void reverse(int arr[], int len) {
    int i;

    for (i = 0; i < len / 2; i++) {
        /* NOTE: In C, arguments are always pass-by-value. The value of an
         *       array is the address of its first element, so the array decays
         *       into a pointer within the function. */
        swap(&arr[i], &arr[len - 1 - i]);

        /* NOTE: Indexing an array is equivalent to offsetting and dereferencing
         *       its address, so the above dereferences a pointer only to ask
         *       for that address back. Instead, it is equivalent to:
         * swap(arr + i, arr + (len - 1 - i)) */

        /* NOTE: A null pointer is guaranteed to be an invalid address for data,
         *       and dereferencing a null pointer is likely to result in a
         *       segfault when the program accesses memory outside its segment.
         * swap(NULL, NULL); */
    }
}

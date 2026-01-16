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

/* NOTE: In C, arguments are always pass-by-value. The value of an array is the
 *       address of its first element, thus, when an array is passed into a
 *       function, it "decays" into a pointer. Note the length must be passed
 *       separately if needed. */
void reverse(int arr[], int len) {
    int i;

    for (i = 0; i < len / 2; i++) {
        swap(&arr[i], &arr[len - 1 - i]);

        /* NOTE: The array and pointer syntaxes are largely interchangeable;
         *       indexing an array is offsetting and dereferencing its address,
         *       so the above is equivalent to the following: */
        swap(arr + i, arr + (len - 1 - i));
    }

    /* NOTE: A NULL pointer is guaranteed to be an invalid address for data, so
     *       this will cause a "segfault" when the swap function tries to use
     *       those invalid addresses.
     * swap(NULL, NULL); */
}

#include <stdio.h>
#include "add.h"
#include "max.h"

int reduce(int[], int, int (*)(int, int));

int main(void) {
    int arr[] = {2, -1, 9, 8, 5, -3, 0, 8};

    printf("reduce(%p, 8, %p): %d\n",
     (void *)arr, (void *)add, reduce(arr, 8, add));

    printf("reduce(%p, 8, %p): %d\n",
     (void *)arr, (void *)max, reduce(arr, 8, max));

    return 0;
}

/* NOTE: Finding the sum is very similar to finding the max element: both
 *       involve repeatedly combining two elements in some way. To avoid
 *       duplicating code, we can pass a pointer to a function that does that
 *       combining operation. */
int reduce(int arr[], int n, int (*fn)(int, int)) {
    int val = arr[0], i;

    for (i = 1; i < n; i++) {
        val = (*fn)(val, arr[i]);
    }

    return val;
}

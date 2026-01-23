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

/* NOTE: The code for finding the max is very similar to finding the sum, just
 *       with a different operation within the loop. We can reduce code
 *       duplication by having this function take as argument a pointer to
 *       another function to perform that combining operation. */
int reduce(int arr[], int n, int (*fn)(int, int)) {
    int val = arr[0], i;

    for (i = 1; i < n; i++) {
        val = (*fn)(val, arr[i]);
    }

    return val;
}

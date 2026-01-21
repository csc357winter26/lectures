#include <stdio.h>

int reduce(int[], int);

int main(void) {
    int arr[] = {2, -1, 9, 8, 5, -3, 0, 8};

    printf("reduce(arr, 8): %d\n", reduce(arr, 8));

    return 0;
}

int reduce(int arr[], int n) {
    int val = arr[0], i;

    for (i = 1; i < n; i++) {
        val = val + arr[i];
    }

    return val;
}

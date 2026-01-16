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
    (void)arr;
    (void)len;
}

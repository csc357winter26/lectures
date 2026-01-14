#include <stdio.h>

void swap(int *, int *);

int main(void) {
    int z = 1, w = 2;

    swap(&z, &w);

    printf("z (%p): %d\n", (void *)&z, z);
    printf("w (%p): %d\n", (void *)&w, w);

    return 0;
}

/* NOTE: In C, arguments are always pass-by-value, but the value of a pointer
 *       is a reference. Essentially, we may opt-in to pass-by-reference
 *       behavior anytime we want by passing a pointer instead. We can give
 *       any function access to any other function's data! */
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;

    printf("x (%p): %p\n", (void *)&x, (void *)x);
    printf("y (%p): %p\n", (void *)&y, (void *)y);
}

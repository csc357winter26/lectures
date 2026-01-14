#include <stdio.h>

void swap(int *, int *);

int main(void) {
    int z = 1, w = 2;

    swap(&z, &w);

    printf("z (%p): %d\n", (void *)&z, z);
    printf("w (%p): %d\n", (void *)&w, w);

    return 0;
}

/* NOTE: In C, everything is always pass-by-value, but the value of a pointer
 *       is a reference. Pointers essentially allow us to opt-in to pass-by-
 *       reference behavior whenever we feel like it by telling a function
 *       *where* a variable is rather than *what* a variable contains. */
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;

    printf("x (%p): %p\n", (void *)&x, (void *)x);
    printf("y (%p): %p\n", (void *)&y, (void *)y);
}

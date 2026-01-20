#include <stdio.h>

/* NOTE: The value of an array of pointers is the address of its first "inner"
 *       pointer, which decays into a double pointer. Recall that pointer and
 *       array syntaxes are largely interchangeable. */
void foo(int **mat) {
    mat[1][0] = 5; /* Interchangeable with "*(*(mat + 1) + 0) = 5". */
}

/* NOTE: In order to make the indexing math work out, the compiler must know the
 *       length of each "inner" array. However, this means that this function
 *       only works on (n x 2) arrays. */
void bar(int mat[][2]) {
    mat[1][0] = 6; /* Interchangeable with "*((int *)mat + 1 * 2 + 0) = 6". */
}

/* NOTE: The compiler sees "mat" as an ordinary integer pointer, but we the
 *       programmers happen to know that it's actually the beginning of an
 *       (n x m) array of integers, and we can do the math for the compiler. */
void bay(int *mat, int m) {
    *(mat + 1 * m + 0) = 7;
}

int main(void) {
    int r0[] = {1, 2}, r1[] = {3, 4};
    int *mat1[2];
    int mat2[][2] = {{1, 2}, {3, 4}};

    mat1[0] = r0;
    mat1[1] = r1;

    foo(mat1);

    printf("mat1: %p\n", (void *)mat1);
    printf(" |- %p: %p\n", (void *)&mat1[0], (void *)mat1[0]);
    printf(" |   |- %p: %d\n", (void *)&mat1[0][0], mat1[0][0]);
    printf(" |   +- %p: %d\n", (void *)&mat1[0][1], mat1[0][1]);
    printf(" +- %p: %p\n", (void *)&mat1[1], (void *)mat1[1]);
    printf("     |- %p: %d\n", (void *)&mat1[1][0], mat1[1][0]);
    printf("     +- %p: %d\n", (void *)&mat1[1][1], mat1[1][1]);

    bar(mat2);
    bay((int *)mat2, 2);

    printf("mat2: %p\n", (void *)mat2);
    printf(" |- %p: %p\n", (void *)&mat2[0], (void *)mat2[0]);
    printf(" |   |- %p: %d\n", (void *)&mat2[0][0], mat2[0][0]);
    printf(" |   +- %p: %d\n", (void *)&mat2[0][1], mat2[0][1]);
    printf(" +- %p: %p\n", (void *)&mat2[1], (void *)mat2[1]);
    printf("     |- %p: %d\n", (void *)&mat2[1][0], mat2[1][0]);
    printf("     +- %p: %d\n", (void *)&mat2[1][1], mat2[1][1]);

    return 0;
}

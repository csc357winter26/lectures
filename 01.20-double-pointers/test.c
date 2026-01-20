#include <stdio.h>

/* NOTE: The value of an array of pointers is the address of its first "inner"
 *       pointer, which thus decays into a double pointer. Recall that pointer
 *       and array syntax is largely interchangeable. */
void foo(int **mat) {
    mat[0][1] = 5;  /* Interchangeable with "*(*(mat + 0) + 1) = 5". */
}

/* NOTE: In order to make the indexing math work out for true multidimensional
 *       arrays, the compiler has to know exactly how long each "inner" array
 *       is going to be, which limits this function to (n x 2) arrays. */
void bar(int mat[][2]) {
    mat[0][1] = 6;  /* Interchangeable with "*(mat + (0 * 2) + 1) = 6". */
}

/* NOTE: The compiler sees "mat" as an ordinary pointer, but we the programmers
 *       know that it's actually the address of an (n x m) array, and we can do
 *       the appropriate indexing math for the compiler. */
void bay(int *mat, int m) {
    *(mat + (0 * m) + 1) = 7;  /* Equivalent to "mat[0][1] = 7". */
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

#include <stdio.h>

int main(void) {
    /* NOTE: This is perfectly valid C syntax, but since x is declared as a
     *       short, the multiplication will overflow: */
    short int x = 16384;
    printf("x: %d\n", x);
    x *= 2;
    printf("x: %d\n", x);

    /* NOTE: This will not compile; although variables are generally mutable,
     *       they are also statically typed, and strings are not integers:
     * x = "0"; */
    x = 0;

    /* NOTE: This will compile, but it evaluates to (-1 < x) < 1, which is
     *       equivalent to 1 < 1, which evaluates to 0: */
    printf("-1 < x < 1: %d\n", -1 < x < 1);
    printf("-1 < x && x < 1: %d\n", -1 < x && x < 1);

    /* NOTE: Under the 1989 ANSI standard, this will not compile; a local
     *       variable can only be declared at the beginning of a block.
     * int y = 0; */

    /* NOTE: This introduces a new block, which then allows y to be declared.
     *       However, the value of uninitialized y is effectively random. */
    {
        int y;

        printf("y (inside): %d\n", y);
        printf("x (inside): %d\n", x);
    }

    /* NOTE: This fails to compile; y is local to the above block, and cannot
     *       be accessed outside.
     * printf("y (outside): %d\n", y); */
    printf("x (outside): %d\n", x);

    return 0;
}

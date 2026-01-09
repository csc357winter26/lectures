#include <stdio.h>

/* NOTE: In computer science, there is often very little cost to trying
 *       something just to see how it works. When learning a new programming
 *       language, we should get into the habit of trying new syntax just to
 *       confirm that it behaves as we understand it. */

int main(void) {
    short int x = 16384;
    printf("x: %d\n", x);

    /* NOTE: This is perfectly valid C syntax, and it compiles and runs without
     *       errors, but since x is short, 16384 * 2 = 32768 overflows. */
    x *= 2;
    printf("x: %d\n", x);

    /* NOTE: This will not compile; although variables are generally mutable,
     *       they are also statically typed, and strings are not integers:
     * x = "0"; */
    x = 0;

    /* NOTE: This is valid syntax, but it is equivalent to (-1 < x) < 1, which
     *       is equivalent to 1 < 1, which evaluates to 0: */
    printf("-1 < x < 1: %d\n", -1 < x < 1);
    printf("-1 < x && x < 1: %d\n", -1 < x && x < 1);

    /* NOTE: Under the 1989 ANSI standard, this fails to compile; locals may
     *       only be declared at the beginning of a block.
     * int y; */

    /* NOTE: This introduces a new block, which then allows y to be declared.
     *       Note the value of the uninitialized y is effectively random. */
    {
        int y;
        printf("y (inside): %d\n", y);
        printf("x (inside): %d\n", x);
    }

    /* NOTE: Although x is in-scope inside the above block, y is not in-scope
     *       outside of it.
     * printf("y (outside): %d\n", y); */
    printf("x (outside): %d\n", x);

    return 0;
}

#include <stdio.h>

/* NOTE: In computer science, there is often very little cost to trying
 *       something just to see how it works. We should get into the habit of
 *       trying new syntax just to confirm that it works as we understand. */
int main(void) {
    short int x = 16384;
    printf("x: %d\n", x);

    /* NOTE: This is perfectly valid C syntax, and it compiles and runs without
     *       errors, however, because x is declared as short, it overflows. */
    x *= 2;
    printf("x: %d\n", x);

    /* NOTE: This fails to compile; x is declared as an integer, and thus it
     *       cannot be reassigned a string at runtime.
     * x = "0"; */
    x = 0;

    /* NOTE: This is valid syntax, but it doesn't behave as expected. This is
     *       equivalent to (-1 < x) < 1, which is equivalent to 1 < 1, which
     *       then evaluates to 0. */
    printf("-1 < x < 1: %d\n", -1 < x < 1);
    printf("-1 < x && x < 1: %d\n", -1 < x && x < 1);

    /* NOTE: Under the 1989 ANSI standard, this fails to compile; locals may
     *       only be declared at the beginning of a block.
     * int y; */

    /* NOTE: This creates a new scope within which is the (uninitialized!)
     *       variable y. Additionally, x is still accessible. */
    {
        int y;
        printf("x (inside): %d\n", x);
        printf("y (inside): %d\n", y);
    }

    /* NOTE: However, y is not accessible outside of the above block, it is
     *       local to that block.
     * printf("y (outside): %d\n", y); */
    printf("x (outside): %d\n", x);

    return 0;
}

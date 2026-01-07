#include <stdio.h>

/* NOTE: Ordinarily, the arguments to main are the command line arguments. If
 *       we the programmers know that we don't need that information, we can
 *       instead declare the parameters as "void" to reassure the compiler that
 *       we didn't just forget to use the arguments we were given. */
int main(void) {
    printf("Hello, world!\n");

    return 0;
}

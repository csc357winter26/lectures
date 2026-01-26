#include <stdio.h>
#include "test.h"

/* NOTE: Arguments are always pass-by-value, and the value of a structure is
 *       the whole structure, so functions receive a copy of their structure
 *       arguments. If this function wishes to pass back an updated structure,
 *       it must return the entire structure. */
Pair foo(Pair pair) {
    pair.first = 3;
    pair.second = 4;

    printf("pair (%p):\n", (void *)&pair);
    printf(" |- first  (%p): %d\n", (void *)&pair.first, pair.first);
    printf(" +- second (%p): %d\n", (void *)&pair.second, pair.second);

    return pair;
}

/* NOTE: Alternatively, we always have the option of emulating pass-by-reference
 *       behavior by passing a pointer instead. Note that the dot operator has
 *       precedence over the unary star operator. */
void bar(Pair *pair) {
    (*pair).first = 5; /* Interchangeable with "pair->first = 5;". */
    (*pair).second = 6; /* Interchangeable with "pair->second = 6;". */

    printf("pair (%p): %p\n", (void *)&pair, (void *)pair);
    printf(" |- first  (%p): %d\n", (void *)&((*pair).first), (*pair).first);
    printf(" +- second (%p): %d\n", (void *)&((*pair).second), (*pair).second);
}

int main(void) {
    Pair pair = {1, 2};

    pair = foo(pair);

    printf("pair (%p):\n", (void *)&pair);
    printf(" |- first  (%p): %d\n", (void *)&pair.first, pair.first);
    printf(" +- second (%p): %d\n", (void *)&pair.second, pair.second);

    bar(&pair);

    printf("pair (%p):\n", (void *)&pair);
    printf(" |- first  (%p): %d\n", (void *)&pair.first, pair.first);
    printf(" +- second (%p): %d\n", (void *)&pair.second, pair.second);

    return 0;
}

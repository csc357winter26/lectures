/* NOTE: This instructs the compiler to copy-paste the text of the header files
 *       into this file. Angle brackets indicate a file in the standard library
 *       whereas quotes indicate a file that we ourselves created. */
#include <stdio.h>
#include "add.h"

/* NOTE: This instructs the compiler to replace any occurrences of the text
 *       "ONE" and "TWO" with "1" and "2", respectively. Note there are no
 *       semicolons, else they would be part of the replacement text. */
#define ONE 1
#define TWO 2

int main(void) {
    printf("add(ONE, TWO): %d\n", add(ONE, TWO));


    return 0;
}

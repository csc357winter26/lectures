#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[16];

    /* NOTE: This program expects to use the existing stdin/stdout streams. If
     *       we then replace the corresponding file descriptors with the ends
     *       of a pipe, we can "trick" this program into reading from and
     *       writing to that pipe instead. */

    fgets(buf, 16, stdin);
    buf[strlen(buf) - 1] = '\0';
    printf("Hello, %s!\n", buf);

    return 0;
}

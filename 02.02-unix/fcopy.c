#include <stdio.h>

/* NOTE: Standard library functions encapsulate the most commonly desired
 *       functionality. For example, even if we ask for 16 bytes, fread will
 *       read a much larger chunk of data into memory. The next time we ask for
 *       16 bytes, fread already has them in memory. */
#define SIZE 16

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n;
    FILE *src, *dest;

    src = fopen(argv[1], "r");
    dest = fopen(argv[2], "w");

    while ((n = fread(buf, sizeof(char), SIZE, src)) > 0) {
        fwrite(buf, sizeof(char), n, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
}

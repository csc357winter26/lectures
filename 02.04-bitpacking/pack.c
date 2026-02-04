#include <stdlib.h>
#include <stdio.h>

unsigned char stob(char *);

int main(int argc, char* argv[]) {
    unsigned char byte;
    char buf[8];
    int n;
    FILE *src, *dest;

    if ((src = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    dest = fopen(argv[2], "w");

    /* NOTE: If the standard library can already do what we need, there is no
     *       reason to reinvent the wheel. In this case, our input is 8-bit
     *       textual characters and our output is 8-bit bytes, both of which
     *       can already be handled by standard library functions. */

    while ((n = fread(buf, sizeof(char), 8, src)) > 0) {
        for (; n < 8; n++) {
            buf[n] = '0';
        }

        byte = stob(buf);
        fwrite(&byte, sizeof(char), 1, dest);
    }

    fclose(src);
    fclose(dest);

    return EXIT_SUCCESS;
}

unsigned char stob(char *bits) {
    unsigned char byte = 0, mask;

    /* NOTE: This function needs to take as argument a string of 8 characters
     *       and return a single byte of 8 bits. Note that the first character
     *       in the string corresponds to the most significant bit in the
     *       byte; character 0 is bit 7. */

    for (mask = 1 << 7; mask > 0; mask >>= 1) {
        if (*(bits++) == '1') {
            byte |= mask;
        }
    }

    return byte;
}

#include <stdlib.h>
#include <stdio.h>

unsigned char stob(char *);

int main(int argc, char* argv[]) {
    unsigned char byte;
    char buf[8];
    int n;
    FILE *src, *dest;

    /* NOTE: When a system call fails, it will set the secret global variable
     *       "errno" to indicate the reason for the failure. The standard
     *       library function "perror" can then be used to print an error
     *       message before returning failure. */

    if ((src = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    if ((dest = fopen(argv[2], "w")) == NULL) {
        perror(argv[2]);
        fclose(src);
        return EXIT_FAILURE;
    }

    /* NOTE: If the standard library can do what we want, there is no reason to
     *       reinvent the wheel. In this case, our input is textual characters
     *       and output is individual bytes, both of which can be handled by the
     *       standard library functions. */

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

    /* NOTE: This function needs to take as input a string of eight characters,
     *       each '0' or '1', and "pack" the corresponding eight bits into a
     *       single byte. Note that the first character in the string is the
     *       most significant bit in the byte. */

    for (mask = 1 << 7; mask > 0; mask >>= 1) {
        if (*(bits++) == '1') {
            byte |= mask;
        }
    }

    return byte;
}

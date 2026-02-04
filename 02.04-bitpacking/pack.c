#include <stdio.h>

unsigned char stob(char *);

int main(int argc, char* argv[]) {
    unsigned char byte;
    char buf[8];
    int n;
    FILE *src, *dest;

    src = fopen(argv[1], "r");
    dest = fopen(argv[2], "w");

    while ((n = fread(buf, sizeof(char), 8, src)) > 0) {
        for (; n < 8; n++) {
            buf[n] = '0';
        }

        byte = stob(buf);
        fwrite(&byte, sizeof(char), 1, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
}

unsigned char stob(char *bits) {
    unsigned char byte = 0;

    return byte;
}

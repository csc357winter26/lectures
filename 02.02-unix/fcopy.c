#include <stdio.h>

/* NOTE: Standard library functions encapsulate the most commonly desired
 *       functionality. For example, even if we ask for only 16 bytes, "fread"
 *       will read a much larger chunk of data (likely 4096 bytes) into a
 *       dynamically allocated buffer... */
#define SIZE 16

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n;
    FILE *src, *dest;

    src = fopen(argv[1], "r");
    dest = fopen(argv[2], "w");

    /* NOTE: ...the next time we ask for another 16 bytes, "fread" already has
     *       them in its buffer. It still makes the system call "read" behind
     *       the scenes, but it only has to call "read" once every 4096 / 16 =
     *       256 times "fread" is called. */
    while ((n = fread(buf, sizeof(char), SIZE, src)) > 0) {
        fwrite(buf, sizeof(char), n, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
}

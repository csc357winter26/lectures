#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* NOTE: By increasing the size of this buffer, we decrease the total number of
 *       system calls we have to make, thereby decreasing the total running
 *       time. A system must transfer control to and from the OS; it takes more
 *       time than an ordinary function call. */
#define SIZE 4096

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n, src, dest;

    /* NOTE: Unlike the standard library function "fopen", the system call
     *       "open" takes options as bitmasks rather than strings, does not
     *       assume the default permissions, and returns a "file descriptor"
     *       that indexes a "file table" behind the scenes rather than a
     *       dyanmically allocated FILE structure. */
    src = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    while ((n = read(src, buf, sizeof(char) * SIZE)) > 0) {
        write(dest, buf, sizeof(char) * n);
    }

    close(src);
    close(dest);

    return 0;
}

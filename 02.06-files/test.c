#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat buf;

    /* NOTE: In the same way that "read" expects a pointer to an array that
     *       will be filled with the data that was read, "stat" expects a
     *       pointer to a structure that will be populated with the metadata
     *       that was read. */
    if (stat(argv[1], &buf) < 0) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    /* NOTE: Each file is uniquely identified by its device and inode number
     *       pair -- files do not have names! Files have numbers, and a
     *       directory maps human-readable names to those numbers. */
    printf("device: %ld\n", buf.st_dev);
    printf("inode:  %ld\n", buf.st_ino);
    printf("size:   %ld\n", buf.st_size);
    printf("blocks: %ld\n", buf.st_blocks);

    return EXIT_SUCCESS;
}

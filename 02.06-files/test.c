#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat buf;

    /* NOTE: In the same way that "read" expects a pointer to an array that
     *       will be filled with the data from the file, "stat" expects a
     *       pointer to a structure that will be populated with the metadata
     *       about the file. */
    if (stat(argv[1], &buf) < 0) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    /* NOTE: Each file is uniquely identified by its device number together
     *       with its inode number -- files do not have names! Files have
     *       numbers, and those numbers are mapped from human-readable
     *       names by the parent directory. */
    printf("device: %ld\n", buf.st_dev);
    printf("inode:  %ld\n", buf.st_ino);
    printf("size:   %ld\n", buf.st_size);
    printf("blocks: %ld\n", buf.st_blocks);

    return EXIT_SUCCESS;
}

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat buf;

    /* NOTE: Every process has a current working directory, a sense of where it
     *       currently "is" in the file system. By changing the CWD to the
     *       given path, any files within that directory can be opened without
     *       having to find them elsewhere in the file system. */
    chdir(argv[1]);

    /* NOTE: Directories are files, and in theory they could be accessed using
     *       the same "open" and "read" system calls as any other file, however,
     *       the format of a directory is not standardized, so the OS provides
     *       library functions that know how to parse a directory. */
    dir = opendir(".");

    /* NOTE: There are plenty of reasons why any of these functions might go
     *       wrong, so we really should be checking these return values for
     *       errors. For the sake of brevity, error checking has been omitted
     *       from this lecture example. */
    while ((entry = readdir(dir)) != NULL) {
        /* NOTE: The only information that is guaranteed to be within a dirent
         *       is the entry's name and the inode number to which it is mapped.
         *       If we want any additional information, we can use the name
         *       to stat the file proper. */
        stat(entry->d_name, &buf);
        printf("%s -> %ld (%ld bytes in %ld blocks)\n",
         entry->d_name, entry->d_ino, buf.st_size, buf.st_blocks);
    }

    closedir(dir);

    return EXIT_SUCCESS;
}

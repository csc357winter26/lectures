#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat buf;

    /* NOTE: Every process has a "current working directory", a sense of where
     *       it currently "is" in the file system. By changing our CWD before
     *       opening it, we ensure that we are "at" the same place as all of
     *       the files contained within the directory. */
    chdir(argv[1]);

    /* NOTE: A directory is a file, so its binary data can be read using the
     *       same system calls as any ordinary file. However, the format of
     *       that binary data is not standardized, so the OS provides library
     *       functions dedicated to reading directories. */
    dir = opendir(".");

    /* NOTE: There are myriad reasons why any of these functions might go
     *       wrong; "readdir", for example, also returns NULL in case of error,
     *       not just when it reaches the end of the directory. For brevity,
     *       error checking has been left out of this lecture example. */
    while ((entry = readdir(dir)) != NULL) {

        /* NOTE: The only information guaranteed to be in a directory entry is
         *       the filename and inode number to which it is mapped. Once we
         *       have the filename, any additional information can be queried
         *       with "stat". */
        stat(entry->d_name, &buf);
        printf("%s -> %ld (%ld bytes in %ld blocks)\n",
         entry->d_name, entry->d_ino, buf.st_size, buf.st_blocks);
    }

    closedir(dir);

    return EXIT_SUCCESS;
}

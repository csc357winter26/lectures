#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* NOTE: Making a system call takes longer than calling an ordinary function,
 *       since system calls have to transfer control to and from the OS. By
 *       increasing the size of the buffer, we decrease the number of system
 *       calls and therefore the amount of time the program takes. */
#define SIZE 4096

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n, src, dest;

    /* NOTE: The system call "open" takes a bitmask of options instead of a
     *       string, forces us to provide new files' permissions instead of
     *       using the default, and returns a "file descriptor" that indexes a
     *       behind-the-scenes "file table" instead of a FILE structure. */
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

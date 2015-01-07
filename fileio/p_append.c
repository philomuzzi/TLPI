#include <sys/stat.h>
#include <fcntl.h>

extern "C"
{
    #include "tlpi_hdr.h"
}

int main(int argc, char **argv)
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    int fd = open(argv[1], O_WRONLY | O_APPEND);
    if (fd == -1)
        errExit("open");

    int numWrite;

    if ((numWrite = write(fd, "111\n", 4)) == -1)
        errExit("write");

    if (numWrite == 4)
        printf("%s write 4 char\n", argv[1]);

    if (lseek(fd, 0, SEEK_SET) == -1)
        errExit("lseek");

    if ((numWrite = write(fd, "222\n", 4)) == -1)
        errExit("write");

    if (numWrite == 4)
        printf("%s write 4 char\n", argv[1]);

    exit(EXIT_SUCCESS);
}
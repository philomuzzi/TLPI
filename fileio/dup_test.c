#include <sys/stat.h>
#include <fcntl.h>

extern "C"
{
    #include "tlpi_hdr.h"
}

int main(int argc, char** argv)
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s filename\n", argv[0]);

    int fd, fd1, fd2, fd3;

    fd = open(argv[1], O_RDWR | O_APPEND | O_CREAT);
    if (fd == -1)
        errExit("open");

    if (write(fd, "123\n", 4) == -1)
        errExit("write");

    fd1 = dup(fd);
    if (fd1 == -1)
        errExit("dup");

    if (write(fd, "234\n", 4) == -1)
        errExit("write");

    fd2 = dup2(fd, 2);
    if (fd2 == -1)
        errExit("dup2");

    if (fd2 != 2)
        cmdLineErr("fd2 should be 2, now is %d\n", fd2);

    if (write(fd2, "345\n", 4) == -1)
        errExit("write");

    fd3 = dup3(fd, 100, O_CLOEXEC);
    if (fd3 == -1)
        errExit("dup3");

    if (fd3 != 100)
        cmdLineErr("fd3 shoule be 3, now is %d\n", fd3);

    if (write(fd3, "456\n", 4) == -1)
        errExit("write");

    exit(EXIT_SUCCESS);
}
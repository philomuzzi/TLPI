#include <fcntl.h>

extern "C"
{
    #include "tlpi_hdr.h"
}

int my_dup(int oldfd)
{
    int fd = fcntl(oldfd, F_DUPFD, 0);
    return fd;
}

int my_dup2(int oldfd, int newfd)
{
    if (fcntl(oldfd, F_GETFL) == -1)
    {
        errno = EBADF;
        return -1;
    }

    if (oldfd == newfd)
        return newfd;

    if (fcntl(newfd, F_GETFL) != -1)
    {
        close(newfd);
    }

    int fd = fcntl(oldfd, F_DUPFD, newfd);
    return fd;
}

int main(int argc, char** argv)
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    int fd, fd2, tmpfd;
    fd = open(argv[1], O_RDONLY | O_CREAT);
    if (fd == -1)
        errExit("open");

    fd2 = my_dup(fd);
    printf("fd not equal to fd2, fd: %d, fd2: %d\n", fd, fd2);

    tmpfd = my_dup2(fd, fd);
    printf("fd should equal to tmpfd, fd: %d, tmpfd: %d\n", fd, tmpfd);

    tmpfd = my_dup2(fd, -20);
    printf("tmpfd should be 有效, tmpfd: %d\n", tmpfd);

    tmpfd = dup2(fd, -20);
    printf("tmpfd should be 有效, tmpfd: %d\n", tmpfd);

    tmpfd = my_dup2(-2, tmpfd);
    printf("tmpfd shoule be -1, tmpfd:%d, errno:%d\n", tmpfd, errno);

    exit(EXIT_SUCCESS);
}

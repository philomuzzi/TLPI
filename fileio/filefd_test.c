#include <fcntl.h>

extern "C"
{
    #include "tlpi_hdr.h"
}

int main(int argc, char** argv)
{
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    int fd, fd2;
    fd = open(argv[1], O_RDWR | O_CREAT);
    if (fd == -1)
        errExit("open");

    fd2 = dup(fd);
    if (fd2 == -1)
        errExit("dup");

    int flags, flags2;
    flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        errExit("fcntl");

    flags2 = fcntl(fd2, F_GETFL);
    if (flags2 == -1)
        errExit("fcntl");

    if (flags == flags2)
        printf("dup fd have same fcntl flags\n");

    int cur, cur2;
    cur = lseek(fd, 0, SEEK_CUR);
    if (cur == -1)
        errExit("lseek");

    cur2 = lseek(fd2, 0, SEEK_CUR);
    if (cur2 == -1)
        errExit("lseek");

    if (cur == cur2)
        printf("dup fd have same file offset\n");

    exit(EXIT_SUCCESS);
}

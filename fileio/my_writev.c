#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>

extern "C"
{
    #include "tlpi_hdr.h"
}

struct MyStruct
{
    int x;
    int y;
    int z;
};

int my_writev(int fd, const struct iovec *iov, int iovcnt)
{

}

int main(int argc, char** argv)
{
    int fd;
    struct iovec iov[3];
    struct MyStruct myStruct;
    myStruct.x = 1;
    myStruct.y = 2;
    myStruct.z = 3;
    int x = 1000;
    char *str = "abcd\n";
    ssize_t numWrite, totRequired;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    fd = open(argv[1], O_WRONLY | O_CREAT);
    if (fd == -1)
        errExit("open");

    totRequired = 0;

    iov[0].iov_base = &myStruct;
    iov[0].iov_len = sizeof(struct stat);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    totRequired += iov[1].iov_len;

    iov[2].iov_base = &str;
    iov[2].iov_len = strlen(str);
    totRequired += iov[2].iov_len;

    numWrite = writev(fd, iov, 3);
    if (numWrite == -1)
        errExit("writev");

    if (numWrite != totRequired)
        cmdLineErr("writev error, numWrite not equal to totRequired\n");

    printf("total bytes requested: %ldl bytes read: %ld\n", (long)totRequired, (long)numRead);

    exit(EXIT_SUCCESS);
}
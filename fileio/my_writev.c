#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>

extern "C"
{
    #include "tlpi_hdr.h"
}

int my_writev(int fd, const struct iovec *iov, int iovcnt)
{
    int numWrite;
    int len = 0;
    for(int i = 0; i != iovcnt; ++i)
    {
        len += iov[i].iov_len;
        printf("len: %d\n", len);
    }

    char* buf = (char*)malloc(len + 1);
    memset(buf, 0, len+1);

    char* k = buf;
    for (int i = 0; i != iovcnt; ++i)
    {
        memcpy(k, iov[i].iov_base, iov[i].iov_len);
        k += iov[i].iov_len;
    }

// 可能需要一个while循环才能写完，因为可能被中断
    numWrite = write(fd, buf, len);
    if(numWrite == -1)
        return -1;

    return numWrite;
}

int main(int argc, char** argv)
{
    int fd;
    struct iovec iov[3];
    int z = 222200;
    int x = 100000;
    char *str = "abcdefghijk";
    ssize_t numWrite, totRequired;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    fd = open(argv[1], O_WRONLY | O_CREAT);
    if (fd == -1)
        errExit("open");

    totRequired = 0;

    iov[0].iov_base = &z;
    iov[0].iov_len = sizeof(z);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    totRequired += iov[1].iov_len;

    iov[2].iov_base = &str;
    iov[2].iov_len = strlen(str) + 1;
    totRequired += iov[2].iov_len;

    numWrite = my_writev(fd, iov, 3);
    if (numWrite == -1)
        errExit("my_writev");

    if (numWrite != totRequired)
        printf("writev error, numWrite not equal to totRequired\n");

    printf("total bytes requested: %ld bytes write: %ld\n", (long)totRequired, (long)numWrite);

    int fd2 = open(argv[1], O_RDONLY);
    if (fd2 == -1)
        errExit("open");

    char buf[100];
    read(fd2, buf, 100);
    printf("content: %s\n", buf);

    exit(EXIT_SUCCESS);
}

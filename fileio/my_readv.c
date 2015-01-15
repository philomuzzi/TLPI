#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>

extern "C"
{
    #include "tlpi_hdr.h"
}

int my_readv(int fd, const struct iovec *iov, int iovcnt)
{
    int numRead = 0;

    // 读取到一个缓存里面，然后再一一copy到iov中
#define MAX_TMP 1000
    char* tmp = (char*)malloc(MAX_TMP);
    memset(tmp, 0, MAX_TMP);

    int tmpRead;
    while ((tmpRead = read(fd, tmp, MAX_TMP-numRead)) != 0)
    {
        // 需要处理信号
        if (tmpRead == -1 && errno != EINTR)
            return -1;
        numRead += tmpRead;
    }

    printf("numRead: %d\n", numRead);

    char * j = tmp;
    for (int i = 0; i != iovcnt; ++i)
    {
        memcpy(iov[i].iov_base, j, iov[i].iov_len);
        j += iov[i].iov_len;
    }

    return numRead;
}

int main(int argc, char** argv)
{
    int fd;
    struct iovec iov[3];
    int z;
    int x;
#define STR_SIZE 100
    char str[STR_SIZE];
    ssize_t numRead, totRequired;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    fd = open(argv[1], O_RDONLY);
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
    iov[2].iov_len = STR_SIZE;
    totRequired += iov[2].iov_len;

    numRead = my_readv(fd, iov, 3);
    if (numRead == -1)
        errExit("readv");

    if (numRead < totRequired)
        printf("Read fewer bytes than requested\n");

    printf("total bytes requested: %ld bytes read: %ld\n", (long)totRequired, (long)numRead);
    printf("z: %d, x: %d, str: %s\n", z, x, str);

    exit(EXIT_SUCCESS);
}

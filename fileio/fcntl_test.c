#include <sys/stat.h>
#include <fcntl.h>
extern "C" {
    #include "tlpi_hdr.h"
}

int main(int argc, char** argv)
{
    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s -r|-w|-rw file\n", argv[0]);

    int flags, accessMode, fd, numWrite, openflags;

    openflags = O_CREAT | O_SYNC;

    if (strcmp(argv[1], "-w") == 0)
        openflags |= O_WRONLY;
    else if (strcmp(argv[1], "-rw") == 0)
        openflags |= O_RDWR;
    else
        openflags |= O_RDONLY;

    fd = open(argv[2], openflags);
    if (fd == -1)
        errExit("open");

    flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        errExit("fcntl");

    if (flags & O_SYNC)
        printf("writes are synchronized\n");

    accessMode = flags & O_ACCMODE;
    if (accessMode == O_WRONLY || accessMode == O_RDWR)
        printf("%s is writable\n", argv[2]);

    if (accessMode == O_RDONLY || accessMode == O_RDWR)
        printf("%s is readable\n", argv[2]);

    if ((numWrite = write(fd, "123456789\n", 10)) == -1)
        printf("%s write failed!\n", argv[2]);

    if (numWrite == 10)
        printf("%s write %d charaters!\n", argv[2], 10);

    flags |= O_APPEND;
    // can not set access mode
    accessMode = O_RDWR;
    flags |= accessMode;
    if (fcntl(fd, F_SETFL, flags) == -1)
        errExit("fcntl");

    if ((numWrite = write(fd, "abcd\n", 5)) == -1)
        errExit("write");

    if (numWrite == 5)
        printf("%s write %d charaters!\n", argv[2], 5);

    exit(EXIT_SUCCESS);
}

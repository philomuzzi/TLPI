#include <sys/stat.h>
#include <fcntl.h>
extern "C" {
    #include "tlpi_hdr.h"
}

int main(int argc, char** argv)
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    int flags, accessMode, fd. numWrite;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        errExit("open");

    flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        errExit("fcntl");

    if (flags & O_SYNC)
        printf("writes are synchronized\n");

    accessMode = flags & O_ACCMODE;
    if (accessMode == O_WRONLY || accessMode == O_RDWR)
        printf("file is writable\n");

    if (accessMode == O_RDONLY || accessMode == O_RDWR)
        printf("file is readable\n");

    if ((numWrite = write(fd, "12345", 5)) == -1)
        printf("write file failed!\n");

    flags |= O_APPEND;
    accessMode = O_RDWR;
    flags |= accessMode;
    if (fcntl(fd, F_SETFL, flags) == -1)
        errExit("fcntl");

    if ((numWrite = write(fd, "12345", 5)) == -1)
        errExit("write");

    if (numWrite == 5)
        printf("%s write %d charaters!\n", argv[1], 5);

    exit(EXIT_SUCCESS);
}
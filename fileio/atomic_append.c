#include <sys/stat.h>
#include <fcntl.h>

extern "C"
{
    #include "tlpi_hdr.h"
}

int main(int argc, char **argv)
{
    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    size_t num_bytes;
    bool bAppend = true;
    int openFlags = O_WRONLY | O_CREAT | O_APPEND;

    num_bytes = getLong(argv[2], GN_ANY_BASE, argv[2]);

    if (argc == 4 && strcmp(argv[3], "x") == 0)
    {
        openFlags = O_WRONLY | O_CREAT;
        bAppend = false;
    }

    int fd = open(argv[1], openFlags);
    if (fd == -1)
        errExit("open");

    while(num_bytes--)
    {
        if (bAppend) {
            if (write(fd, "1", 1) != 1)
                fatal("Partial/failed write");
        } else {
            if (lseek(fd, 0, SEEK_END) == -1)
                errExit("lseek");
            if (write(fd, "1", 1) != 1)
                fatal("Partial/failed write");
        }
    }

    exit(EXIT_SUCCESS);
}
